#include<iostream>
#include<string>

using namespace std;

class Father
{
public:
	Father()
	{
		FirstName = "*";
		SecondName = "匿名";
	}
	Father(const string& first,const string&second)
		:FirstName(first),SecondName(second)
	{}

	void Print()
	{
		cout << FirstName << SecondName << endl;
	}
protected:
	string FirstName;
	string SecondName;
};

class Son:public Father
{
public:
	Son(const string& SonS, const string& FarF, const string& FarS)
		:Father(FarF, FarS)//基类必须用初始化列表调用其构造函数初始化，派生类的成员都可以初始化
	{
		this->SonSecondName = SonS;
	}
	Son()
	{
		SonSecondName = "匿名";
	}

	//当基类与派生类函数相同时，默认对象为谁调用那个对象的函数，特殊情况需要用作用域符指定指定
	void Print()
	{
		cout << FirstName << SonSecondName << endl;
	}

protected:
	string SonSecondName;
};

int main()
{
	Son boy("二狗","李","二涛");
	boy.Print();//调用Son对象的Print函数
	//指定调用Father对象的Print函数
	boy.Father::Print();//调用Father对象的Print函数

	//测试默认构造函数
	Son boy2;
	boy2.Print();
	boy2.Father::Print();
	return 0;
}