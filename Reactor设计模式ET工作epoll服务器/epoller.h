#pragma once

#include"sock.h"
#include<sys/epoll.h>
#include<string>
#include<unordered_map>

namespace EpollSever{

#define MAXSIZE 64

  class epoller;
  class EventItem;

  typedef int(*call_back)(EventItem*);//函数指针回调函数 const& 输入 *(指针)输出 &输入输出

  class EventItem{
    public:
      int sock=0;
      //回指epoll模型
      epoller* Epoller=nullptr;
      //回调函数，用来进行数据处理
      call_back recv_hander=nullptr;
      call_back send_hander=nullptr;
      call_back error_hander=nullptr;

      //为了保证数据读取完毕，需要定义缓冲区
      std::string inbuff;//输入缓冲区
      std::string outbuff;//发送缓冲区

      void RegisterCallBack(call_back _recv,call_back _send,call_back _error){//管理回调函数，删除回调函数，只需要将参数设置为nullpt
        recv_hander=_recv;
        send_hander=_send;
        error_hander=_error;
      }

  };

  class epoller{
    private:
      int epfd;
      std::unordered_map<int,EventItem> event_item;//sock映射到EventItem,每个sock都有自己独立的缓冲区和处理方法
    public:
      epoller(){
        epfd=epoll_create(256);
        if(epfd<0){//256无意义->
          std::cerr<<"epoll create error"<<std::endl;
          exit(4);
        }
        std::cout<<"creat epoll fd="<<epfd<<std::endl;
      }

      void DisPatch(int timeout){// 如果底层特定事件就绪，就把特定事件分派给回调函数统一处理，称为事件分派器
        struct epoll_event fd_events[MAXSIZE];//MAXSIZE不能额大于创建epoll时的size及256
        int num=epoll_wait(epfd,fd_events,MAXSIZE,timeout);
        //内核会将就绪事件依次放入数组中，不会做重复遍历
        
        //std::cout<<"就绪事件数："<<num<<std::endl;
        for(int i=0;i<num;i++){
          int sock=fd_events[i].data.fd;
          if((fd_events[i].events&EPOLLERR)||(fd_events[i].events&EPOLLHUP)){
            //对端异常或者连接断开->
            if(event_item[sock].error_hander!=nullptr){
              //将事件设置为读写关心
              fd_events[i].events=EPOLLIN|EPOLLOUT;
              event_item[sock].error_hander(&event_item[sock]);
            }
          }
          if(fd_events[i].events&EPOLLIN){
            //读事件就绪
            if(event_item[sock].recv_hander!=nullptr){//读回调函数存在
              event_item[sock].recv_hander(&event_item[sock]);//这个套接字独有的缓存区。
            }
          }
          if(fd_events[i].events&EPOLLOUT){
            //写事件就绪
            if(event_item[sock].send_hander!=nullptr){
              event_item[sock].send_hander(&event_item[sock]);
            }
          }
        }
      }

      ~epoller(){
        if(epfd>=0){
          close(epfd);
        }
      }
    
      void AddEvent(int sock,uint32_t event,EventItem&item){
        struct epoll_event ev;
        memset(&ev,0,sizeof(ev));
        ev.events|=event;
        ev.data.fd=sock;
        if(epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev)<0){
          std::cerr<<"epoll ctl error:"<<sock<<std::endl;
        } 
        else{
        //  std::cout<<"add sock "<<item.sock<<std::endl;
          event_item.insert(std::make_pair(sock,item));
        }
      }

      void DelEvent(int sock){
        if(epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr)<0){
          std::cout<<"epoll ctl del error"<<std::endl;
        }
        std::cout<<"remove sock "<<sock<<std::endl;
        event_item.erase(sock);
      }

      void EnableReadWrite(int sock,bool read,bool write){//之前没有关心过套接字的写，需要套接字写时调用这个接口修改成写即可
        //修改让epoll关注这个套接字的读写->
        struct epoll_event event;
        event.data.fd=sock;
        event.events=(read==true?EPOLLIN:0)|(write==true?EPOLLOUT:0)|EPOLLET;//ET工作模式选择读写
        if(epoll_ctl(epfd,EPOLL_CTL_MOD,sock,&event)<0){
          std::cerr<<"epoll ctl mod error ,sock:"<<sock<<std::endl;
        }
      }
  }; 
}
