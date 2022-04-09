#pragma once

#include"sork.h"
#include<sys/epoll.h>

namespace EpollSever{

#define MAXSIZE 64
  const int Back_Log=5;

  class epoll_sever{
    private:
      int listen_sock;
      int epfd;
      int port;
    public:
      epoll_sever(int _port):port(_port){
        listen_sock=NetWork_Sorket::Sork::Socket();
        NetWork_Sorket::Sork::Bind(listen_sock,port);
        NetWork_Sorket::Sork::Listen(listen_sock,Back_Log);
        epfd=epoll_create(256);
        if(epfd<0){//256无意义->
          std::cerr<<"epoll create error"<<std::endl;
          exit(4);
        }
      }

      void Start(){
        //将listen_sock添加到红黑树中,关心读
        AddEvent(listen_sock,EPOLLIN);
        int timeout=1000;
        
        struct epoll_event fd_events[MAXSIZE];//MAXSIZE不能额大于创建epoll时的size及256
        while(true){
          int num=epoll_wait(epfd,fd_events,MAXSIZE,timeout);
          //内核会将就绪事件依次放入数组中，不会做重复遍历
          if(num>0){
            std::cout<<"epoll wait succeed!"<<std::endl;
            for(int i=0;i<num;i++){
              int sock=fd_events[i].data.fd;
              if(fd_events[i].events&EPOLLIN){
                //读事件就绪
                if(sock==listen_sock){
                  struct sockaddr_in peer;
                  socklen_t len=sizeof(peer);
                  int sock=0;
                  if((sock=accept(listen_sock,(struct sockaddr*)&peer,&len))<0){
                    std::cerr<<"accept error"<<std::endl;
                    continue;
                  }
                  std::cout<<"get a new link"<<std::endl<<"ip: "<<inet_ntoa(peer.sin_addr)<<" port"<<ntohs(peer.sin_port)<<std::endl;
                  AddEvent(sock,EPOLLIN);//先监测读事件就绪情况,只有主动写时才设置EPOLLOUT
                }
                else{
                  char buff[1024];
                  ssize_t size=recv(sock,buff,sizeof(buff)-1,0);//存在数据读不完或粘包问题
                  if(size>0){
                    buff[size]=0;
                    std::cout<<buff<<std::endl;
                  }
                  else{
                    std::cout<<"client close !"<<std::endl;
                    close(sock);
                    DelEvent(sock);
                  }
                }
              }
              else if(fd_events[i].events&EPOLLOUT){
                //写事件就绪
                //......
              }
            }
          }
          else if(num==0){
            std::cout<<"time out"<<std::endl;
          }
          else{
            std::cerr<<"epoll wait error"<<std::endl;
          }
        }
      }

      ~epoll_sever(){
        if(listen_sock>=0){
          close(listen_sock);
        }
        if(epfd>=0){
          close(epfd);
        }
      }
    private:
      void AddEvent(int sock,uint32_t event){
        struct epoll_event ev;
        memset(&ev,0,sizeof(ev));
        ev.events|=event;
        ev.data.fd=sock;
        if(epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev)<0){
          std::cerr<<"epoll ctl error:"<<sock<<std::endl;
        }
      }
      void DelEvent(int sock){
        if(epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr)<0){
          std::cout<<"epoll ctl del error"<<std::endl;
        }
      }
  }; 
}
