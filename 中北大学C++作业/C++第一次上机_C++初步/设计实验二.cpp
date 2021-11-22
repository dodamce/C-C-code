#include<iostream>

#include<string.h>

using namespace std;

//·µ»Ø>0->a>b =0->a==b <0->a<b;

int Max(int a, int b)
{
	if (a == b)
		return 0;
	else if (a < b)
		return -1;
	else
		return 1;
}

int Max(char a, char b)
{
	if (a == b)
		return 0;
	else if (a < b)
		return -1;
	else
		return 1;
}

int Max(char* a, char* b)
{
	int tmp = strcmp(a, b);
	return strcmp(a, b);
}

int Max(const char* a,const char* b)
{
	return strcmp(a, b);
}

int main()
{
	if (Max("abze", "abfr")>0)
	{
		cout << ">" << endl;
	}
	char a[] = "hello";
	char b[] = "hzllo";
	if (Max(a, b)<0)
	{
		cout << "<" << endl;
	}
	if (Max('e', 'f') > 0)
	{
		cout << ">" << endl;
	}
	if (Max(4, 2) > 0)
	{
		cout << ">" << endl;
	}
	return 0;
}