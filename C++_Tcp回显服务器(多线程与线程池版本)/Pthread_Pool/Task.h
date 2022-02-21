#pragma once 

#include<iostream>
#include<string>
#include<unistd.h>
#include<string.h>

struct Hander{
  void operator()(int sock,std::string&ip,int port)
  {
    char buff[1024];
    while(true)
    {
       memset(buff,0,sizeof(buff));
       ssize_t ReadSize=read(sock,buff,sizeof(buff)-1);
       if(ReadSize>0){
         buff[ReadSize]='\0';//添加字符串结束标志
         std::cout<<"Client["<<ip<<"-port-"<<port<<"]# "<<buff<<std::endl;
         write(sock,buff,ReadSize);//向服务器写入数据
       }
       else if(ReadSize==0){//对端关闭链接
         std::cout<<"Client["<<ip<<"-port-"<<port<<"]# 关闭"<<std::endl;
         break;
       }
       else{
         std::cerr<<sock<<"读取错误"<<std::endl;
         break;
      }
    }
    std::cout<<"服务终止"<<std::endl;
    close(sock);
  }
};

class Task{
  private:
    int sock;
    std::string ip;
    int port;
    Hander condut;//仿函数
  public:
    Task()=default;
    Task(int _sock,std::string _ip,int _port)
      :sock(_sock),ip(_ip),port(_port)
    {}

    void Run(){
      condut(sock,ip,port);
    }

};
