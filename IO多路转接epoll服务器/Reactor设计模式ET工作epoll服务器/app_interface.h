#pragma once 

#include<iostream>
#include"epoller.h"
#include"Util.h"

namespace interface{

  using namespace EpollSever;

  int recver(EventItem*);
  int sender(EventItem*);
  int error(EventItem*);
  int accepter(EventItem*item){
    std::cout<<"get a new link sock="<< item->sock<<std::endl;
    while(true){
      struct sockaddr_in peer;
      socklen_t len=sizeof(peer);
      int sock=accept(item->sock,(struct sockaddr*)&peer,&len);
      //设置非阻塞
      Util::SetNoBlock(sock);
      if(sock<0){//->
        if(errno==EAGAIN||errno==EWOULDBLOCK){//底层没有连接了
          return 0;
        }
        if(errno==EINTR){
          //读取过程被信号打断
          continue;
        }
        else{
          //读取出错
          return -1;
        }
      }
      else{
        //读取成功,添加到epoller中,并添加这个套接字的注册方法
        EventItem tmp_item;
        tmp_item.sock=sock;
        tmp_item.Epoller=item->Epoller;
        tmp_item.RegisterCallBack(recver,sender,error);
        epoller* tmp_Epoller=item->Epoller;
        tmp_Epoller->AddEvent(sock,EPOLLIN|EPOLLET,tmp_item);
      }
    }

    return 0;
  }

  int recver(EventItem*item){
    //数据读取
    return 0;
  }

  int sender(EventItem*item){
    //发送数据
    return 0;
  }

  int error(EventItem*item){
    //出错
  }
}
