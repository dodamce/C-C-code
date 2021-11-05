//动态括号匹配

#include<iostream>

#include<stack>//C++STL

#include<string>

using namespace std;

class Match
{
public:
	void InSert(char ch)//插入栈中
	{
		Str.push_back(ch);//记录此时字符串
		if (ch == ')' || ch == ']' || ch == '}')//遇到左括号进占，遇到右括号出栈对比
		{
			//出栈对比
			FindMatch(ch);
		}
		else if (ch == '(' || ch == '[' || ch == '{')//只有括号入栈，其他字符不入栈
		{
			Stk.push(ch);
		}
		if (Stk.empty())
		{
			cout << "括号匹配" << endl;
		}
		else
		{
			cout << "括号不匹配" << endl;
		}
	}

	//打印字串
	void PrintStr()
	{
		cout << "当前字符串为" << Str << endl;
		cout << endl << Str;
	}
private:
	void FindMatch(const char ch)
	{
		if ((Stk.top()=='{'&&ch=='}')||(Stk.top()=='('&&ch==')')||(Stk.top()=='['&&ch==']'))
		{
			Stk.pop();//删除括号，匹配外层括号
		}
	}
	stack<char>Stk;
	string Str;

};

int main()
{
	Match Mh;
	char ch = 0;
	while (cin >> ch)
	{
		Mh.InSert(ch);
		Mh.PrintStr();
	}
	return 0;
}