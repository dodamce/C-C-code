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

	//处理对端套接字
	SOCKET _clientSocket;
	sockaddr_in _cAddr;
	int len;//结构体长度
public:
	//服务器操作
	TcpSocket() :_userSocket(0), _clientSocket(0), _uAddr({ 0 }), _cAddr({ 0 }), len(0)
	{
		//初始化套接字 
		WSADATA date;
		WORD w = MAKEWORD(2, 0);//版本信息，使用2.0
		if (WSAStartup(w, &date) != 0)
		{
			cout << "初始化套接字失败" << endl;
		}
	}

	int Bind(int port)//服务器绑定 端口+ip
	{
		//创建套接字+初始化ip信息+绑定
		_userSocket = socket(AF_INET, SOCK_STREAM, 0);//ipv4 tcp
		_uAddr.sin_family = AF_INET;
		_uAddr.sin_port = htons(port);//转网络字节序
		_uAddr.sin_addr.S_un.S_addr = INADDR_ANY;//任何ip
		//绑定
		return bind(_userSocket, (const sockaddr*)&_uAddr, sizeof(_uAddr));//失败返回-1
	}

	int Listen(int num)
	{
		return listen(_userSocket, num);
	}

	SOCKET Accept()//服务器接受客户端，返回客户端的套接字
	{
		len = sizeof(_cAddr);
		_clientSocket = accept(_userSocket,(sockaddr*)&_cAddr,&len);//输出型参数
		//cout<<WSAGetLastError();//获取错误信息
		return _clientSocket;
	}

	//打印客户端ip地址
	string GetAddress()
	{
		return inet_ntoa(_cAddr.sin_addr);
	}

	//发送消息
	SOCKET SentMesage(string meg)
	{
		return send(_clientSocket, meg.c_str(), meg.size() + 1, 0);//多发送一个'\0'
	}


	~TcpSocket()
	{
		closesocket(_userSocket);
		closesocket(_clientSocket);
		WSACleanup();//清理套接字资源
	}
};