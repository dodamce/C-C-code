#pragma once 

#include<iostream>
#include<map>
#include<functional>
#include<pthread.h>

class Task
{
  private:
    int x;int y;char op;
  public:
    Task()=default;
    Task(int _x,int _y,char _op):x(_x),y(_y),op(_op){}

    void Run()//任务处理方法
    {
      std::map<char,std::function<int(int,int)>>opMap=
      {
        {'+',[](int x,int y){return x+y;}},
        {'-',[](int x,int y){return x-y;}},
        {'*',[](int x,int y){return x*y;}},
        {'/',[](int x,int y){return x/y;}},
        {'%',[](int x,int y){return x%y;}}
      };

      double ret=(double)opMap[op](x,y);

      std::cout<<"Thread: ["<<pthread_self()<<"]: "<<x<<op<<y<<" "<<ret<<std::endl;
    }

};
