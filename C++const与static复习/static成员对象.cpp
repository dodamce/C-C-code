#include<iostream>

using namespace std;

class temp
{
public:
	static int a;//静态成员变量在类外定义，且突破类作用域就可以访问，不需要对象,静态变量值可以改变,且改变后，会影响所有对象中的此值
	int b;//访问b必须靠对象
	temp(int date=1)
	{
		b = date;
	}

	static void Print()//static成员函数只能访问static变量。
	{//同样static函数突破类作用域就可以访问
		a++;
		cout << a << endl;
		//cout << b << endl;//报错

	}

	void Print1()//非static对象才可以访问,且static不会成重载
	{
		cout << a << " " << b << endl;
	}

	//如果想static函数访问非static变量要指定对象,用对象访问非static变量
	static void PrintStatic(temp a1)
	{
		cout << a << " " << a1.b << endl;
	}

private:
};

//在类外定义 
int temp::a = 1;


//例子

class asd
{
public:
	asd()
	{
		a++;
	}
private:
	static int a;
};

int asd::a = 0;

asd a1;
asd a2[3];

//最后a的值为4因为每次创建asd对象调用构造函数，每次构造a++，一个构造了四次

int main()
{
	cout << temp::a << " " << endl;//直接突破类作用域就可以访问
	cout << temp().b << endl;
	temp::Print();
	temp().Print1();
	temp  a(4);
	temp::PrintStatic(a);
	//静态对象与定义全局的对象相同，生命周期为整个文件
}