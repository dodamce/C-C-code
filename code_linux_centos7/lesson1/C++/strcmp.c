#include<stdio.h>

int MyStrcmp(char*soc,char*des)
{
   while(*soc!='\0'||*des!='\0')
   {
     if(*soc>*des)
     {
       return 1;
     }
     if(*soc<*des)
     {
       return -1;
     }
     soc++;
     des++;
   }
   if(*soc=='\0'&&*des=='\0')
   {
     retrun 0;
   }
}

int main()
{
  char s1[]="hello";
  char s2[]="strcmp";
  int flag=MyStrcmp(s1,s2);
  if(flag)
  {
    printf("s1>s2");
  }
  else if(flag==0)
  {
    printf("s1==s2");
  }
  else
  {
    printf("s1<s2");
  }
  return 0;
}
