#include<iostream>

using namespace std;

class Computer
{
public:
	Computer(const char*Type,const char*Factoty,const char*Cpu,int money,int UNumber)
	{
		strcpy(type, Type);
		strcpy(factory, Factoty);
		strcpy(cpu,Cpu);
		memony = money;
		usbnumber = UNumber;
	}


private:
	char type[20];
	char factory[20];
	char cpu[20];
	int memony;
	int usbnumber;
};

int main()
{
	Computer s("123","123","123", 10,10);
	Computer s2(s);
	getchar();
	return 0;
}