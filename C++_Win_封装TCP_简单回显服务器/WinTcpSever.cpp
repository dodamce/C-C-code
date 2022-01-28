#include"WinTcpSever.h"

int main()
{
	TcpSocket sever;
	sever.Bind(1500);
	sever.Listen(5);
	cout << "服务器启动" << endl;
	while (1)
	{
		if (sever.Accept() != INVALID_SOCKET)
		{
			cout << sever.GetAddress() << "连接服务器" << endl;
			sever.SentMesage("Hello Windows");
		}
	}
	return 0;
}