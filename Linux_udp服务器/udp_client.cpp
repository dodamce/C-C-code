#include"udp_client.h"

//udp_client+sever_ip+sever_port

int main(int argc,char*argv[])
{
  if(argc!=3)
  {
    std::cout<<"User:"<<argv[0]<<"sever_ip+sever_port"<<std::endl;
  }
  else 
  {
    std::string ip=argv[1];
    int port=atoi(argv[2]);
    UdpClient*client=new UdpClient(ip,port);
    client->InitUdpClient();
    client->Start();
  }
  return 0;
}
