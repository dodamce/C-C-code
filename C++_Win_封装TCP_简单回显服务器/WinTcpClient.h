#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include<string>
#include<winSock2.h>

#pragma comment(lib,"WS2_32.lib")//�׽��������ľ�̬��

using namespace std;

class TcpSocket
{
private:
	SOCKET _userSocket;//�׽���
	sockaddr_in _uAddr;
public:
	TcpSocket() :_userSocket(0), _uAddr({ 0 })
	{
		//��ʼ���׽��� 
		WSADATA date;
		WORD w = MAKEWORD(2, 0);//�汾��Ϣ��ʹ��2.0
		if (WSAStartup(w, &date) != 0)
		{
			cout << "��ʼ���׽���ʧ��" << endl;
		}
	}


	//�ͻ���������� �ͻ��� ip+�˿�
	int Request(const string& ip, int port)
	{
		//�����׽���+��ʼ��ip��Ϣ+��
		_userSocket = socket(AF_INET, SOCK_STREAM, 0);//ipv4 tcp
		_uAddr.sin_family = AF_INET;
		_uAddr.sin_port = htons(port);//ת�����ֽ���
		_uAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());//ת��ip��ʽ
		return connect(_userSocket, (const sockaddr*)&_uAddr, sizeof(_uAddr));
	}

	//��ȡ��Ϣ
	string RecvDate(int ReadLen)//Ҫ��ȡ�����ݳ���
	{
		char* mess = new char[ReadLen];
		memset(mess, 0, ReadLen);
		recv(_userSocket, mess, ReadLen, 0);
		string ret(mess);
		delete[] mess;
		return ret;
	}

	~TcpSocket()
	{
		closesocket(_userSocket);
		WSACleanup();//�����׽�����Դ
	}
};