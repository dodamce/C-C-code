#include<iostream>

using namespace std;

class A
{
public:
	int _a;
	A(int a,int b,int c)
		:_a(a),_b(b),_c(c)
	{}

	void Print()
	{
		cout << _a << " " << _b << " " << _c << endl;
	}
protected:
	int _b;
private:
	int _c;
};

class B : public A//公有继承中父类在B中权限形式不变，函数不变
{
public:

protected:

private:
};

class C : protected A//保护继承，父类的公有属性成员全部变为保护
{
public:

protected:

private:
};

//私有继承
class D : private A//私有继承，父类中的所有非私有成员继承过来时全部变为私有成员
{
public:
	void Print2()
	{
		//cout << _c;报错，_c为父类的私有成员任何继承无法访问
		cout << _a << " " << _b << endl;
	}

protected:

private:
};
//父类中的私有成员任何继承方式都无法访问
//私有继承会导致其无法在被其他类继承

class E :public D
{
	//其中无任何成员，失去继承意义
	/*void print3()
	{
		cout << _a << _b << endl;报错
	}*/
};

int main()
{
	return 0;
}