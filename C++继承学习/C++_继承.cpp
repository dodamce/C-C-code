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

class B : public A//���м̳��и�����B��Ȩ����ʽ���䣬��������
{
public:

protected:

private:
};

class C : protected A//�����̳У�����Ĺ������Գ�Աȫ����Ϊ����
{
public:

protected:

private:
};

//˽�м̳�
class D : private A//˽�м̳У������е����з�˽�г�Ա�̳й���ʱȫ����Ϊ˽�г�Ա
{
public:
	void Print2()
	{
		//cout << _c;����_cΪ�����˽�г�Ա�κμ̳��޷�����
		cout << _a << " " << _b << endl;
	}

protected:

private:
};
//�����е�˽�г�Ա�κμ̳з�ʽ���޷�����
//˽�м̳лᵼ�����޷��ڱ�������̳�

class E :public D
{
	//�������κγ�Ա��ʧȥ�̳�����
	/*void print3()
	{
		cout << _a << _b << endl;����
	}*/
};

int main()
{
	return 0;
}