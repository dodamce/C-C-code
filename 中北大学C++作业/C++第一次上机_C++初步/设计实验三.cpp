#include<iostream>

using namespace std;

void My_swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void My_Pswap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	int a = 10;
	int b = 20;
	cout << a << " " << b << endl;
	My_swap(a, b);
	cout << a << " " << b << endl;
	My_Pswap(&a, &b);
	cout << a << " " << b << endl;
	return 0;
}