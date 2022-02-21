#pragma once

#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>
#include<string.h>

class TcpClient
{
  private:
    std::string sev_ip;//服务器ip
    int sev_port;
    int sock;
  public:
    TcpClient(std::string _ip,int _sev_port):sev_ip(_ip),sev_port(_sev_port),sock(-1)
    {}

    void InitClient()
    {
      sock=socket(AF_INET,SOCK_STREAM,0);
      if(sock<0){
        std::cerr<<"创建套接字失败"<<std::endl;
        exit(-1);
      }
      //客户端不需要绑定监听
    }

    //启动客户端
    void Start()
    {
      //向服务器发送链接
      //填充服务器信息
      struct sockaddr_in sever;
      memset(&sever,0,sizeof(sever));
      sever.sin_family=AF_INET;
      sever.sin_port=htons(sev_port);//服务器开放的端口
      sever.sin_addr.s_addr=inet_addr(sev_ip.c_str());//服务器的ip地址

      if(connect(sock,(struct sockaddr*)&sever,sizeof(sever))==0){
        //与服务器交互
        std::cout<<"发送交互请求成功"<<std::endl;
        Request(sock);
      }
      else{
        std::cerr<<"交互失败"<<std::endl;
      }
    }

    void Request(int Sock)
    {
      std::string meg;
      while(true)
      {
        std::cout<<"输入信息#";
        std::cin>>meg;
        char buff[1024];
        write(Sock,meg.c_str(),meg.size());
        //读取服务器发送的消息
        ssize_t ReadSize=read(sock,buff,sizeof(buff)-1);
        if(ReadSize>0){
          buff[ReadSize]='\0';
        }
        std::cout<<"Sever#"<<buff<<std::endl;
      }
    }
    
    ~TcpClient()
    {
      if(sock>=0){
        close(sock);
      }
    }
};
