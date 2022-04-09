#pragma once 

#include<iostream>
#include<unistd.h>
#include<fcntl.h>

//设置文件描述符为非阻塞

namespace Util{
  void SetNoBlock(int sock){
    int fd=fcntl(sock,F_GETFL);
    fcntl(sock,fd|O_NONBLOCK);
  }
}

