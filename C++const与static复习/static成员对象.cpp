#include<iostream>

using namespace std;

class temp
{
public:
	static int a;//��̬��Ա���������ⶨ�壬��ͻ����������Ϳ��Է��ʣ�����Ҫ����,��̬����ֵ���Ըı�,�Ҹı�󣬻�Ӱ�����ж����еĴ�ֵ
	int b;//����b���뿿����
	temp(int date=1)
	{
		b = date;
	}

	static void Print()//static��Ա����ֻ�ܷ���static������
	{//ͬ��static����ͻ����������Ϳ��Է���
		a++;
		cout << a << endl;
		//cout << b << endl;//����

	}

	void Print1()//��static����ſ��Է���,��static���������
	{
		cout << a << " " << b << endl;
	}

	//�����static�������ʷ�static����Ҫָ������,�ö�����ʷ�static����
	static void PrintStatic(temp a1)
	{
		cout << a << " " << a1.b << endl;
	}

private:
};

//�����ⶨ�� 
int temp::a = 1;


//����

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

//���a��ֵΪ4��Ϊÿ�δ���asd������ù��캯����ÿ�ι���a++��һ���������Ĵ�

int main()
{
	cout << temp::a << " " << endl;//ֱ��ͻ����������Ϳ��Է���
	cout << temp().b << endl;
	temp::Print();
	temp().Print1();
	temp  a(4);
	temp::PrintStatic(a);
	//��̬�����붨��ȫ�ֵĶ�����ͬ����������Ϊ�����ļ�
}