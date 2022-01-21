#include<iostream>
#include<string>
#include<bitset>

using namespace std;

void ShowListA() {}

template<class T, class ...Args>//ģ��ɱ����
void ShowListA(const T& val, Args...args)
{
	//�ݹ�չ��������
	cout << val << endl;
	ShowListA(args...);//���0��������ʱ�򣬵����޲κ��������ݹ�
}

template<class ...Args>
void ShowArgs(Args...args)
{
	cout << "Tips����������Ϊ " << sizeof...(args) << endl;//��ӡ��������
	ShowListA(args...);//չ��������
}


template<class T>
void PrintArgs(const T& t)
{
	cout << t << endl;
}

void ShowListCom() {};
//���ű��ʽ�Ƶ�ģ�����
template<class...Args>
void ShowListCom(Args...args)
{
	//�б��ʼ��
	int arr[] = { (PrintArgs(args),0)... };//�����СΪ����������ǰ����args֮�������������ͬ
//չ��Ϊ(PrintArgs(a1),0),(PrintArgs(a2),0)(PrintArgs(a3),0),�����������0�����Կ��Էŵ�������
	cout << endl;

}

int main()
{
	ShowListCom(1, 'A', string("ABX"));
	ShowListCom();
	ShowListCom(1);
	ShowListCom(1, "Hello");
	return 0;
}