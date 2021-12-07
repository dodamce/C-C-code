#pragma once

#include"OpenHashTable_map_set.h"


namespace dodamce
{
	template<class Key>
	class unordered_set
	{
		struct KeyOfSet
		{
			const Key& operator()(const Key& Val)
			{
				return Val;
			}
		};
	public:
		typedef typename OpenHash::Hash<Key, Key, KeyOfSet>::iterator iterator;

		iterator begin()
		{
			return _Date.begin();
		}

		iterator end()
		{
			return _Date.end();
		}

		pair<iterator,bool> Insert(const Key& Date)
		{
			return _Date.Insert(Date);
		}
	private:
		OpenHash::Hash<Key, Key, KeyOfSet>_Date;
	};
}