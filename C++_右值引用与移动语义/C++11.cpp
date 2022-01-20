#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include"string.h"

using namespace std;

void TestRight()
{
	int x = 10; int y = 20;
	//右值
	10;
	(x + y);
	fmax(x, y);
	int&& r = 10;
	int&& r2 = (x + y);
	int&& t3 = fmax(x, y);//将临时的右值保存起来，右值就变的可以取地址了
	r = 50;
	std::cout << r << std::endl;
	std::cout << &r << std::endl;
}

void Test()
{
	//左值引用可以引右值
	const int& r = 10 + 20;
	//右值引用不能直接引左值
	int a = 10;
	//int&& r2 = a;
	int&& r2 = std::move(a);
}

//移动构造，移动赋值
void Test2()
{
	My::string s = "Hello";
	My::string s2 = std::move(s);//将s对象move后，s对象被销毁，需要注意
}

void Fun(int& val) { cout << "左值引用" << endl; }
void Fun(int&& val) { cout << "右值引用" << endl; }
void Fun(const int& val) { cout << "const 左值引用" << endl; }
void Fun(const int&& val) { cout << "const 右值引用" << endl; }

//万能引用
template<class T>
void N_Perfect(T&& val)//val可以引用右值或左值,无完美转发
{
	Fun(val);//右值被引用后可以取到地址，所以属性从右值变为左值
	cout << &val << endl;
}

void Test3()
{
	N_Perfect(10);
	int a = 20;
	N_Perfect(a);
	N_Perfect(std::move(a));
	const int b = 20;
	N_Perfect(b);
	N_Perfect(std::move(b));
}

template<class T>
void Perfect(T&& val)//val可以引用右值或左值,完美转发
{
	Fun(std::forward<T>(val));//完美转发保持左右值属性
}

void Test4()
{
	Perfect(10);
	int a = 20;
	Perfect(a);
	Perfect(std::move(a));
	const int b = 20;
	Perfect(b);
	Perfect(std::move(b));
}

//右值引用再传参时会属性会退化为左值

template<class T1, class T2>

auto Fun(T1 t1, T2 t2)->decltype(t1* t2)//auto不能单独做返回值,->指定返回值类型
{
	decltype(t1 * t2)ret = t1 * t2;//根据乘积来判断ret的类型
	cout << typeid(ret).name() << endl;
	return ret;
}


int main()
{
	//TestRight();x
	//Test();
	//Test2();
	//Test3();
	Test4();
	cout << Fun(1, 3) << endl;
	cout << Fun(1.1, 4) << endl;
	return 0;
}