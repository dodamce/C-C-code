#include"List.h"

void TestList1()//²âÊÔÎ²²å.µü´úÆ÷
{
	My::list<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	My::list<int>::iterator it= v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (auto e : v)
	{
		cout << e << " ";
	}
}

void TestList2()
{
	My::list<int>v;
	v.push_back(2);
	v.push_back(2);
	v.push_back(4);
	v.push_back(6);
	v.push_back(7);
	My::PrintList(v);
}


void TestList3()
{
	My::list<int>v; 
	v.push_back(2);
	v.push_back(2);
	v.push_back(4);
	v.push_back(6);
	v.push_back(7);
	//v.clear();
	My::list<int>v1(v);//¿½±´¹¹Ôì
	My::PrintList(v1);
	v.clear();
	My::PrintList(v);
	v = v1;
	My::PrintList(v);
}

int main()
{
	//TestList1();
	TestList3();
	return 0;
}