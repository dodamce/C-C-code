#include<iostream>
#include<string>

using namespace std;

class Father
{
public:
	Father()
	{
		FirstName = "*";
		SecondName = "����";
	}
	Father(const string& first,const string&second)
		:FirstName(first),SecondName(second)
	{}

	void Print()
	{
		cout << FirstName << SecondName << endl;
	}
protected:
	string FirstName;
	string SecondName;
};

class Son:public Father
{
public:
	Son(const string& SonS, const string& FarF, const string& FarS)
		:Father(FarF, FarS)//��������ó�ʼ���б�����乹�캯����ʼ����������ĳ�Ա�����Գ�ʼ��
	{
		this->SonSecondName = SonS;
	}
	Son()
	{
		SonSecondName = "����";
	}

	//�������������ຯ����ͬʱ��Ĭ�϶���Ϊ˭�����Ǹ�����ĺ��������������Ҫ���������ָ��ָ��
	void Print()
	{
		cout << FirstName << SonSecondName << endl;
	}

protected:
	string SonSecondName;
};

int main()
{
	Son boy("����","��","����");
	boy.Print();//����Son�����Print����
	//ָ������Father�����Print����
	boy.Father::Print();//����Father�����Print����

	//����Ĭ�Ϲ��캯��
	Son boy2;
	boy2.Print();
	boy2.Father::Print();
	return 0;
}