#pragma once 

#include<iostream>
#include<vector>

using namespace std;

namespace CloseSpace//闭散列哈希
{
	enum State{EMPTY,EXITS,DELETE};//状态枚举
	template<class Key,class Value>
	struct HashDate
	{
		HashDate() :_state(EMPTY) {}
		pair<Key, Value>_kv;
		State _state;
	};

	template<class Key>
	struct HashKey//默认仿函数
	{
		int operator()(const Key _Key) { return _Key; }
	};
	//string特化
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

	template<class Key, class Value, class HashFuc = HashKey<Key>>
	class HashTable
	{
		typedef HashDate<Key, Value> HashDate;
	public:
		HashTable() :_size(0) { _Table.resize(10); }
		bool Insert(const pair<Key, Value>& kv)
		{
			HashFuc kot;
			if (Find(kv.first)) { return false; }//不允许冗余
			//计算负载因子>0.7增加哈希结构大小
			if ((double)_size / (double)_Table.size() > 0.7)
			{
				//增容
				HashTable<Key, Value, HashFuc> NewTable;
				NewTable._Table.resize(_Table.size() * 2);
				for (const auto& Date : _Table)
				{
					NewTable.Insert(Date._kv);
				}
				_Table.swap(NewTable._Table);
			}

			size_t Pos = kot(kv.first) % _Table.size();
			while (_Table[Pos]._state == EXITS)//线性探测
			{
				Pos++;
				Pos %= _Table.size();
			}
			_Table[Pos]._kv = kv;
			_Table[Pos]._state = EXITS;
			++_size;
			return true;
		}

		HashDate* Find(const Key& key)
		{
			HashFuc kot;
			size_t Pos = kot(key) % _Table.size();
			while (_Table[Pos]._state != EMPTY)
			{
				if (_Table[Pos]._state != DELETE && _Table[Pos]._kv.first == key)//找到了
				{
					return &_Table[Pos];
				}
				++Pos;
				Pos %= _Table.size();
			}
			return nullptr;
		}

		bool Erase(const Key& key)
		{
			HashDate* Pos = Find(key);
			bool IsErase = false;
			if (nullptr == Pos) 
			{ 
				cout << "不存在的值" << endl;
			}
			else
			{
				Pos->_state = DELETE;
				IsErase = true;
			}
			--_size;
			return IsErase;
		}

		void PrintHashTable()//测试接口
		{
			for (size_t i = 0; i < _Table.size(); i++)
			{
				if (_Table[i]._state == EXITS)
				{
					cout << _Table[i]._kv.first << "->" << _Table[i]._kv.second << " ";
				}
			}
			cout << endl;
		}

	private:
		vector<HashDate>_Table;
		size_t _size;//存放有效数据的个数
	};
}