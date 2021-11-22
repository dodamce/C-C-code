//字符串反转

#include<iostream>

#include<stack>//C++STL

using namespace std;

//打印出栈元素函数
void PrintStack(stack<char>& Str)
{
	if (Str.empty())//栈为空，错误
	{
		cout << "error" << endl;
	}
	while (!Str.empty())
	{
		cout << Str.top();
		Str.pop();
	}
	cout << endl;
}

int main()
{
	stack<char>Str;//栈
	while (1)//多组测试
	{
		//持续输入字符串，以‘#’代表字符串结束的标志
		char ch;
		cout << "每个字符串以#结尾！！！" << endl;
		while (1)
		{
			cin >> ch;
			if (ch == '#')
				break;//跳出循环开始处理字符串
			Str.push(ch);
		}
		PrintStack(Str);
	}
	return 0;
}