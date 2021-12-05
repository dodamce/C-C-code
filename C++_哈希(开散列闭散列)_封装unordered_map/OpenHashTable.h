#pragma once

#include<iostream>
#include<vector>

using namespace std;

namespace OpenHash
{
	template<class Key,class Value>
	struct HashDate
	{
		HashDate<Key, Value>* _next;
		pair<Key, Value>_kv;
		HashDate(const pair<Key, Value>& Date) :_next(nullptr), _kv(Date) {}
	};

	//默认仿函数
	template<class Key>
	struct HashKey
	{
		int operator()(const Key& key) { return key; }
	};
	//特化字符串
	template<>struct HashKey<string>
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

	template<class Key, class Value,class HashFuc=HashKey<Key>>
	class Hash
	{
		typedef HashDate<Key, Value> HashDate;
	public:
		Hash() :_size(0) { _Table.resize(4); }
		bool Insert(const pair<Key, Value>& Date)
		{
			HashFuc kot;
			if (Find(Date.first)) { return false; }//不允许冗余
			if (_size == _Table.size())//负载因子太大扩容
			{
				vector<HashDate*>NewVector;
				NewVector.resize(_Table.size() * 2);
				//遍历原数组
				for (int i = 0; i < _Table.size(); i++)
				{
					HashDate* cur = _Table[i];
					while (cur != nullptr)
					{
						HashDate* next = cur->_next;
						size_t idex = kot(cur->_kv.first) % NewVector.size();
						cur->_next = NewVector[idex];
						NewVector[idex] = cur;
						cur = next;
					}
				}
				_Table.swap(NewVector);
			}
			size_t Pos = kot(Date.first) % _Table.size();
			HashDate* cur = new HashDate(Date);//头插
			cur->_next = _Table[Pos];
			_Table[Pos] = cur;
			++_size;
			return true;
		}

		HashDate* Find(const Key& key)
		{
			HashFuc kot;
			size_t Pos = kot(key) % _Table.size();
			HashDate* cur = _Table[Pos];
			while (cur != nullptr)
			{
				if (cur->_kv.first == key)
				{
					break;
				}
				cur = cur->_next;
			}
			return cur;
		}

		bool Erase(const Key& key)
		{
			size_t Pos = key % _Table.size();
			HashDate* cur = _Table[Pos];
			HashDate* bef = nullptr;
			while (cur->_kv.first != key)
			{
				bef = cur;
				cur = cur->_next;
			}
			if(cur!=nullptr)
			{
				if (bef == nullptr) {//删除第一个节点
					_Table[Pos] = cur->_next;
				}
				else {
					bef->_next = cur->_next;
				}
				delete cur;
				--_size;
				return true;
			}
			else
			{
				cout << "无此元素" << endl;
				return false;
			}
		}

		void PrintHashTable()//测试用接口
		{
			for (int i = 0; i < _Table.size(); i++)
			{
				if (_Table[i] == nullptr)
				{
					cout << "nullptr" << " ";
				}
				else
				{
					HashDate* cur = _Table[i];
					while (cur != nullptr)
					{
						cout << _Table[i]->_kv.first << "->" << _Table[i]->_kv.second << " ";
						cur = cur->_next;
					}
				}
			}
			cout << endl;
		}
	private:
		vector<HashDate*>_Table;
		size_t _size;
	};
}