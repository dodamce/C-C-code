#include"WinTcpSever.h"

int main()
{
	TcpSocket sever;
	sever.Bind(1500);
	sever.Listen(5);
	cout << "����������" << endl;
	while (1)
	{
		if (sever.Accept() != INVALID_SOCKET)
		{
			cout << sever.GetAddress() << "���ӷ�����" << endl;
			sever.SentMesage("Hello Windows");
		}
	}
	return 0;
}