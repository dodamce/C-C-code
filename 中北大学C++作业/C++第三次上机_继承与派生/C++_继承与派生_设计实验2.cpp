#include<iostream>
#include<stdio.h>
using namespace std;

class Paper
{
public:
	void fun()
	{
		cout << "����һ��ֽ" << endl;
	}
};

class HomeWork :virtual public Paper
{
public:
	HomeWork(const char* s="*****")
	{
		_name = s;
	}
	void fun()
	{
		printf("���ƣ�%s ���ܣ�д��ҵ\n",_name);
	}
	const char* GetName()
	{
		return _name;
	}
private:
	const char* _name;
};

class Book :virtual public Paper
{
public:
	Book(const char* s="*****")
	{
		_name = s;
	}
	void fun()
	{
		printf("���ƣ�%s ���ܣ�����Ķ�\n", _name);
	}
	const char* GetName()
	{
		return _name;
	}
private:
	const char* _name;
};

class WorkBook :public HomeWork, public Book
{
public:
	WorkBook(const char*BookName="*****", const char* WorkName="*****")
		:HomeWork(WorkName),Book(BookName)
	{}
	void fun()
	{
		printf("���ƣ�%s ��ҵ��%s ���ܣ�ѧ����ϰ�ϼ�\n",Book::GetName(),HomeWork::GetName());
	}
};

//��Ԫ����
void Test1()
{
	HomeWork s;
	s.fun();
}

void Test2()
{
	Book s("�»��ֵ�");
	s.fun();
}

void Test3()
{
	WorkBook s;
	s.fun();
	WorkBook s2("�����ҵ", "������ҵ");
	s2.fun();
}

int main()
{
	/*Test1();
	Test2();
	Test3();*/
	WorkBook work("������ҵ","��ѧ��ҵ");
	cout << work.Book::GetName() << "->" << work.HomeWork::GetName() << endl;
	work.fun();
	work.Book::fun();
	work.HomeWork::fun();
	return 0;
}