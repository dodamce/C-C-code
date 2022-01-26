#include"udp_sever.h"

//udp + port启动服务

int main(int argc,char*argv[])
{
  if(argc!=2)
  {
    std::cout<<"User:"<<argv[0]<<"+port"<<std::endl;
  }
  else 
  {
    int port=atoi(argv[1]);
    UdpSever*svr=new UdpSever(port);
    svr->InitUdpSever();
    svr->Start();
  }
  return 0;
}
