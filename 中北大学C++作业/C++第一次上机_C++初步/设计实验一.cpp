#include<iostream>

using namespace std;

//函数模板
//template<class T>
//T Max(T a, T b,T c)
//{
//	T tmp = a > b ? a : b;
//	return tmp > c ? tmp : c;
//}

//函数重载
int Max(int a, int b, int c)
{
	int tmp = a > b ? a : b;
	return tmp > c ? tmp : c;
}

double Max(double a, double b, double c)
{
	double tmp = a > b ? a : b;
	return tmp > c ? tmp : c;
}

char Max(char a, char b, char c)
{
	char tmp = a > b ? a : b;
	return tmp > c ? tmp : c;
}

int main()
{
	double max=Max(1.3, 6.4, 3.4);
	char max2 = Max('e', 'q', 'e');
	cout << max << " " << max2 << endl;
	return 0;
}