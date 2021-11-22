#include<iostream>
#include<stdio.h>
using namespace std;

class Paper
{
public:
	void fun()
	{
		cout << "这是一张纸" << endl;
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
		printf("名称：%s 功能：写作业\n",_name);
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
		printf("名称：%s 功能：浏览阅读\n", _name);
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
		printf("名称：%s 作业：%s 功能：学生练习合集\n",Book::GetName(),HomeWork::GetName());
	}
};

//单元测试
void Test1()
{
	HomeWork s;
	s.fun();
}

void Test2()
{
	Book s("新华字典");
	s.fun();
}

void Test3()
{
	WorkBook s;
	s.fun();
	WorkBook s2("暑假作业", "语文作业");
	s2.fun();
}

int main()
{
	/*Test1();
	Test2();
	Test3();*/
	WorkBook work("寒假作业","数学作业");
	cout << work.Book::GetName() << "->" << work.HomeWork::GetName() << endl;
	work.fun();
	work.Book::fun();
	work.HomeWork::fun();
	return 0;
}