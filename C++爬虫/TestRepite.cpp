#define _CRT_SECURE_NO_WARNINGS 1

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include<winsock2.h>
#include<string>
#include<queue>
#include<map>
#include<regex>
#include<fstream>

//http://www.netbian.com/s/meinvmm/

#pragma comment(lib,"WS2_32.lib")

#include<windows.h>

using namespace std;

map<string, int> g_map;

//存放主机名
char g_zhuji[256] = { 0 };
//存放主机后的路径
char g_path[256] = { 0 };
//服务器socket
SOCKET g_socket;
//存放图片地址的容器
vector<string> photoAddr;
//存放网页地址的容器
vector<string> htmlAddr;

/*
用户输入网址，获取源代码，分析网络图片地址
使用http协议将图片下载下来，循环链接新的网址
*/

void AnylizeAddr(char* buff)
{
	char _buff[256] = { 0 };
	strcpy(_buff, buff);
	//略过前7个
	char* p = strstr(_buff, "http://");
	if (p == nullptr)
	{
		return;
	}
	else
	{
		p += 7;
	}
	sscanf(p, "%[^/]%s", g_zhuji, g_path);
	cout << "主机：" << g_zhuji << "路径：" << g_path << endl;

}

void ConectAddr()
{
	//1 获取协议版本号
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		printf("请求版本号失败！\n");
		return;
	}
	printf("请求版本号成功！\n");
	//2 创建socket
	g_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == g_socket) {
		printf("创建socket失败!\n");
		return;
	}
	printf("创建socket成功!\n");
	//3 创建协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET; //必须和socket函数第一个参数一致
	//4 绑定
	int r = bind(g_socket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("绑定失败!\n");
		return;
	}
	printf("绑定成功！\n");
	//5 拿到主机ip地址
	struct hostent* p = gethostbyname(g_zhuji);//192.168.0.44    ipv4
	if (NULL == p) {
		printf("获取主机地址失败!\n");
		return;
	}
	printf("获取主机地址成功!\n");

	memcpy(&addr.sin_addr, p->h_addr, 4);	//把主机地址放入协议地址族中
	addr.sin_port = htons(80);				//设置主机端口号   浏览器端口号一般为80

	//6 连接服务器
	r = connect(g_socket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("连接服务器失败!\n");
		return;
	}
	printf("连接服务器成功！\n");
	//7 通信：发送获取源代码请求

	//请求信息
	string reqInfo = "GET " + (string)g_path + " HTTP/1.1\r\nHost:" +
		(string)g_zhuji + "\r\nConnection:Close\r\n\r\n";
	//发送请求信息到服务器
	r = send(g_socket, reqInfo.c_str(), reqInfo.size(), NULL);
	if (r > 0) {
		printf("发送请求信息成功!\n");
	}
	else {
		printf("发送请求信息失败，失败原因：%d\n", WSAGetLastError());
	}
}

void GetImage(string& allHtml)
{
	smatch mat;//匹配对象
	regex patten("src=\"(.*?\\.jpg)\"");
	string::const_iterator begin = allHtml.begin();
	string::const_iterator end = allHtml.end();
	while (regex_search(begin, end, mat, patten))//必须是const迭代器
	{
		string mes(mat[1].first, mat[1].second);
		photoAddr.push_back(mes);
		cout << "找到图片:" << mes << endl;
		begin = mat[0].second;//改变起始位置
	}
}

void GetAddr(string& allHtml)
{
	smatch mat;//匹配对象
	regex patten("href=\"(http://[^\\s,\"]+)\"");
	string::const_iterator begin = allHtml.begin();
	string::const_iterator end = allHtml.end();
	while (regex_search(begin, end, mat, patten))//必须是const迭代器
	{
		string mes(mat[1].first, mat[1].second);
		htmlAddr.push_back(mes);
		cout << "找到网址:" << mes << endl;
		begin = mat[0].second;//改变起始位置
	}
}

