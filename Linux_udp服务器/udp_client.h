#pragma once 

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<cstring>
#include<unistd.h>

class UdpClient{
  private:
    int sockfd;
    std::string ip;
    int sever_port;
  public:
    UdpClient(std::string _ip,int _sever_port):sockfd(-1),ip(_ip),sever_port(_sever_port){}

    ~UdpClient(){
      if(sockfd>0)
      {
        close(sockfd);
      }
    }

    bool InitUdpClient()
    {
      sockfd=socket(AF_INET,SOCK_DGRAM,0);
      if(sockfd<0)
      {
        std::cerr<<"socket error"<<std::endl;
        return false;
      }
      //客户端不需要绑定，sendto函数会采用系统自己分配
      return true;
    }

    void Start()
    {
      std::string meg;
      struct sockaddr_in sever;
      memset(&sever,0,sizeof(sever));
      sever.sin_family=AF_INET;
      sever.sin_port=htons(sever_port);
      sever.sin_addr.s_addr=inet_addr(ip.c_str());
      while(true)
      {
        std::cout<<"Please Enter#";
        std::cin>>meg;
        sendto(sockfd,meg.c_str(),meg.size(),0,(struct sockaddr*)&sever,sizeof(sever));

        char buff[128]={0};

        struct sockaddr_in tmp;
        socklen_t len=sizeof(tmp);
        ssize_t size=recvfrom(sockfd,buff,sizeof(buff)-1,0,(struct sockaddr*)&tmp,&len);
        if(size>0)
        {
          buff[size]='\0';
          std::cout<<buff<<std::endl;
        }
        else 
        {
          std::cout<<"recvfrom error"<<std::endl;
        }
      }
    }
};


