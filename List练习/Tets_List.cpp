#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

template<class Pos>
void Print(const Pos&p)
{
	Pos::const_iterator it = p.begin();
	while (it != p.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

void TestList1()
{
	list<int> it;
	it.push_back(1);
	it.push_back(2);
	it.push_back(3);
	it.push_back(4);
	it.push_back(5);
	list<int>::iterator begin = it.begin();
	while (begin != it.end())
	{
		cout << *begin << " ";
		++begin;
	}
	cout << endl;
	for (auto e : it)
	{
		cout << e << " ";
	}
	cout << endl;
	int a[] = { 10, 11, 12, 13, 14 };
	list<int>v1(a, a + sizeof(a) / sizeof(int));
	for (auto e : v1)
	{
		cout << e << " ";
	}
}

void TestList2()
{
	int a[] = { 10, 14, 12, 15, 9 };
	vector<int>v1(a, a + sizeof(a) / sizeof(int));
	sort(v1.begin(), v1.end());//Ĭ������
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	sort(v1.begin(), v1.end(), greater<int>());//����
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	//list��֧��sort sort �ײ�ʵ��Ϊ����
	list<int>v2(a, a + sizeof(a) / sizeof(int));
	v2.sort();
	for (auto e : v2)
	{
		cout << e << " ";
	}
}

void TestList3()
{
	list<int> it;
	it.push_back(1);
	it.push_back(2);
	it.push_back(3);
	it.push_back(4);
	it.push_back(5);
	Print(it);
	int a[] = { 10, 14, 12, 15, 9 };
	vector<int>v1(a, a + sizeof(a) / sizeof(int));
	Print(v1);
}

void TestList4()
{
	list<int> it;
	it.push_back(1);
	it.push_back(2);
	it.push_back(3);
	it.push_back(4);
	it.push_back(5);
	list<int>::iterator pos = find(it.begin(), it.end(), 3);
	it.insert(pos, 30);
	Print(it);
	it.erase(pos);//ɾ�����ݺ�pos������ʧЧ
	Print(it);
}

void TestList5()//ת��
{
	list<int>v;
	for (int i = 0; i < 5; i++)
	{
		v.push_back(i);
	}
	list<int>v2;
	for (int i = 10; i < 15; i++)
	{
		v2.push_back(i);
	}
	Print(v); Print(v2);
	list<int>::iterator pos = find(v.begin(), v.end(), 3);
	v.splice(pos, v2);
	Print(v); Print(v2);
	v2.splice(v2.begin(), v, pos);//pos��λ�û���ָ��3��λ�ã�û��ʧЧ
	Print(v); Print(v2);
	v2.push_back(10);
	//pos = v.begin();
	v.splice(v.begin(), v2, pos, v2.end());
	Print(v);
}

void TestList6()//ȥ��ָ��Ԫ�أ�ȥ��(����Ԫ��)(��������ȥ��)������,����
{
	list<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(2);
	list<int>v2(v);
	Print(v);
	v.remove(2);
	Print(v);
	/*v2.unique();
	Print(v2);*/
	v2.sort();//Ч�ʲ���
	v2.unique();
	Print(v2);
	v2.reverse();
	Print(v2);
	v2.swap(v);//����v2��v��ֵ
	Print(v2);
}

int main()
{
	//TestList1();
	//TestList2();
	//TestList3();
	//TestList4();
	//TestList5();
	TestList6();
	return 0;
}