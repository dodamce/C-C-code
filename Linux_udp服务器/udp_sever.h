#pragma once

#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<cstring>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>

class UdpSever{
  private:
    int port;
    int sockfd;
  public:
    UdpSever(int _port):port(_port),sockfd(-1){}

    ~UdpSever(){
      if(sockfd>0)
      {
        close(sockfd);
      }
    }
    bool InitUdpSever()
    {
      sockfd=socket(AF_INET,SOCK_DGRAM,0);//ipv4 udp协议
      if(sockfd<=0){
        std::cerr<<"socket error"<<std::endl;
        return false;
      }
      std::cout<<"socket creat success sockfd:"<<sockfd<<std::endl;//socket=3文件描述符

      //绑定端口与ip
      struct sockaddr_in local;
      memset(&local,'\n',sizeof(local));//初始化
      local.sin_family=AF_INET;//通信家族
      local.sin_port=htons(port);//端口转为网络字节序
      local.sin_addr.s_addr=INADDR_ANY;//字符串型IP转数字型IP
      //绑定
      if(bind(sockfd,(struct sockaddr*)&local,sizeof(local))<0)
      {
        std::cerr<<"bind error"<<std::endl;
        return false;
      }
      std::cout<<"bind success"<<std::endl;
      return true;
    }

#define SIZE 255
    void Start()
    {
      while(true)
      {
        //udp接受消息
        char buff[SIZE]={0}; //预留一个空间给'\0'
        sockaddr_in client;
        socklen_t len=sizeof(client);
        ssize_t size=recvfrom(sockfd,buff,sizeof(buff)-1,0,(struct sockaddr*)&client,&len);
        if(size>0)
        {
          buff[size]='\0';
          int _port=ntohs(client.sin_port);//对端的端口号
          std::string _ip=inet_ntoa(client.sin_addr);
          std::cout<<_ip<<":"<<_port<<"#"<<buff<<std::endl;

          std::string cmd=buff;
          std::string ret;//存放父进程读取到的管道信息
          if(cmd=="ls")
          {
            int pipes[2];
            pipe(pipes);//匿名管道
            //进程替换执行操作
            pid_t id=fork();
            if(id==0)
            {
              //child进程进行写入
              close(pipes[0]);
              dup2(pipes[1],1);//将显示屏上的数据写到管道中
              execl("/usr/bin/ls","ls","-a","-l","-i",nullptr);
              exit(-1);
            }
            //父进程要读取数据放到ret字符串中
            close(pipes[1]);
            char ch=0;
            while(true)
            {
              if(read(pipes[0],&ch,1)>0)
              {
                ret.push_back(ch);
              }
              else 
              {
                break;
              }
            }
            wait(nullptr);//等待任意一个进程
          }

          std::string echo_meg="sever get! ";
          if(ret.empty())//表明不是ls命令
          {
            echo_meg+=buff;
          }
          else//是ls命令，将服务器文件发送到网络中 
          {
            echo_meg=ret;
          }
          
          sendto(sockfd,echo_meg.c_str(),echo_meg.size(),0,(struct sockaddr*)&client,len);
        }
        else 
        {
          std::cerr<<"recvfrom error"<<std::endl;
        }
      }
    }
};

