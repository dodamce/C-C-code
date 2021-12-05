#include"OpenHashTable.h"

void Test1()//测试插入/查找/删除/打印接口
{
	OpenHash::Hash<int, int>Table;
	vector<int>ret = { 1,2,100,20,4,44 };
	for (int i = 0; i < ret.size(); i++)
	{
		Table.Insert(make_pair(ret[i], i));
	}
	Table.PrintHashTable();
	for (const auto& e : ret)
	{
		if (Table.Find(e))
		{
			Table.Erase(e);
			Table.PrintHashTable();
		}
	}
}

void Test2()//测试字符串类型
{
	//统计次数
	vector<string>Array = { "苹果","香蕉","西瓜","香蕉", "香蕉","西瓜","西瓜","苹果" };
	//CloseSpace::HashTable<string, int,StrHashKey>Hash;
	OpenHash::Hash<string, int>Hash;
	for (int i = 0; i < Array.size(); i++)
	{
		OpenHash::HashDate<string, int>* Pos = Hash.Find(Array[i]);
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
	//Test1();
	Test2();
	return 0;
}