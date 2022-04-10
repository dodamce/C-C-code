#pragma once 

#include<iostream>
#include"epoller.h"
#include"Util.h"
#include<vector>
#include<string>

namespace interface{

  using namespace EpollSever;

  int recver(EventItem*);
  int sender(EventItem*);
  int error(EventItem*);

  int accepter(EventItem*item){
    while(true){
      struct sockaddr_in peer;
      socklen_t len=sizeof(peer);
      int sock=accept(item->sock,(struct sockaddr*)&peer,&len);
      if(sock<0){//->
        if(errno==EAGAIN||errno==EWOULDBLOCK){//底层没有连接了

          //std::cout<<"no link need to accept"<<std::endl;
          return 0;
        }
        if(errno==EINTR){
          //std::cout<<"interrupted by a signal"<<std::endl;
          //读取过程被信号打断
          continue;
        }
        else{
          //读取出错
          item->error_hander(item);
          return -1;
        }
      }
      else{
        std::cout<<"get a new link sock="<<sock<<std::endl;
        //设置非阻塞
        Util::SetNoBlock(sock);
        //读取成功,添加到epoller中,并添加这个套接字的注册方法
        EventItem tmp_item;
        tmp_item.sock=sock;
        tmp_item.Epoller=item->Epoller;
        tmp_item.RegisterCallBack(recver,sender,error);
        epoller* tmp_Epoller=item->Epoller;
        tmp_Epoller->AddEvent(sock,EPOLLIN|EPOLLET,tmp_item);
       // std::cout<<"add done"<<std::endl;
      }
    }

    return 0;
  }

  int recv_sock(int sock,std::string&out){
    //返回0 读取成功，-1读取失败
    while(true){
      char buff[1024]={0};
      ssize_t size=recv(sock,buff,sizeof(buff)-1,0);
      if(size<0){
        if(errno==EAGAIN||errno==EWOULDBLOCK){
          //读取完毕->
          return 0;
        }
        else if(errno==EINTR){
          //被信号中断
          continue;
        }
        else{
          //读取出错
          return -1;
        }
      }
      else{
        buff[size]=0;
        out+=buff;//将读取到的内容添加到inbuff中
      }
    }
  }

  int recver(EventItem*item){
    //数据读取
    //1.非阻塞读取
   // std::cout<<"recver redy"<<item->sock<<std::endl;
    if(recv_sock(item->sock,item->inbuff)<0){
      //读取失败->
      item->error_hander(item); 
      return -1;
    }
    //std::cout<<"client# "<<item->inbuff<<std::endl;
    //2.根据发来的数据流进行分包，防止粘包，涉及到协议定制，约定以|标定报文之间的分割符
    std::vector<std::string>MessArray;
    Util::SplitStr(item->inbuff,MessArray,"|");

    //std::cout<<item->inbuff<<std::endl;
    //3.针对每个报文，进行协议反序列化,这里要处理加法运算
    struct Date{
      int x=0;int y=0;
    };
    for(auto&mes:MessArray){
      std::cout<<mes<<std::endl;
      struct Date date;
      //将a+b字符串反序列化成 struct Date{int x=a;int y=b;}; 
      Util::Deserialize(mes,date.x,date.y);
      //std::cout<<date.x<<":"<<date.y<<std::endl;
      //4.业务处理，可以与线程池拓展处理，这里不考虑（构建任务类，将任务插入到线程池中）
      int ret=date.x+date.y;
      //5.形成响应报文，协议序列化成字符串
      std::string respon;
      respon+=std::to_string(date.x);
      respon+="+";
      respon+=std::to_string(date.y);
      respon+="=";
      respon+=std::to_string(ret);
      //添加响应报文的分隔符
      respon+="|";
      //6.写回
      //添加到输出缓冲区上
      item->outbuff+=respon;
    }
    //修改文件描述符的写
    if(!item->outbuff.empty()){
      item->Epoller->EnableReadWrite(item->sock,true,true);//关心这个文件描述符的读写
    }
    return 0;
  }

  //ET模式一次全部写完
  //返回0代表写完了，1代表没写完，下次继续写，-1写入失败
  int sender_sock(int sock,std::string&in){
    size_t total=0;//当前写入的字数,//不能直接全部发出，因为对端可能不能一次全部接受。
    while(true){
      size_t size=send(sock,in.c_str()+total,in.size()-total,0);
      if(size>0){
        total+=size;
        if(total>=in.size()){
          //写完了
          return 0;
        }
      }
      else if(size<0){
        if(errno==EAGAIN||errno==EWOULDBLOCK){
          in.erase(0,total);
          return 1;//对端无法再接受，但是写成功了,需要将发送缓冲区移除所有已经发送的数据->
        }
        else if(errno==EINTR){//被信号中断
          continue;
        }
        else{
          //写入失败
          return -1;
        }
      }
    }
  }

  int sender(EventItem*item){
    //发送数据
    int ret=sender_sock(item->sock,item->outbuff);
    if(ret==0){
      //发送完毕，不在关心这个文件描述符的写
      item->Epoller->EnableReadWrite(item->sock,true,false); 
    }
    else if(ret==1){
      //还没有全部发送完，继续关注这个文件描述符的读写,虽然这里默认文件描述符已经被设置了关心读写，这里为了保险再设置一次
      item->Epoller->EnableReadWrite(item->sock,true,true);
    }
    else{
      //出错
      item->error_hander(item);
    }
    return 0;
  }

  int error(EventItem*item){
    //出错
    //此时文件描述符被设置成了可读可写，可自行返回错误响应
    close(item->sock);
    item->Epoller->DelEvent(item->sock);
    return 0;
  }
}
