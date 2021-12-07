#include"unordered_map.h"
#include"unordered_set.h"
#include<time.h>

void Test()
{
	vector<int> arr = { 10,8,28,5,1,4 };
	dodamce::unordered_set<int>Table;
	for (int i = 0; i < arr.size(); i++)
	{
		Table.Insert(arr[i]);
	}
	dodamce::unordered_set<int>::iterator Ptr = Table.begin();
	while (Ptr != Table.end())
	{
		cout << *Ptr << " ";
		++Ptr;
	}
	cout << endl;
	while (Ptr != Table.end())
	{
		cout << *Ptr << " ";
		++Ptr;
	}
}

void Test2()
{
	vector<int> arr = { 10,8,28,5,1,4 };
	dodamce::unordered_map<int, int>Table;
	for (int i = 0; i < arr.size(); i++)
	{
		Table.Insert(make_pair(arr[i], i));
	}
	dodamce::unordered_map<int, int>::iterator Ptr = Table.begin();
	while (Ptr != Table.end())
	{
		cout << Ptr->first << "->" << Ptr->second << endl;
		++Ptr;
	}
	Table[10] = 100;
	dodamce::unordered_map<int, int>::iterator Pos = Table.begin();
	while (Pos != Table.end())
	{
		cout << Pos->first << "->" << Pos->second << endl;
		++Pos;
	}
}

void Test1()//²âÊÔµü´úÆ÷
{
	srand((unsigned int)time(nullptr));
	int Size = 10;
	dodamce::unordered_set<int>Table;
	for (int i = 0; i < Size; i++)
	{
		Table.Insert(rand() % 50 + 1);
	}
	dodamce::unordered_set<int>::iterator Ptr = Table.begin();
	while (Ptr != Table.end())
	{
		cout << *Ptr << " ";
		++Ptr;
	}
}

void Test3()//²âÊÔ¿½±´¹¹Ôìº¯Êý
{
	srand((unsigned int)time(nullptr));
	int Size = 10;
	dodamce::unordered_set<int>Table;
	for (int i = 0; i < Size; i++)
	{
		Table.Insert(rand() % 50 + 1);
	}
	dodamce::unordered_set<int>::iterator Ptr = Table.begin();
	while (Ptr != Table.end())
	{
		cout << *Ptr << " ";
		++Ptr;
	}
	cout << endl;
	dodamce::unordered_set<int>Copy_Table = Table;
	for (const auto& e : Table)
	{
		cout << e << " ";
	}
}

int main()
{
	//Test1();
	//Test();
	//Test2();
	Test3();
	return 0;
}