#include"WinTcpClient.h"

int main()
{
	TcpSocket client;
	client.Request("127.0.0.1",1500);//���ز���
	cout << "�ͻ�����" << endl;
	cout << "sever��" << client.RecvDate(1024) << endl;
	getchar();
}