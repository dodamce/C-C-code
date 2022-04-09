#pragma once

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

namespace NetWork_Sorket{
  class Sork{
    public:
      static int Socket(){
        //创建监听套接字
        int listenSock=socket(AF_INET,SOCK_STREAM,0);
        if(listenSock<0){
          std::cout<<"socket error"<<std::endl;
          exit(-1);
        }
        int opt=1;
        //设置套接字属性
        setsockopt(opt,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
        return listenSock;
      }

      static bool Bind(int listenSock,int port){
        //绑定,IP=INADDR_ANY
        struct sockaddr_in local;
        memset(&local,0,sizeof(local));
        local.sin_family=AF_INET;
        local.sin_port=htons(port);
        local.sin_addr.s_addr=INADDR_ANY;
        if(bind(listenSock,(struct sockaddr*)&local,sizeof(local))<0){
          std::cout<<"bind error"<<std::endl;
          exit(-2);
        }
        return true;
      }

      static int Listen(int listenSock,int Len){//全连接队列长度
        //监听
        if(listen(listenSock,Len)<0){
          std::cout<<"listen error"<<std::endl;
          exit(-3);
        }
        return true;
      }
  };
}
