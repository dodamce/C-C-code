#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//lambda表达式
//捕捉列表+参数+返回值类型+函数实现

struct Date
{
	Date(int year,int mouth,int date):_year(year),_mounth(mouth),_date(date)
	{}
	int _year;
	int _mounth;
	int _date;
};

void Test()
{
	int a = 1; int b = 2;
	//add函数的lambda表达式
	auto addfun = [](int x, int y)->int {return x + y; };
	cout << addfun(a, b) << endl;
	//捕捉a,b
	auto addfun1 = [a, b]()->int {return a + b + 10; };
	cout << addfun1() << endl;
	//省略返回值与捕捉的参数,返回值编译器可以自己推导
	auto addfun2 = [a, b] {return a + b + 20; };
	cout << addfun2() << endl;


	//lambda表达式实现交换函数
	auto swap = [](int& x, int& y)->void {int tmp = x; x = y; y = tmp; };
	cout << a << " " << b << endl;
	swap(a, b);
	cout << "lambda swap " << a << " " << b << endl;

	//利用捕捉列表省略参数//mutable使值捕捉的变量可修改
	//auto swap1 = [a, b]()mutable->void {int tmp = a; a = b; a = tmp; };
	auto swap1 = [&a, &b] {int tmp = a; a = b; b = tmp; };

	swap1();
	cout << "lambda swap " << a << " " << b << endl;

	//lambda表达式替换仿函数实现排序
	//lambda表达式底层实际上为仿函数，每个不同的lambda表达式类型名称不同，所以不能相互赋值

	vector<Date>vet;
	vet.emplace_back(2021, 10, 2);
	vet.emplace_back(2021, 12, 24);
	std::sort(vet.begin(), vet.end(), [](const Date& y1, const Date& y2)->bool {return y1._mounth > y2._mounth; });

}

#include<functional>

char fun(int a, int b)
{
	return 'A';
}

class funter
{
public:
	char operator()(int a, int b)
	{
		return 'A';
	}

	static int Cout(int a, int b)
	{
		return a + b;
	}
	int Cout2(int a, int b)
	{
		return a + b;
	}
};

/*
template<class T>//使用包装器后模板只会实例化为一份，因为相同类型函数包装器相同
*/

void Test1()
{
	//包装函数指针
	std::function<char(int, int)>ff = fun;
	//调用
	cout << ff(1, 2) << endl;
	//包装仿函数
	std::function<char(int, int)>ff1 = funter();
	cout << ff1(3, 4) << endl;
	//包装成员函数
	//静态：
	std::function<int(int, int)>ff2 = funter::Cout;
	cout << ff2(1, 2) << endl;
	//非静态：
	std::function<int(funter, int, int)>ff3 = &funter::Cout2;//取成员函数的地址
	cout << ff3(funter(), 1, 6) << endl;
	//包装lambda表达式
	auto f5 = [](int a, int b)->int {return a + b; };
	std::function<int(int, int)>ff4 = f5;
	cout << ff4(1, 3) << endl;
	//包装器类型如果函数类型相同，则相同
}

int main()
{
	//Test();lambda表达式
	Test1();//包装器

	return 0;
}