#include<iostream>

using namespace std;

class Teacher
{
public:
	Teacher(double a=0,double b=0,double c=0)
		:Money(a),TimePay(b),Gift(c)
	{}
	virtual double GetSumMoney()=0;
    double GetMoney()
	{
		return Money;
	}
	double GetTimePay()
	{
		return TimePay;
	}
	double GetGife()
	{
		return Gift;
	}
private:
	double Money;
	double TimePay;
	double Gift;
};

class TackTeacher:public Teacher
{
public:
	TackTeacher(double a=800,double b=20,double c=600)
		:Teacher(a,b,c)
	{}
	double GetSumMoney()
	{
		return GetMoney()+GetTimePay()+GetGife();
	}
};

class LowTeacher:public Teacher
{
public:
	LowTeacher(double a=900,double b=30,double c=700)
		:Teacher(a,b,c)
	{}
	double GetSumMoney()
	{
		return GetMoney()+GetTimePay()+GetGife();
	}
};

class HighTeacher:public Teacher
{
public:
	HighTeacher(double a=1000,double b=40,double c=800)
		:Teacher(a,b,c)
	{}
	double GetSumMoney()
	{
		return GetMoney()+GetTimePay()+GetGife();
	}
};


int main()
{
	Teacher*Pot=new TackTeacher;
	cout<<Pot->GetSumMoney()<<endl;
	Pot=new LowTeacher;
	cout<<Pot->GetSumMoney()<<endl;
	Pot=new HighTeacher();
	cout<<Pot->GetSumMoney()<<endl;
	getchar();
	return 0;
}