#include<iostream>
#include<string>

using namespace std;

class Teacher
{
public:
	Teacher(const string& a, int b)
		:_name(a),_money(b)
	{
		cout << "1 ";//������֤��̳еĹ��캯������˳��
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

class People :public Student, public Teacher//������Ĺ��캯��˳��Ϊ��̳�˳��
//���๹�캯������˳��Ϊ�ȵ���Student�Ĺ��캯���ٵ���Teacher�Ĺ��캯���������ʼ���б��˳���޹�
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
	People Larry(123,200504,"Larry",1000000);//��ӡ˳��Ϊ213����ʼ��˳��Ϊ123����֪���ʼ��˳���޹�
	return 0;
}