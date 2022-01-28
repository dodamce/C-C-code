#include"WinTcpClient.h"

int main()
{
	TcpSocket client;
	client.Request("127.0.0.1",1500);//本地测试
	cout << "客户启动" << endl;
	cout << "sever：" << client.RecvDate(1024) << endl;
	getchar();
}