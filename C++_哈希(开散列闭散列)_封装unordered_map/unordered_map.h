#pragma once

#include"OpenHashTable_map_set.h"

namespace dodamce
{
	template<class Key, class Value>
	class unordered_map
	{
		struct KeyOfMap
		{
			const Key& operator()(const pair<Key, Value>& Val)
			{
				return Val.first;
			}
		};
	public:
		typedef typename OpenHash::Hash<Key, pair<Key, Value>, KeyOfMap>::iterator iterator;

		iterator begin()
		{
			return _Date.begin();
		}

		iterator end()
		{
			return _Date.end();
		}

		Value& operator[](const Key& pos)
		{
			pair<iterator, bool>idex = _Date.Insert(make_pair(pos, Value()));
			return idex.first->second;
		}

		pair<iterator, bool> Insert(const pair<Key, Value>& Date)
		{
			return _Date.Insert(Date);
		}
	private:
		OpenHash::Hash<Key, pair<Key, Value>, KeyOfMap>_Date;
	};
}