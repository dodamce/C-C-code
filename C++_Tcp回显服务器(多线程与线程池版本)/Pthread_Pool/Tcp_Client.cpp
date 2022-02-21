#include"Tcp_Client.h"

// ./Tcp_Client +ip +port

void User(char*name)
{
  std::cout<<name<<" + sever_ip + sever_port"<<std::endl;
}

int main(int argc,char*argv[])
{
  if(argc!=3){
    User(argv[0]);
    exit(-1);
  }

  TcpClient*Client=new TcpClient(argv[1],atoi(argv[2]));
  Client->InitClient();

  Client->Start();
  return 0;
}
