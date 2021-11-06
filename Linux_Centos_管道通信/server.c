#include"Commmen.c"

int main()
{
  if(mkfifo(FIFE_NAME,0664)<0)//创建管道文件
  {
    perror("make fifo error\n");
    return 1;
  }

  int fd=open(FIFE_NAME,O_RDONLY);//打开管道文件，只读取
  if(fd<0)
  {
    perror("open error\n");
    return 2;
  }
  char buff[32]={0};
  while(1)
  {
    buff[0]='\0';//每次情况字符串
    ssize_t size=read(fd,buff,sizeof(buff)-1);//读取字符串放到buff缓冲区中,空余一个空间存放'\0'
    if(size>0)//读取成功
    {
      buff[size]='\0';//为字符串添加'\0'
      printf("client:%s\n",buff);
    }
    else if(size==0)//管道关闭
    {
      printf("End Client\n");
      break;
    }
    else //读取失败
    {
      perror("read error\n");
      break;
    }
  }

  close(fd);
  return 0;
}
