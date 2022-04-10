#pragma once 

#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<vector>
#include<string>

//设置文件描述符为非阻塞

namespace Util{
  void SetNoBlock(int sock){
    int fd=fcntl(sock,F_GETFL);
    fcntl(sock,F_SETFL,fd|O_NONBLOCK);
  }

  void SplitStr(std::string&in,std::vector<std::string>&buff,std::string gist){
    //asdc|derc|代表两个完整的报文
    while(true){
      size_t pos=in.find(gist);
      if(pos==std::string::npos){
        break;
      }
      std::string ms=in.substr(0,pos);
      buff.push_back(ms);
      in.erase(0,pos+gist.size());//从头开始截取pos+gist.size()个
    }
  }

  void Deserialize(std::string& in,int&x,int&y){
    //in 认为字符串风格为1+1，不考虑错误情况
    int pos=in.find("+");
    x=atoi(in.substr(0,pos).c_str());
    y=atoi(in.substr(pos+1).c_str());//跳过加号
  }
}