void GetHtml()
{
	string allHtml;
	char buff[1024] = { 0 };
	int size = 0;
	while (true)
	{
		size = recv(g_socket, buff, sizeof(buff) - 1, NULL);
		if (size > 0)
		{
			buff[size] = '\0';
			allHtml += buff;
		}
		else
		{
			break;
		}
	}
	//cout << allHtml << endl;
	//从网页源代码中获取网址以及图片链接
	GetImage(allHtml);
	GetAddr(allHtml);
}

void getAddr(string& allHtml) {
	smatch mat;//专门用作匹配的
	//href="http://img.chinaz.com/max-templates/passport/styles/topbar.css"
	regex pattern("href=\"(http://[^\\s,\"]+)\"");

	string::const_iterator start = allHtml.begin();//字符串起始位置
	string::const_iterator end = allHtml.end();//字符串结束位置

	//regex_search:查找函数
	while (regex_search(start, end, mat, pattern)) {
		string msg(mat[1].first, mat[1].second);
		htmlAddr.push_back(msg);
		cout << "找到网页地址：" << msg << endl;
		start = mat[0].second;//改变起始位置
	}
}

//下载图片到本地
void saveImage(string& photoAddr) {
	//1 解析图片地址
	char buff[256];
	memset(buff, 0, 256);
	strcpy(buff, photoAddr.c_str());
	AnylizeAddr(buff);
	//2 连接服务器
	//3 发送下载图片请求
	ConectAddr();
	//4 本地创建图片文件
	//4.1 得到图片文件名
	string photoName;
	photoName.resize(photoAddr.size());

	char ch;
	int j = 0;
	for (int i = 0; i < photoAddr.length(); i++) {
		ch = photoAddr[i];
		// '\0'  '\n' '\t' '\r' '\\' '\"'
		if (ch != '\\' && ch != '/' && ch != ':' && ch != '*' && ch != '?' &&
			ch != '"' && ch != '<' && ch != '>' && ch != '|') {
			photoName[j++] = ch;
		}//这些符号不可以做文件名
	}

	photoName = "./images/" + photoName.substr(0, j);//文件夹位置路径
	//4.2 创建图片文件
	fstream file;
	file.open(photoName, ios::out | ios::binary);//二进制写

	//5 接收发送过来的图片信息并写入图片文件中
	int r;
	char tempBuff[1024] = { 0 };

	//排除掉文件头的"\r\n\r\n"
	r = recv(g_socket, tempBuff, 1023, NULL);
	char* p = strstr(tempBuff, "\r\n\r\n");
	file.write(p + strlen("\r\n\r\n"), r - (p - tempBuff) - strlen("\r\n\r\n"));

	while (true) {
		r = recv(g_socket, tempBuff, 1023, NULL);
		if (r > 0) {
			file.write(tempBuff, r);
		}
		else {
			break;
		}

	}
	//6 保存关闭
	file.close();
}
void SnapJpg(const char*addr)//爬取jpj图片
{
	//解析域名链接服务器
	queue<string>q;//保存网址
	q.push(addr);
	while (!q.empty())//广度优先变量
	{
		string frontAddr = q.front();
		q.pop();
		//利用map容器解决网址重复问题，将域名保存到map中
		g_map[frontAddr]++;
		//得到域名
		char buff[256];
		memset(buff, 0, sizeof(buff));
		strcpy(buff, frontAddr.c_str());
		AnylizeAddr(buff);
		//链接服务器
		ConectAddr();
		//得到源代码
		GetHtml();
		vector<string>::iterator ptr;
		for (ptr = htmlAddr.begin(); ptr != htmlAddr.end(); ptr++)
		{
			if (0 == g_map[*ptr])//说明这个网址没有重复
			{
				q.push(*ptr);
			}
		}
		htmlAddr.clear();
		//下载图片
		for (ptr = photoAddr.begin(); ptr != photoAddr.end(); ptr++)
		{
			saveImage(*ptr);
		}
		photoAddr.clear();
	}
}

int main()
{
	string addr;
	cout << "输入网址" << endl;
	cin >> addr;
	//创建文件夹
	CreateDirectory(".//images",nullptr);
	SnapJpg(addr.c_str());
	return 0;
}