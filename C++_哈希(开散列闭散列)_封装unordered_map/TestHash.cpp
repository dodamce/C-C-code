#include"Hash_Table.h"

void Test()//���Բ���/ɾ��/����/��ӡ�ӿ�
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

//����һ���Զ���º���
//��������ƫ�ػ�Ĭ�Ϸº���
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

void Test2()//�����ַ�������
{
	//ͳ�ƴ���
	vector<string>Array = { "ƻ��","�㽶","����","�㽶", "�㽶","����","����","ƻ��" };
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