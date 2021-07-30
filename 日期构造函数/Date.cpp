#include"Date.h"

inline int GetMonthDay(int year, int mounth)
{
	int day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		day[2] = 29;
	}
	return day[mounth];
}

Date::Date(int year, int mounth, int day)
{
	if (year > 0 && mounth > 0 && mounth < 13 && day>0 && day <= GetMonthDay(year, mounth))
	{
		_year = year;
		_mounth = mounth;
		_day = day;
	}
	else
	{
		cout << "日期非法" << endl;
		assert(false);
	}
}

Date::Date(const Date& p)
{
	_year = p._year;
	_mounth = p._mounth;
	_day = p._day;
}

Date::~Date()
{
	cout << "~Date()析构函数" << endl;
}

 void Date::Print()
{
	 cout << _year << "年" << _mounth << "月" << _day << "天" << endl;
}

 Date Date::operator=(const Date& p)
 {
	 if (this != &p)
	 {
		 _year = p._year;
		 _mounth = p._mounth;
		 _day = p._day;
	 }
	 return *this;
 }

 Date& Date::operator+=(int day)
 {
	 _day += day;
	 while(_day > GetMonthDay(_year, _mounth))
	 {
		 _day -= GetMonthDay(_year, _mounth);
		 ++_mounth;
		 if (_mounth > 12)
		 {
			 ++_year;
			 _mounth = 1;
		 }
	 }
	 return *this;
 }

 Date Date::operator+(int day)
{
	 Date ret(*this);
	 ret += day;
	 return ret;
}

 Date& Date::operator-=(int day)
 {
	 _day -= day;
	 while (_day <= 0)
	 {
		 _mounth--;
		 if (_mounth <= 0)
		 {
			 _year--;
			 _mounth = 12;
		 }
		 _day += GetMonthDay(_year, _mounth);
	 }
	 return *this;
 }

 Date Date::operator-(int day)
 {
	 Date ret(*this);
	 ret -= day;
	 return ret;
 }

 Date& Date::operator++()
 {
	 (*this) += 1;
	 return *this;
 }

 Date Date::operator++(int)
 {
	 Date tmp(*this);
	 *this += 1;
	 return tmp;
 }

 Date& Date::operator--()
 {
	 (*this) -= 1;
	 return (*this);
 }

 Date Date::operator--(int)
 {
	 Date tmp(*this);
	 *this -= 1;
	 return tmp;
 }

 int Date::operator-(const Date& d)
 {
	 Date max = *(this);
	 Date min = d;
	 int flag = 1;
	 if (*this < d)
	 {
		 max = d;
		 min == *this;
		 flag = -1;
	 }
	 int n = 0;
	 while (min != max)
	 {
		 min++;
		 n++;
	 }
	 return n * flag;
 }

 bool Date::operator==(const Date& d)
 {
	 return _year == d._year && _mounth == d._mounth && _day == d._day;
}

 bool Date::operator<(const Date& d)
 {
	 if (d._year > _year)
	 {
		 return true;
	 }
	 else
	 {
		 if (d._mounth > _mounth)
		 {
			 return true;
		 }
		 else
		 {
			 if (d._day > _day)
			 {
				 return true;
			 }
			 else
			 {
				 return false;
			 }
		 }
	 }
 }

 bool Date::operator<=(const Date& d)
 {
	 return *(this) < d || *(this) == d;
 }

 bool Date::operator>(const Date& d)
 {
	 return !(*(this) <= d);
 }

 bool Date::operator>=(const Date& d)
 {
	 return (*this) > d || (*this) == d;
 }

 bool Date::operator!=(const Date& d)
 {
	 return ((*this) == d);
 }

 //友元函数

 ostream& operator<<(ostream& out,const Date& d)
 {
	 out << d._year << "年" << d._mounth << "月" << d._day << "天";
	 return out;
 }

 istream& operator>>(istream& in, Date& d)
 {
	 in >> d._year >> d._mounth >> d._day;
	 return in;
 }