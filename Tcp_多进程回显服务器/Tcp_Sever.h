#pragma once 

#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>

#define DEF_PORT 8081

class TcpSever
{
  private:
    int port;
    int listen_sock;//监听套接字
  public: 
    TcpSever(int _port=DEF_PORT):port(_port),listen_sock(-1)
    {}

    void InitSever()
    {
      listen_sock=socket(AF_INET,SOCK_STREAM,0);//IPV4流式套接
      if(listen_sock<0){
        std::cerr<<"监听套接字创建失败"<<std::endl;
        exit(-1);
      }
      //绑定
      struct sockaddr_in local;
      memset(&local,'\0',sizeof(local));//初始化结构体
      local.sin_family=AF_INET;
      local.sin_port=htons(port);//主机转网络
      local.sin_addr.s_addr=INADDR_ANY;//随机绑定服务器ip
      if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0){
        std::cerr<<"绑定失败"<<std::endl;
        exit(-2);
      }
      //建立链接
#define BACK_LOG 5
      if(listen(listen_sock,BACK_LOG)<0){
        std::cerr<<"链接失败"<<std::endl;
        exit(-3);
      }
    }

    //获取链接
    void Loop()
    {
      //获取客户端信息
      struct sockaddr_in client;
      //signal(SIGCHID,hander);//hander是信号捕捉方法
      while(true)
      {
        socklen_t len=sizeof(client);
        //获取新链接
        int sock=accept(listen_sock,(struct sockaddr*)&client,&len);
        if(sock<0){
          std::cerr<<"接受链接失败"<<std::endl;
          continue;//继续接受其他链接请求
        }
        //多线程处理多个客户端
        pid_t id=fork();
        if(id==0)//子进程
        {
          //子进程,与子进程的子进程不关心listen_sock
          close(listen_sock);
          if(fork()>0)
          {
            exit(0);//子进程直接退出后子进程的子进程变为孤儿进程被守护进程接管，不用等待了
          }
          //子进程的子进程,处理业务
          std::cout<<"获取新连接成功! ip["<<inet_ntoa(client.sin_addr)<<"] port["<<ntohs(client.sin_port)<<"]"<<std::endl;//整数ip转为字符ip形式,网络字节端口转化为本地端口
           //开始服务
          std::string CIp=inet_ntoa(client.sin_addr);
          int CPort=ntohs(client.sin_port);
          Sever(sock,CIp,CPort);
          exit(0);
        }
        //不能使用阻塞等待，可以使用信号机制忽略SIGCHID信号，或者使用两次fork函数
        close(sock);//父进程不关心客户端的链接请求，请求交给子进程做。
        waitpid(id,nullptr,0);//不会阻塞，因为id进程创建完子进程会立即退出，所以不会阻塞。
      }
    }

    void Sever(int sock,std::string&ip,int port)
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
      //关闭链接
      close(sock);
      std::cout<<"服务终止"<<std::endl;
    }
    ~TcpSever(){
      if(listen_sock>=0){
        close(listen_sock);
      }
    }
};
