#include"epoll_sever.h"
#include<stdlib.h>

void UsrHelp(const char*name){
  std::cout<<"UsrHelp# "<<name<<" +port"<<std::endl;
}

int main(int argc,char*argv[]){
  if(argc!=2){
    UsrHelp(argv[0]);
    exit(5);
  }
  int port=atoi(argv[1]);

  EpollSever::epoll_sever*sever=new EpollSever::epoll_sever(port);
  sever->Start();
  return 0;
}
