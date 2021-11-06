#include"Commmen.c"

int main()
{
  int fd=open(FIFE_NAME,O_WRONLY);//通过写的方式打开管道文件
  if(fd<0)
  {
    perror("open error\n");
    return 1;
  }
  char buff[32]={0};
  while(1)
  {
    printf("Enter String\n");
    buff[0]='\0';//清空字符缓冲区
    ssize_t size=read(0,buff,sizeof(buff));//0为标准输入的文件描述符，读取键盘输入的字符
    if(size>0)
    {
      buff[size]='\0';
      write(fd,buff,strlen(buff)-1);//向管道文件中写入buff数组的数据
    }
    else 
    {
      printf("error wirte\n");
    }
  }
  close(fd);
  return 0;
}


