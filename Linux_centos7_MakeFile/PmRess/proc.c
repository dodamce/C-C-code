#include"proc.h"

void Cout()
{
  int i=9;
  while(i)
  {
    printf("%2d\r",i);
    fflush(stdout);
    sleep(1);
    i--;
  }
}

void ProcBar()
{
  int i=0;
  char arr[102];
  char tmp[5]="|/-\\";
  memset(arr,'\0',sizeof(arr));
  printf("\n");
  while(i<=100)
  {
    //printf( "\033[1;31;40m 输出红色字符 \033[0m" )
     printf ("[\033[4;33;45m%-100s\033[0m][%d%%][%c]\r",arr,i,tmp[i%4]);
    //printf("[\033[0m\033[1;34m%-100s\033[0m][%d%%][%c]\r",arr,i,tmp[i%4]);
    fflush(stdout);
    usleep(100000);
    arr[i]='=';
    i++;
  }
  printf("\n");
}

