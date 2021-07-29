#include<iostream>


class Date
{
public:
	Date(int year = 2020, int mounth = 1,int day=1)
	{
		_year = year;
		_mounth = mounth;
		_day = day;
	}
	Date(Date& p)
	{
		_year = p._year;
		_mounth = p._mounth;
		_day = p._day;
	}
	Date operator=(const Date& x)
	{
		if (this != &x)
		{
			_year = x._year;
			_mounth = x._mounth;
			_day = x._day;
		}
		return *this;
	}
private:
	int _year;
	int _mounth;
	int _day;
};

int main()
{
	Date a(2021,5,30);
	Date b(a);
	Date c;
	b = c = a;
	return 0;
}