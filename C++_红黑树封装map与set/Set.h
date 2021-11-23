#include"Base_RBTree.h"

namespace dodamce
{
	template<class key>
	class set
	{
		struct KeyOfSet
		{
			const key& operator()(const key& k)//���������������
			{
				return k;
			}
		};
	public:
		typedef typename RBTree<const key, key, KeyOfSet>::iterator iterator;/*��������������*/
		typedef typename RBTree<const key, key, KeyOfSet>::reserve_iterator reserve_iterator;
		iterator begin()
		{
			return _t.begin();
		}

		reserve_iterator rbegin()
		{
			return _t.rbegin();
		}

		iterator end()
		{
			return _t.end();
		}

		reserve_iterator rend()
		{
			return _t.rend();
		}

		pair<iterator,bool> insert(const key& val)
		{
			return _t.Insert(val);
		}
	private:
		//���û��������ģ��
		RBTree<const key, key,KeyOfSet>_t;
	};
}