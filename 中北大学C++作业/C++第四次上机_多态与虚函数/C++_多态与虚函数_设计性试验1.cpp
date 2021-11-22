#include<iostream>

using namespace std;

class Time
{
	friend Time operator-(Time& dev,Time& soc);
	friend void DevTime(Time&dev,Time& soc,Time&tmp);
public:
	Time(int hour=0,int minute=0,int second=0)
		:_hour(hour),_minute(minute),_second(second)
	{}
	int GetNumber()
	{
		int time=0;
		time=_second+60*_minute+3600*_hour;
		return time;
	}
private:
	int _hour;
	int _minute;
	int _second;
};

Time operator -(Time& dev,Time& soc)
{
	Time tmp;
	if(dev._hour>soc._hour)
	{
		DevTime(dev,soc,tmp);
	}
	else
	{
		DevTime(soc,dev,tmp);
	}
	return tmp;
}

void DevTime(Time&dev,Time& soc,Time&tmp)//dev>soc
{
	int second=dev._second-soc._second;
	if(second<0)
	{
		dev._minute--;
		second+=60;
	}
	int minute=dev._minute-soc._minute;
	int hour=dev._hour-soc._hour;
	tmp._hour=hour;tmp._minute=minute;tmp._second=second;
}

//µ¥Ôª²âÊÔ
void Test1()
{
	Time s1(6,25,30);
	Time s2(8,30,21);
	Time tmp=s2-s1;
	cout<<tmp.GetNumber()<<endl;
}

int main()
{
	Test1();
	getchar();
}