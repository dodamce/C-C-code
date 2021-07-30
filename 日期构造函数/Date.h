#pragma once

#include<iostream>
#include<assert.h>

using  std::cout;

using std::endl;

using namespace std;

class Date
{
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1);
	void Print();
	Date(const Date& p);
	~Date();
	Date& operator+=(int day);
	Date operator+(int day);
	Date operator=(const Date& p);
	Date operator-(int day);
	Date& operator-=(int day);
	Date& operator++();
	Date operator++(int);
	Date operator--(int);
	Date& operator--();
	int operator-(const Date& d);
	bool operator>(const Date& d);
	bool operator==(const Date& d);
	inline bool operator >= (const Date& d);
	bool operator < (const Date& d);
	bool operator <= (const Date& d);
	bool operator != (const Date& d);
private:
	int _year;
	int _mounth;
	int _day;
};
