#include"Base_RBTree.h"

namespace dodamce
{
	template<class key>
	class set
	{
		struct KeyOfSet
		{
			const key& operator()(const key& k)//对括号运算符重载
			{
				return k;
			}
		};
	public:
		typedef typename RBTree<const key, key, KeyOfSet>::iterator iterator;/*声明迭代器类型*/

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
		//调用基本红黑树模板
		RBTree<const key, key,KeyOfSet>_t;
	};
}