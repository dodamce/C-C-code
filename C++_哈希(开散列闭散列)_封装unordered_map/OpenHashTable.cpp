#include"OpenHashTable.h"

void Test1()//���Բ���/����/ɾ��/��ӡ�ӿ�
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

void Test2()//�����ַ�������
{
	//ͳ�ƴ���
	vector<string>Array = { "ƻ��","�㽶","����","�㽶", "�㽶","����","����","ƻ��" };
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