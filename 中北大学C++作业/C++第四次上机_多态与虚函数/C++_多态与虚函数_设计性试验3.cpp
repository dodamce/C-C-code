#define PAI 3.14
#include<iostream>

using namespace std;

class Size
{
public:
	virtual double Value()=0;
};

class Bool:public Size
{
public:
	Bool(double r)
		:_r(r)
	{}
	double Value()
	{
		return 4/3*(PAI)*pow(_r,3);
	} 
private:
	double _r;
};

class Square:public Size
{
public:
	Square(double longSize,double withSize,double highSize)
		:_long(longSize),_with(withSize),_high(highSize)
	{}
	double Value()
	{
		return _long*_with*_high;
	} 
private:
	double _long;
	double _with;
	double _high;
};

int main()
{
	Bool s1(2);
	cout<<s1.Value()<<endl;
	Square s2(2,4,5);
	cout<<s2.Value()<<endl;
	getchar();
	return 0;
}