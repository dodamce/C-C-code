#include<iostream>

class tmp
{
public:
	tmp(int c = 1, int d = 1)//初始化列表初始化
		:a(c), b(d)
	{}

	void Print()const //const修饰的是this 所以变量不能被修改
	{
		//b++;报错
		std::cout << "const" << " " << std::endl;
	}

	void Print()//与const函数构成重载，因为const函数是const this 指针，形参类型不同
	{
		b++;
		std::cout << "no const" << " " << std::endl;
	}

private:
	const int a;//只能通过初始化列表初始化
	int b;

};

int main()
{
	//const对象只能调用const函数
	const tmp a;
	tmp b;//调用非const对象函数
	a.Print();
	b.Print();
	return 0;
}