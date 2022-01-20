#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include"string.h"

using namespace std;

void TestRight()
{
	int x = 10; int y = 20;
	//��ֵ
	10;
	(x + y);
	fmax(x, y);
	int&& r = 10;
	int&& r2 = (x + y);
	int&& t3 = fmax(x, y);//����ʱ����ֵ������������ֵ�ͱ�Ŀ���ȡ��ַ��
	r = 50;
	std::cout << r << std::endl;
	std::cout << &r << std::endl;
}

void Test()
{
	//��ֵ���ÿ�������ֵ
	const int& r = 10 + 20;
	//��ֵ���ò���ֱ������ֵ
	int a = 10;
	//int&& r2 = a;
	int&& r2 = std::move(a);
}

//�ƶ����죬�ƶ���ֵ
void Test2()
{
	My::string s = "Hello";
	My::string s2 = std::move(s);//��s����move��s�������٣���Ҫע��
}

void Fun(int& val) { cout << "��ֵ����" << endl; }
void Fun(int&& val) { cout << "��ֵ����" << endl; }
void Fun(const int& val) { cout << "const ��ֵ����" << endl; }
void Fun(const int&& val) { cout << "const ��ֵ����" << endl; }

//��������
template<class T>
void N_Perfect(T&& val)//val����������ֵ����ֵ,������ת��
{
	Fun(val);//��ֵ�����ú����ȡ����ַ���������Դ���ֵ��Ϊ��ֵ
	cout << &val << endl;
}

void Test3()
{
	N_Perfect(10);
	int a = 20;
	N_Perfect(a);
	N_Perfect(std::move(a));
	const int b = 20;
	N_Perfect(b);
	N_Perfect(std::move(b));
}

template<class T>
void Perfect(T&& val)//val����������ֵ����ֵ,����ת��
{
	Fun(std::forward<T>(val));//����ת����������ֵ����
}

void Test4()
{
	Perfect(10);
	int a = 20;
	Perfect(a);
	Perfect(std::move(a));
	const int b = 20;
	Perfect(b);
	Perfect(std::move(b));
}

//��ֵ�����ٴ���ʱ�����Ի��˻�Ϊ��ֵ

template<class T1, class T2>

auto Fun(T1 t1, T2 t2)->decltype(t1* t2)//auto���ܵ���������ֵ,->ָ������ֵ����
{
	decltype(t1 * t2)ret = t1 * t2;//���ݳ˻����ж�ret������
	cout << typeid(ret).name() << endl;
	return ret;
}


int main()
{
	//TestRight();x
	//Test();
	//Test2();
	//Test3();
	Test4();
	cout << Fun(1, 3) << endl;
	cout << Fun(1.1, 4) << endl;
	return 0;
}