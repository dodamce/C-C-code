#include<iostream>

#include<stack>

#include<queue>

#include<functional>

#include<list>

using namespace std;

void Test1()//ջ����ջ��ջ
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

void Test2()//��ӳ���
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

//���ȼ�����

void Test3()
{
	//������ƣ�Ĭ���Ǵ�ѣ������ִ�����ȼ���
	//priority_queue<int> pt;
	//С��Ҫ���һ���º������º�����functionalͷ�ļ��С�Ĭ����less����
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