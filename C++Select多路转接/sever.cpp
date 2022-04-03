#include"sever.h"
#include<string>
#include<iostream>
#include<stdlib.h>

//  ./sever port

static void usrHelp(char*name){
  std::cout<<"UsrHelp: "<<name<<"+port "<<std::endl;
}

int main(int argc,char*argv[]){
  if(argc!=2){
    usrHelp(argv[0]);
    exit(-3);
  }
  Select::SelectSever*sever=new Select::SelectSever(atoi(argv[1]));
  sever->InitSever();
  sever->Start();
  return 0;
}
