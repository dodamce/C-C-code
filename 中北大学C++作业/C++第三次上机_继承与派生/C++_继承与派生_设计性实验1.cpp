#include<iostream>

using namespace std;

class Triangle
{
public:
	Triangle(double a = 1, double b = 1, double c = 1)
		:_a(a),_b(b),_c(c)
	{}

	double Area()
	{
		double s = (_a + _b + _c) / 2;
		double area = s * (s - _a) * (s - _b) * (s - _c);//º£Â×¹«Ê½
		return sqrt(area);
	}
private:
	double _a;
	double _b;
	double _c;
};

class Podetium :public Triangle
{
public:
	Podetium(int a=1,int b=1,int c=1,int h=1)
		:Triangle(a,b,c),_h(h)
	{}
	double Volume()
	{
		return this->Area() * _h;
	}
private:
	double _h;
};

void Test1()
{
	Triangle s(2, 2, 2);
	cout << s.Area() << endl;
}

void Test2()
{
	Podetium s(2, 2, 2, 2);
	cout << s.Area() << " " << s.Volume() << endl;
}

int main()
{
	Test1();
	Test2();
	return 0;
}