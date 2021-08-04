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
	sort(v1.begin(), v1.end());//默认升序
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	sort(v1.begin(), v1.end(), greater<int>());//降序
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	//list不支持sort sort 底层实现为快排
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
	it.erase(pos);//删除数据后pos迭代器失效
	Print(it);
}

void TestList5()//转移
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
	v2.splice(v2.begin(), v, pos);//pos的位置还是指向3的位置，没有失效
	Print(v); Print(v2);
	v2.push_back(10);
	//pos = v.begin();
	v.splice(v.begin(), v2, pos, v2.end());
	Print(v);
}

void TestList6()//去掉指定元素，去重(相邻元素)(先排序在去重)，逆置,交换
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
	v2.sort();//效率不高
	v2.unique();
	Print(v2);
	v2.reverse();
	Print(v2);
	v2.swap(v);//交换v2和v的值
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