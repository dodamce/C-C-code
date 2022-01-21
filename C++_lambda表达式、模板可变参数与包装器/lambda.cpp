#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//lambda���ʽ
//��׽�б�+����+����ֵ����+����ʵ��

struct Date
{
	Date(int year,int mouth,int date):_year(year),_mounth(mouth),_date(date)
	{}
	int _year;
	int _mounth;
	int _date;
};

void Test()
{
	int a = 1; int b = 2;
	//add������lambda���ʽ
	auto addfun = [](int x, int y)->int {return x + y; };
	cout << addfun(a, b) << endl;
	//��׽a,b
	auto addfun1 = [a, b]()->int {return a + b + 10; };
	cout << addfun1() << endl;
	//ʡ�Է���ֵ�벶׽�Ĳ���,����ֵ�����������Լ��Ƶ�
	auto addfun2 = [a, b] {return a + b + 20; };
	cout << addfun2() << endl;


	//lambda���ʽʵ�ֽ�������
	auto swap = [](int& x, int& y)->void {int tmp = x; x = y; y = tmp; };
	cout << a << " " << b << endl;
	swap(a, b);
	cout << "lambda swap " << a << " " << b << endl;

	//���ò�׽�б�ʡ�Բ���//mutableʹֵ��׽�ı������޸�
	//auto swap1 = [a, b]()mutable->void {int tmp = a; a = b; a = tmp; };
	auto swap1 = [&a, &b] {int tmp = a; a = b; b = tmp; };

	swap1();
	cout << "lambda swap " << a << " " << b << endl;

	//lambda���ʽ�滻�º���ʵ������
	//lambda���ʽ�ײ�ʵ����Ϊ�º�����ÿ����ͬ��lambda���ʽ�������Ʋ�ͬ�����Բ����໥��ֵ

	vector<Date>vet;
	vet.emplace_back(2021, 10, 2);
	vet.emplace_back(2021, 12, 24);
	std::sort(vet.begin(), vet.end(), [](const Date& y1, const Date& y2)->bool {return y1._mounth > y2._mounth; });

}

#include<functional>

char fun(int a, int b)
{
	return 'A';
}

class funter
{
public:
	char operator()(int a, int b)
	{
		return 'A';
	}

	static int Cout(int a, int b)
	{
		return a + b;
	}
	int Cout2(int a, int b)
	{
		return a + b;
	}
};

/*
template<class T>//ʹ�ð�װ����ģ��ֻ��ʵ����Ϊһ�ݣ���Ϊ��ͬ���ͺ�����װ����ͬ
*/

void Test1()
{
	//��װ����ָ��
	std::function<char(int, int)>ff = fun;
	//����
	cout << ff(1, 2) << endl;
	//��װ�º���
	std::function<char(int, int)>ff1 = funter();
	cout << ff1(3, 4) << endl;
	//��װ��Ա����
	//��̬��
	std::function<int(int, int)>ff2 = funter::Cout;
	cout << ff2(1, 2) << endl;
	//�Ǿ�̬��
	std::function<int(funter, int, int)>ff3 = &funter::Cout2;//ȡ��Ա�����ĵ�ַ
	cout << ff3(funter(), 1, 6) << endl;
	//��װlambda���ʽ
	auto f5 = [](int a, int b)->int {return a + b; };
	std::function<int(int, int)>ff4 = f5;
	cout << ff4(1, 3) << endl;
	//��װ�������������������ͬ������ͬ
}

int main()
{
	//Test();lambda���ʽ
	Test1();//��װ��

	return 0;
}