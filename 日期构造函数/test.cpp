#include"Date.h"

void test1()
{
	Date a(2021, 5, 30);
	//a += 10;
	a.Print();
	a -= 10;
	a.Print();
	Date b = a;
	a = b - 30;
	a.Print();
	a = a + 10;
	a.Print();
}

int main()
{
	test1();
}