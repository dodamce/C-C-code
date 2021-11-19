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

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		bool insert(const key& val)
		{
			_t.Insert(val);
			return true;
		}
	private:
		//���û��������ģ��
		RBTree<const key, key,KeyOfSet>_t;
	};
}