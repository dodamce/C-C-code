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

	//����Զ��׽���
	SOCKET _clientSocket;
	sockaddr_in _cAddr;
	int len;//�ṹ�峤��
public:
	//����������
	TcpSocket() :_userSocket(0), _clientSocket(0), _uAddr({ 0 }), _cAddr({ 0 }), len(0)
	{
		//��ʼ���׽��� 
		WSADATA date;
		WORD w = MAKEWORD(2, 0);//�汾��Ϣ��ʹ��2.0
		if (WSAStartup(w, &date) != 0)
		{
			cout << "��ʼ���׽���ʧ��" << endl;
		}
	}

	int Bind(int port)//�������� �˿�+ip
	{
		//�����׽���+��ʼ��ip��Ϣ+��
		_userSocket = socket(AF_INET, SOCK_STREAM, 0);//ipv4 tcp
		_uAddr.sin_family = AF_INET;
		_uAddr.sin_port = htons(port);//ת�����ֽ���
		_uAddr.sin_addr.S_un.S_addr = INADDR_ANY;//�κ�ip
		//��
		return bind(_userSocket, (const sockaddr*)&_uAddr, sizeof(_uAddr));//ʧ�ܷ���-1
	}

	int Listen(int num)
	{
		return listen(_userSocket, num);
	}

	SOCKET Accept()//���������ܿͻ��ˣ����ؿͻ��˵��׽���
	{
		len = sizeof(_cAddr);
		_clientSocket = accept(_userSocket,(sockaddr*)&_cAddr,&len);//����Ͳ���
		//cout<<WSAGetLastError();//��ȡ������Ϣ
		return _clientSocket;
	}

	//��ӡ�ͻ���ip��ַ
	string GetAddress()
	{
		return inet_ntoa(_cAddr.sin_addr);
	}

	//������Ϣ
	SOCKET SentMesage(string meg)
	{
		return send(_clientSocket, meg.c_str(), meg.size() + 1, 0);//�෢��һ��'\0'
	}


	~TcpSocket()
	{
		closesocket(_userSocket);
		closesocket(_clientSocket);
		WSACleanup();//�����׽�����Դ
	}
};