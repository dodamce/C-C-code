#include"epoller.h"
#include<stdlib.h>
#include"sock.h"
#include"app_interface.h"
#include"Util.h"

const int Back_Log=5;

void UsrHelp(const char*name){
  std::cout<<"UsrHelp# "<<name<<" +port"<<std::endl;
}

int main(int argc,char*argv[]){
  if(argc!=2){
    UsrHelp(argv[0]);
    exit(5);
  }
  int port=atoi(argv[1]);

  //创建listen sock 
  int listen_sock=NetWork_Socket::Sock::Socket();

  std::cout<<"listen sock="<<listen_sock<<std::endl;

  //设置非阻塞
  Util::SetNoBlock(listen_sock);

  NetWork_Socket::Sock::Bind(listen_sock,port);
  NetWork_Socket::Sock::Listen(listen_sock,Back_Log);

  //调用epollsever事件管理器
  EpollSever::epoller epoll;

  EpollSever::EventItem item;
  item.sock=listen_sock;
  item.Epoller=&epoll;

  //这里只关注读事件，注册回调函数
  item.RegisterCallBack(interface::accepter,nullptr,nullptr);
 
  //将监听套接字托管到epoller，ET模式工作
  epoll.AddEvent(listen_sock,EPOLLIN|EPOLLET,item);

  int timeout=1000;
  while(true){
    epoll.DisPatch(timeout);
  }

  return 0;
}
