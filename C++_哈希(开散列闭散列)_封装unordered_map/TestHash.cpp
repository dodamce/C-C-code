#include"Hash_Table.h"

void Test()//测试插入/删除/查找/打印接口
{
	CloseSpace::HashTable<int, int>Table;
	vector<int>ret = { 1,2,100,20,4,44 };
	Table.Erase(10);
	for (const auto s : ret)
	{
		Table.Insert(make_pair(s, s));
	}
	Table.PrintHashTable();
	for (size_t i = 0; i < ret.size(); i++)
	{
		if (Table.Find(ret[i]))
		{
			Table.Erase(ret[i]);
			Table.PrintHashTable();
		}
	}
}

//方法一：自定义仿函数
//方法二：偏特化默认仿函数
//struct StrHashKey
//{
//	int operator()(const string& Str)
//	{
//		int Sum = 0;
//		for (int i = 0; i < Str.size(); i++)
//		{
//			Sum += Str[i];
//		}
//		return Sum;
//	}
//};

void Test2()//测试字符串类型
{
	//统计次数
	vector<string>Array = { "苹果","香蕉","西瓜","香蕉", "香蕉","西瓜","西瓜","苹果" };
	//CloseSpace::HashTable<string, int,StrHashKey>Hash;
	CloseSpace::HashTable<string, int>Hash;
	for (int i = 0; i < Array.size(); i++)
	{
		CloseSpace::HashDate<string,int>*Pos=Hash.Find(Array[i]);
		if (Pos == nullptr)
		{
			Hash.Insert(make_pair(Array[i], 1));
		}
		else
		{
			Pos->_kv.second++;
		}
	}
	Hash.PrintHashTable();
}

int main()
{
	//Test();
	Test2();
	return 0;
}