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

//���������
char g_zhuji[256] = { 0 };
//����������·��
char g_path[256] = { 0 };
//������socket
SOCKET g_socket;
//���ͼƬ��ַ������
vector<string> photoAddr;
//�����ҳ��ַ������
vector<string> htmlAddr;

/*
�û�������ַ����ȡԴ���룬��������ͼƬ��ַ
ʹ��httpЭ�齫ͼƬ����������ѭ�������µ���ַ
*/

void AnylizeAddr(char* buff)
{
	char _buff[256] = { 0 };
	strcpy(_buff, buff);
	//�Թ�ǰ7��
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
	cout << "������" << g_zhuji << "·����" << g_path << endl;

}

void ConectAddr()
{
	//1 ��ȡЭ��汾��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		printf("����汾��ʧ�ܣ�\n");
		return;
	}
	printf("����汾�ųɹ���\n");
	//2 ����socket
	g_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == g_socket) {
		printf("����socketʧ��!\n");
		return;
	}
	printf("����socket�ɹ�!\n");
	//3 ����Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET; //�����socket������һ������һ��
	//4 ��
	int r = bind(g_socket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("��ʧ��!\n");
		return;
	}
	printf("�󶨳ɹ���\n");
	//5 �õ�����ip��ַ
	struct hostent* p = gethostbyname(g_zhuji);//192.168.0.44    ipv4
	if (NULL == p) {
		printf("��ȡ������ַʧ��!\n");
		return;
	}
	printf("��ȡ������ַ�ɹ�!\n");

	memcpy(&addr.sin_addr, p->h_addr, 4);	//��������ַ����Э���ַ����
	addr.sin_port = htons(80);				//���������˿ں�   ������˿ں�һ��Ϊ80

	//6 ���ӷ�����
	r = connect(g_socket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("���ӷ�����ʧ��!\n");
		return;
	}
	printf("���ӷ������ɹ���\n");
	//7 ͨ�ţ����ͻ�ȡԴ��������

	//������Ϣ
	string reqInfo = "GET " + (string)g_path + " HTTP/1.1\r\nHost:" +
		(string)g_zhuji + "\r\nConnection:Close\r\n\r\n";
	//����������Ϣ��������
	r = send(g_socket, reqInfo.c_str(), reqInfo.size(), NULL);
	if (r > 0) {
		printf("����������Ϣ�ɹ�!\n");
	}
	else {
		printf("����������Ϣʧ�ܣ�ʧ��ԭ��%d\n", WSAGetLastError());
	}
}

void GetImage(string& allHtml)
{
	smatch mat;//ƥ�����
	regex patten("src=\"(.*?\\.jpg)\"");
	string::const_iterator begin = allHtml.begin();
	string::const_iterator end = allHtml.end();
	while (regex_search(begin, end, mat, patten))//������const������
	{
		string mes(mat[1].first, mat[1].second);
		photoAddr.push_back(mes);
		cout << "�ҵ�ͼƬ:" << mes << endl;
		begin = mat[0].second;//�ı���ʼλ��
	}
}

void GetAddr(string& allHtml)
{
	smatch mat;//ƥ�����
	regex patten("href=\"(http://[^\\s,\"]+)\"");
	string::const_iterator begin = allHtml.begin();
	string::const_iterator end = allHtml.end();
	while (regex_search(begin, end, mat, patten))//������const������
	{
		string mes(mat[1].first, mat[1].second);
		htmlAddr.push_back(mes);
		cout << "�ҵ���ַ:" << mes << endl;
		begin = mat[0].second;//�ı���ʼλ��
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
	//����ҳԴ�����л�ȡ��ַ�Լ�ͼƬ����
	GetImage(allHtml);
	GetAddr(allHtml);
}

void getAddr(string& allHtml) {
	smatch mat;//ר������ƥ���
	//href="http://img.chinaz.com/max-templates/passport/styles/topbar.css"
	regex pattern("href=\"(http://[^\\s,\"]+)\"");

	string::const_iterator start = allHtml.begin();//�ַ�����ʼλ��
	string::const_iterator end = allHtml.end();//�ַ�������λ��

	//regex_search:���Һ���
	while (regex_search(start, end, mat, pattern)) {
		string msg(mat[1].first, mat[1].second);
		htmlAddr.push_back(msg);
		cout << "�ҵ���ҳ��ַ��" << msg << endl;
		start = mat[0].second;//�ı���ʼλ��
	}
}

//����ͼƬ������
void saveImage(string& photoAddr) {
	//1 ����ͼƬ��ַ
	char buff[256];
	memset(buff, 0, 256);
	strcpy(buff, photoAddr.c_str());
	AnylizeAddr(buff);
	//2 ���ӷ�����
	//3 ��������ͼƬ����
	ConectAddr();
	//4 ���ش���ͼƬ�ļ�
	//4.1 �õ�ͼƬ�ļ���
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
		}//��Щ���Ų��������ļ���
	}

	photoName = "./images/" + photoName.substr(0, j);//�ļ���λ��·��
	//4.2 ����ͼƬ�ļ�
	fstream file;
	file.open(photoName, ios::out | ios::binary);//������д

	//5 ���շ��͹�����ͼƬ��Ϣ��д��ͼƬ�ļ���
	int r;
	char tempBuff[1024] = { 0 };

	//�ų����ļ�ͷ��"\r\n\r\n"
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
	//6 ����ر�
	file.close();
}
void SnapJpg(const char*addr)//��ȡjpjͼƬ
{
	//�����������ӷ�����
	queue<string>q;//������ַ
	q.push(addr);
	while (!q.empty())//������ȱ���
	{
		string frontAddr = q.front();
		q.pop();
		//����map���������ַ�ظ����⣬���������浽map��
		g_map[frontAddr]++;
		//�õ�����
		char buff[256];
		memset(buff, 0, sizeof(buff));
		strcpy(buff, frontAddr.c_str());
		AnylizeAddr(buff);
		//���ӷ�����
		ConectAddr();
		//�õ�Դ����
		GetHtml();
		vector<string>::iterator ptr;
		for (ptr = htmlAddr.begin(); ptr != htmlAddr.end(); ptr++)
		{
			if (0 == g_map[*ptr])//˵�������ַû���ظ�
			{
				q.push(*ptr);
			}
		}
		htmlAddr.clear();
		//����ͼƬ
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
	cout << "������ַ" << endl;
	cin >> addr;
	//�����ļ���
	CreateDirectory(".//images",nullptr);
	SnapJpg(addr.c_str());
	return 0;
}