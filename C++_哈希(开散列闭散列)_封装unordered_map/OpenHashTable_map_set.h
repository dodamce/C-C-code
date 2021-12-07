#pragma once

#include<iostream>
#include<vector>

using namespace std;

namespace OpenHash
{
	template<class Value>
	struct HashDate
	{
		HashDate<Value>* _next;
		Value _kv;
		HashDate(const Value& Date) :_next(nullptr), _kv(Date) {}
	};

	//Ĭ�Ϸº���
	template<class Key>
	struct HashKey
	{
		int operator()(const Key& key) { return key; }
	};
	//�ػ��ַ���
	template<>struct HashKey<string>
	{
		int operator()(const string& Str)
		{
			int Sum = 0;
			for (size_t i = 0; i < Str.size(); i++)
			{
				Sum += ((i + 1) * Str[i]);//���������ͻ
			}
			return Sum;
		}
	};

	//ǰ������
	template<class Key,class Value,class KeyOfValue,class HashFuc>
	class Hash;
	//��ϣ������
	template<class Key, class Value, class KeyOfValue, class HashFuc = HashKey<Key>>
	struct _HashIterator
	{
		typedef HashDate<Value> HashDate;
		typedef _HashIterator<Key, Value, KeyOfValue, HashFuc> Self;
		typedef Hash<Key, Value, KeyOfValue, HashFuc> HashTable;
		HashDate* Node;
		HashTable* _table;
		_HashIterator(HashDate* Ptr, HashTable* Table) :Node(Ptr), _table(Table) {}
		Value& operator*()
		{
			return Node->_kv;
		}
		Value* operator->()
		{
			return &(Node->_kv);
		}
		bool operator ==(const Self& s)const
		{
			return Node == s.Node;
		}
		bool operator !=(const Self& s)const
		{
			return Node != s.Node;
		}

		Self& operator++()//ǰ��++
		{
			if (Node->_next != nullptr)
			{
				Node = Node->_next;
			}
			else
			{
				size_t Pos = KeyOfValue()(Node->_kv) % _table->_Table.size();
				size_t NewPos = Pos + 1;
				while (NewPos < _table->_Table.size())
				{
					if (_table->_Table[NewPos] == nullptr)
					{
						++NewPos;
					}
					else
					{
						Node = _table->_Table[NewPos];
						return *this;
					}
				}
				Node = nullptr;
			}
			return *this;
		}
	};

	template<class Key, class Value, class KeyOfValue, class HashFuc = HashKey<Key>>
	class Hash
	{
		typedef HashDate<Value> HashDate;
		template<class Key, class Value, class KeyOfValue, class HashFuc>
		friend struct _HashIterator;
	public:
		typedef _HashIterator<Key, Value, KeyOfValue, HashFuc> iterator;
		Hash() :_size(0) { _Table.resize(4); }

		//Hash() = default;//��ʽ�ñ���������Ĭ�Ϲ��캯��

		Hash(const Hash<Key, Value, KeyOfValue, HashFuc>& dev)
		{
			_size = dev._size;
			_Table.resize(dev._Table.size());
			for (size_t i = 0; i <dev._Table.size(); i++)
			{
				HashDate* cur = dev._Table[i];
				while (cur != nullptr)
				{
					HashDate* copy = new HashDate(cur->_kv);
					copy->_next = _Table[i];
					_Table[i] = copy;
					cur = cur->_next;
				}
			}
		}

		Hash& operator=(Hash<Key, Value, KeyOfValue> dev)//��ֵ��
		{
			_Table.swap(dev._Table);
			std::swap(_size, dev._size);
			return *this;
		}

		~Hash()
		{
			for (size_t i = 0; i < _Table.size(); i++)
			{
				HashDate* cur = _Table[i];
				if (cur != nullptr)
				{
					HashDate* next = cur->_next;
					delete cur;
					cur = next;
				}
				_Table[i] = nullptr;
			}

		}

		iterator begin()
		{
			for (size_t i = 0; i < _Table.size(); i++)
			{
				if (_Table[i] != nullptr)
				{
					return iterator(_Table[i], this);//this�ǹ�ϣ��
				}
			}
			return end();
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		pair<iterator,bool> Insert(const Value& Date)
		{
			HashFuc kot;
			KeyOfValue Type;
			iterator Ptr = Find(Type(Date));
			if (Ptr != end()) { return make_pair(Ptr, false); }//����������
			if (_size == _Table.size())//��������̫������
			{
				vector<HashDate*>NewVector;
				NewVector.resize(_Table.size() * 2);
				//����ԭ����
				for (size_t i = 0; i < _Table.size(); i++)
				{
					HashDate* cur = _Table[i];
					while (cur != nullptr)
					{
						HashDate* next = cur->_next;
						size_t idex = kot(Type(cur->_kv)) % NewVector.size();
						cur->_next = NewVector[idex];
						NewVector[idex] = cur;
						cur = next;
					}
				}
				_Table.swap(NewVector);
			}
			size_t Pos = kot(Type(Date)) % _Table.size();
			HashDate* cur = new HashDate(Date);//ͷ��
			cur->_next = _Table[Pos];
			_Table[Pos] = cur;
			++_size;
			return make_pair(iterator(_Table[Pos], this), true);
		}

		iterator Find(const Key& key)
		{
			HashFuc kot;
			KeyOfValue Type;
			size_t Pos = kot(key) % _Table.size();
			HashDate* cur = _Table[Pos];
			while (cur != nullptr)
			{
				if (Type(cur->_kv) == key)
				{
					break;
				}
				cur = cur->_next;
			}
			return iterator(cur, this);
		}

		bool Erase(const Key& key)
		{
			HashFuc kot;
			size_t Pos = kot(Type(key)) % _Table.size();
			HashDate* cur = _Table[Pos];
			HashDate* bef = nullptr;
			while (cur->_kv.first != key)
			{
				bef = cur;
				cur = cur->_next;
			}
			if(cur!=nullptr)
			{
				if (bef == nullptr) {//ɾ����һ���ڵ�
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
				cout << "�޴�Ԫ��" << endl;
				return false;
			}
		}
	private:
		vector<HashDate*>_Table;
		size_t _size;
	};
}