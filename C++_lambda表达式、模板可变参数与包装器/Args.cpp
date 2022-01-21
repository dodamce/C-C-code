#include<iostream>
#include<string>
#include<bitset>

using namespace std;

void ShowListA() {}

template<class T, class ...Args>//模板可变参数
void ShowListA(const T& val, Args...args)
{
	//递归展开参数包
	cout << val << endl;
	ShowListA(args...);//最后到0个参数的时候，调用无参函数结束递归
}

template<class ...Args>
void ShowArgs(Args...args)
{
	cout << "Tips：参数个数为 " << sizeof...(args) << endl;//打印参数个数
	ShowListA(args...);//展开参数包
}


template<class T>
void PrintArgs(const T& t)
{
	cout << t << endl;
}

void ShowListCom() {};
//逗号表达式推导模板参数
template<class...Args>
void ShowListCom(Args...args)
{
	//列表初始化
	int arr[] = { (PrintArgs(args),0)... };//数组大小为参数个数，前提是args之间的数据类型相同
//展开为(PrintArgs(a1),0),(PrintArgs(a2),0)(PrintArgs(a3),0),结果都是整数0，所以可以放到数组中
	cout << endl;

}

int main()
{
	ShowListCom(1, 'A', string("ABX"));
	ShowListCom();
	ShowListCom(1);
	ShowListCom(1, "Hello");
	return 0;
}