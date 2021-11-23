#include"Base_RBTree.h"

namespace dodamce
{
	template<class key, class value>
	class map
	{
		struct KeyOfMap
		{
			const key& operator()(const pair<const key, value>&kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<key, pair<const key,value>, KeyOfMap>::iterator iterator;
		typedef typename RBTree<key, pair<const key, value>, KeyOfMap>::reserve_iterator reserve_iterator;
		
		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		reserve_iterator rbegin()
		{
			return _t.rbegin();
		}

		reserve_iterator rend()
		{
			return _t.rend();
		}

		pair<iterator,bool> insert(const pair<const key, value>& val)//map的插入
		{
			return _t.Insert(val);
		}

		value& operator[](const key&Key)
		{
			pair<iterator, bool> ret = insert(make_pair(Key,value()));//value模板类型的构造函数
			return ret.first->second;
		}
	private:
		RBTree<key, pair<const key, value>,KeyOfMap>_t;
	};
}