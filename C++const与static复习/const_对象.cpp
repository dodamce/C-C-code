#include<iostream>

class tmp
{
public:
	tmp(int c = 1, int d = 1)//��ʼ���б��ʼ��
		:a(c), b(d)
	{}

	void Print()const //const���ε���this ���Ա������ܱ��޸�
	{
		//b++;����
		std::cout << "const" << " " << std::endl;
	}

	void Print()//��const�����������أ���Ϊconst������const this ָ�룬�β����Ͳ�ͬ
	{
		b++;
		std::cout << "no const" << " " << std::endl;
	}

private:
	const int a;//ֻ��ͨ����ʼ���б��ʼ��
	int b;

};

int main()
{
	//const����ֻ�ܵ���const����
	const tmp a;
	tmp b;//���÷�const������
	a.Print();
	b.Print();
	return 0;
}