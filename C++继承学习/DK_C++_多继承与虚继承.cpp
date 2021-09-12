#include<iostream>
#include<string>

using namespace std;

class Teacher
{
public:
	Teacher(const string& a, int b)
		:_name(a),_money(b)
	{
		cout << "1 ";//用来验证多继承的构造函数调用顺序
	}
protected:
	string _name;
	int _money;
};

class Student
{
public:
	Student(int number=00000)
		:_number(number)
	{
		cout << "2 ";
	}
protected:
	int _number;
};

class People :public Student, public Teacher//派生类的构造函数顺序为其继承顺序
//此类构造函数调用顺序为先调用Student的构造函数再调用Teacher的构造函数，与其初始化列表的顺序无关
{
public:
	People(int ID,int number,const string&name,int money)
		:Teacher(name,money),Student(number)
	{
		_ID = ID;
		cout << "3 ";
	}
protected:
	int _ID;
};

int main()
{
	People Larry(123,200504,"Larry",1000000);//打印顺序为213，初始化顺序为123，可知与初始化顺序无关
	return 0;
}