#pragma once 

#include<iostream>
#include<pthread.h>
#include<queue>

#define NUM 5

template<typename Task>
class ThreadPool
{
  private:
    std::queue<Task> _task_queue;//临界资源
    pthread_mutex_t _lock;
    int _thread_num;
    pthread_cond_t _cond;
  public:
   ThreadPool(int Num=NUM):_thread_num(Num){
     pthread_mutex_init(&_lock,nullptr);
     pthread_cond_init(&_cond,nullptr);
   }

   bool IsEmpty(){return _task_queue.empty();}

   static void*Routine(void*arg)//静态函数无隐含的this指针
   {
     pthread_detach(pthread_self());
     ThreadPool<Task>*self=(ThreadPool<Task>*)arg;
     while(true)
     {
       pthread_mutex_lock(&(self->_lock));
       while(self->IsEmpty())//循环检测临界资源是否就绪
       {
         //休眠
         pthread_cond_wait(&(self->_cond),&(self->_lock));
       }
       //任务队列有任务
       Task t;
       self->Pop(t);
       pthread_mutex_unlock(&(self->_lock));
       //解锁后处理任务
       t.Run();
     }
   }

   void Push(const Task&in)//外部添加任务
   {
     pthread_mutex_lock(&_lock);
     _task_queue.push(in);
     //唤醒一个线程
     pthread_cond_signal(&_cond);
     pthread_mutex_unlock(&_lock);
   }

   void Pop(Task&out)//线程获取任务
   {
     out=_task_queue.front();
     _task_queue.pop();
   }

   ~ThreadPool(){
     pthread_mutex_destroy(&_lock);
     pthread_cond_destroy(&_cond);
   }

   void InitThreadPool()
   {
     pthread_t tid;
     for(int i=0;i<_thread_num;i++)
     {
       pthread_create(&tid,nullptr,Routine,this);//为了避免传参时C++传this指针，在线程执行方法上带static。传参数时将this指针传到线程执行方法上。 
     }
     
   }
};
