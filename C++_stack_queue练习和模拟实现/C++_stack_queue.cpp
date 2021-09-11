#include<iostream>

#include<stack>

#include<queue>

#include<functional>

#include<list>

using namespace std;

void Test1()//栈的入栈出栈
{
	stack<int>s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	cout << s.top() << endl;
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}

void Test2()//入队出队
{
	queue<int>s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	cout << s.front() << endl;
	while (!s.empty())
	{
		cout << s.front() << " ";
		s.pop();
	}
	cout << endl;
}

//优先级队列

void Test3()
{
	//与堆类似，默认是大堆，即数字大的优先级高
	//priority_queue<int> pt;
	//小堆要添加一个仿函数，仿函数在functional头文件中。默认是less函数
    //priority_queue<int,vector<int>,greater<vector<int>::value_type>> pt;
	priority_queue<int, vector<int>, greater<int>> pt;
	pt.push(5);
	pt.push(2);
	pt.push(9);
	pt.push(6);
	pt.push(3);
	while (!pt.empty())
	{
		cout << pt.top() << " ";
		pt.pop();
	}

}

int main()
{
	/*Test1();
	Test2();*/
	Test3();
	return 0;
}