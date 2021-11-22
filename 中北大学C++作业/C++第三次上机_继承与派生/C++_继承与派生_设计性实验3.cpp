#include<iostream>

using namespace std;

class Account
{
public:
	Account(double number=0.0)
		:balance(number)
	{}

	void credit(double number)
	{
		balance += number;
	}

	void debit(double number)
	{
		balance -= number;
	}
	double Get_balance()
	{
		return balance;
	}
private:
	double balance;
};

class SavingAccout :public Account
{
public:
	SavingAccout(double number = 0.0, double accrual = 0.01)
		:Account(number),interest(accrual)
	{}
	double CalculateInterest()
	{
		return this->Get_balance() * interest;
	}
	double Get_interest()
	{
		return interest;
	}
private:
	double interest;
};

class CheckingAccout :public Account
{
public:
	CheckingAccout(double number = 0.0, double take_out = 0.0)
		:Account(number-take_out),exchange(take_out)
	{}
	bool debit()
	{
		return exchange > 0.0;
	}
	double Get_exchange()
	{
		return exchange;
	}
private:
	double exchange;
};

//单元测试
void Test1()
{
	Account s(1000);
	cout << s.Get_balance() << endl;
	s.credit(100);
	cout << s.Get_balance() << endl;
	s.debit(50);
	cout << s.Get_balance() << endl;
}

void Test2()
{
	SavingAccout s(1000, 0.038);
	cout << s.CalculateInterest() << endl;
	s.credit(100);
	cout << s.CalculateInterest() << endl;
	s.debit(200);
	cout << s.CalculateInterest() << endl;
	cout << s.Get_balance() << " " << s.Get_interest() << endl;
}

void Test3()
{
	CheckingAccout s(1000, 200);
	if (s.debit())
		printf("取出金钱\n");
	else
		printf("没有取出金钱\n");
	cout << s.Get_balance() << " " << s.Get_exchange() << endl;
	CheckingAccout s2(1000);
	if (s2.debit())
		printf("取出金钱\n");
	else
		printf("没有取出金钱\n");
	s2.credit(100);
	cout << s2.Get_balance() << " " << s.Get_exchange() << endl;
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	Account people(10000);
	cout << people.Get_balance() << endl;
	people.credit(1000);
	cout << people.Get_balance() << endl;
	people.debit(100);
	cout << people.Get_balance() << endl;
	SavingAccout SavePeople(people.Get_balance(), 0.038);
	cout << SavePeople.CalculateInterest() << endl;
	CheckingAccout CheckPeople(people.Get_balance(), 1000);
	cout << CheckPeople.Get_balance() << " " << CheckPeople.Get_exchange() << endl;
	if (CheckPeople.debit())
		printf("取钱\n");
	else
		printf("没有取钱\n");
	return 0;
}