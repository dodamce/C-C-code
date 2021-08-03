#include<stdio.h>
//#define DOS 1 


int main()
{
#if DOS
  printf("hello linux\n");
#else 
  printf("hello Windows\n");
#endif

 /*
  printf("hello linux\n");
  printf("hello linux2\n");
  */
  return 0;
}
