#pragma once

#include"sock.h"

#define LISTEN_SIZE 5
#define RFDS_SIZE (sizeof(fd_set)*8)  //最大可以等待的套接字个数1024
#define DEF_FD -1 //默认无效套接字

#include<sys/select.h>
#include<vector>
#include<algorithm>

namespace Select{
  class SelectSever{
    private:
      int listenSork;
      int port;
    public:
      SelectSever(int _port):port(_port){
        listenSork=NetWork_Sorket::Sork::Socket();

      }

      void InitSever(){
        NetWork_Sorket::Sork::Bind(listenSork,port);
        NetWork_Sorket::Sork::Listen(listenSork,LISTEN_SIZE);
      }

      void Start(){
        fd_set rfds;//读文件描述符集
        std::vector<int>fd_Array(RFDS_SIZE,DEF_FD);//保存所有文件描述符,DEF_FD代表没有文件描述符。
        fd_Array[0]=listenSork;//将监听套接字写入数组第一个元素，之后将其写入到rfds让select等待链接就绪

        while(true){
          //对所有合法的文件描述符，每次循环重新设置到rfds

          FD_ZERO(&rfds);//每次处理后将rfds位图清空
          //遍历数组，将有效文件描述符设置到rfds
          for(auto& fd:fd_Array){
            if(fd==DEF_FD){
              continue;
            }
            else{
              //合法fd,添加到文件描述符集中
              FD_SET(fd,&rfds);
            }
          }
          int MaxFd=*(std::max_element(fd_Array.begin(),fd_Array.end()));//获取数组最大的文件描述符值
          //设定select时间参数(输入，输出参数)，每次循环需要重新设定
          //struct timeval timeout={5,0};//每隔5秒一次
          /*
           * seclect中的timeout=nullptr时select会阻塞等待
           * timeout={0};非阻塞轮询
           * timeout={a,b}as bms之后返回，无论是否有事件就绪
           * */
          switch(select(MaxFd+1,&rfds,nullptr,nullptr,/*&timeout*/nullptr)){
            case 0://超时
              std::cout<<"over time"<<std::endl;
              break;
            case -1://等待出错
              std::cout<<"select error"<<std::endl;
              break;
            default://正常事件处理
              //std::cout<<"select!"<<std::endl;
              //事件处理，所有事件就绪情况在rfds中
              EventProc(rfds,fd_Array);
              break;
          }//end switch
        }//end sever
      }
      ~SelectSever(){
      }
    private:
      void EventProc(const fd_set& rfds,std::vector<int>&fd_Array){
        //判定特定的fd是否在rfds中，证明fd文件描述符已经就绪。
        for(auto&fd:fd_Array ){
          if(fd==DEF_FD){
            continue;
          }
          if(FD_ISSET(fd,&rfds)&&fd==listenSork){
            //监听套接字已经就绪
            struct sockaddr_in peer;
            socklen_t len=sizeof(peer);
            int sock=accept(fd,(struct sockaddr*)&peer,&len);//不会阻塞
            if(sock<0){
              std::cout<<"accept error"<<std::endl;
              continue;
            }
            //链接建立后，还要判断sock文件描述符是否就绪，将sock放入select中让select等待数据就绪,服务器不需要阻塞
            //将文件描述符添加到fd_Array中,找到数组未使用的位置
            int peer_port=htons(peer.sin_port);
            std::string peer_ip=inet_ntoa(peer.sin_addr);
            std::cout<<"accept! "<<peer_ip<<" : "<<peer_port<<std::endl;
            std::vector<int>::iterator pos=find(fd_Array.begin(),fd_Array.end(),DEF_FD);
            if(pos==fd_Array.end()){//数组已满
              close(sock);//无法处理，直接关闭接受的sock
              std::cout<<"select sever is full ! close sock:"<<sock<<std::endl;
            }
            else{
              *pos=sock;
            }
          } 
          else{
            //处理正常的fd，先判断fd是否就绪
            if(FD_ISSET(fd,&rfds)){
              //读事件就绪,实现不阻塞的读
              char buff[1024]={0};
              ssize_t size=recv(fd,buff,sizeof(buff)-1,0);
              if(size>0){
                buff[size]='\0';
                std::cout<<"echo# "<<buff<<std::endl;
              }
              else if(size==0){
                std::cout<<"client quit!"<<std::endl;
                //数组对应位置设置为DEF_FD,关闭文件描述符
                close(fd);
                fd=DEF_FD;
              }
              else{
                std::cerr<<"recv error"<<std::endl;
                close(fd);
                fd=DEF_FD;
              }
            }
            else{//fd未就绪
              //...
            }
          }
        }//end for
      }//end fuction
  };
}
