#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
  int fd[2]={0};
  if(pipe(fd)<0)
  {
    perror("pipe error\n");
  }
  pid_t id=fork();
  if(id==0)
  {
    //child
    close(fd[0]);//子进程关闭读端
    const char* Str="Hello Linux";
    for(int i=0;i<10;i++)
    {
      write(fd[1],Str,strlen(Str));//向管道写入数据
      sleep(1);
    }
    close(fd[1]);
    exit(0);
  }
  //father
  close(fd[1]);
  char buff[32]={0};
  while(1)
  {
    ssize_t ReadSize=read(fd[0],buff,sizeof(buff));
    if(ReadSize>0)//读取到数据
    {
      buff[ReadSize]='\0';//补充字符串接受的标准
      printf("receive:%s\n",buff);
    }
    else if(ReadSize==0)//读取结束
    {
      printf("read end!\n");
      break;
    }
    else //读取失败
    {
      perror("read error!\n");
      break;
    }
  }
  waitpid(id,NULL,0);//父进程阻塞式等待
  return 0;
}
