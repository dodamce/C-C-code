//模拟形参得到实参的过程

//赋值时先定义的先赋值

#include<iostream>
#include<queue>
#include<string>
#include<vector>

using namespace std;


int main()
{
	vector<string>Arr;
	queue<string>Num;
	while (1)
	{
		Arr.clear();
		cout << "请定义变量名,以' '字符分割每个变量，变量输入完毕后以'#'结束" << endl;
		/* a b c #   定义三个变量*/
		string Str;
		while (cin >> Str && Str != "#")
		{
			Arr.push_back(Str);
		}
		string _Num;
		cout << "请定义变量大小,以' '字符分割每个变量大小，变量输入完毕后以'#'结束" << endl;
		while (cin >> _Num && _Num != "#")
		{
			Num.push(_Num);
		}
		for (int i = 0; i < Arr.size(); i++)
		{
			cout << Arr[i] << "=" << Num.front() << endl;
			Num.pop();
		}
	}
	return 0;
}