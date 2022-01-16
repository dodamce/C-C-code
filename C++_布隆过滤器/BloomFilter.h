#pragma once

#include"BitSet.h"
#include<string>
#include<iostream>//测试用

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
		size_t PosHash1 = HashFuc1()(k) % Size;//匿名对象,字符串转整形
		size_t PosHash2 = HashFuc2()(k) % Size;
		size_t PosHash3 = HashFuc3()(k) % Size;
		cout << "Test:" << PosHash1 << " " << PosHash2 << " " << PosHash3 << endl;
		_bitSets.Set(PosHash1);
		_bitSets.Set(PosHash2);
		_bitSets.Set(PosHash3);
	}

	bool Find(const Key& k)//true在，false不在。只要有一个映射不存在，就一定不在
	{
		size_t PosHash1 = HashFuc1()(k) % Size;//匿名对象,字符串转整形
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
		return true;//三个位都在，说明可能在。仍然存在冲突
	}
private:
	NUC::BitSet<Size>_bitSets;
};