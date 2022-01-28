#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include<string>
#include<winSock2.h>

#pragma comment(lib,"WS2_32.lib")//套接字依赖的静态库

using namespace std;

class TcpSocket
{
private:
	SOCKET _userSocket;//套接字
	sockaddr_in _uAddr;
public:
	TcpSocket() :_userSocket(0), _uAddr({ 0 })
	{
		//初始化套接字 
		WSADATA date;
		WORD w = MAKEWORD(2, 0);//版本信息，使用2.0
		if (WSAStartup(w, &date) != 0)
		{
			cout << "初始化套接字失败" << endl;
		}
	}


	//客户端请求操作 客户端 ip+端口
	int Request(const string& ip, int port)
	{
		//创建套接字+初始化ip信息+绑定
		_userSocket = socket(AF_INET, SOCK_STREAM, 0);//ipv4 tcp
		_uAddr.sin_family = AF_INET;
		_uAddr.sin_port = htons(port);//转网络字节序
		_uAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());//转化ip格式
		return connect(_userSocket, (const sockaddr*)&_uAddr, sizeof(_uAddr));
	}

	//读取消息
	string RecvDate(int ReadLen)//要读取的数据长度
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
		WSACleanup();//清理套接字资源
	}
};