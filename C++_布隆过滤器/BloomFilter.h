#pragma once

#include"BitSet.h"
#include<string>
#include<iostream>//������

using namespace std;

struct StrHashArv
{
	int operator()(const string& Str)
	{
		int Sum = 0;
		for (int i = 0; i < Str.size(); i++)
		{
			Sum += ((i + 1) * Str[i]);
		}
		return Sum;
	}
};

struct StrHashSum
{
	int operator()(const string& Str)
	{
		int Sum = 0;
		for (int i = 0; i < Str.size(); i++)
		{
			Sum += Str[i];
		}
		return Sum;
	}
};

struct StrHashBKDR
{
	int operator()(const string& Str)
	{
		int Sum = 0;
		for (auto ch : Str)
		{
			Sum += ch;
			Sum *= 131;
		}
		return Sum;
	}
};

template<size_t Size, class Key = string, class HashFuc1 = StrHashArv, class HashFuc2 = StrHashBKDR, class HashFuc3 = StrHashSum>
class BloomFilter
{
public:
	void Set(const Key& k)
	{
		size_t PosHash1 = HashFuc1()(k) % Size;//��������,�ַ���ת����
		size_t PosHash2 = HashFuc2()(k) % Size;
		size_t PosHash3 = HashFuc3()(k) % Size;
		cout << "Test:" << PosHash1 << " " << PosHash2 << " " << PosHash3 << endl;
		_bitSets.Set(PosHash1);
		_bitSets.Set(PosHash2);
		_bitSets.Set(PosHash3);
	}

	bool Find(const Key& k)//true�ڣ�false���ڡ�ֻҪ��һ��ӳ�䲻���ڣ���һ������
	{
		size_t PosHash1 = HashFuc1()(k) % Size;//��������,�ַ���ת����
		if (_bitSets.Find(PosHash1) == false)
		{
			return false;
		}
		size_t PosHash2 = HashFuc2()(k) % Size;
		if (_bitSets.Find(PosHash2) == false)
		{
			return false;
		}
		size_t PosHash3 = HashFuc3()(k) % Size;
		if (_bitSets.Find(PosHash3) == false)
		{
			return false;
		}
		return true;//����λ���ڣ�˵�������ڡ���Ȼ���ڳ�ͻ
	}
private:
	NUC::BitSet<Size>_bitSets;
};