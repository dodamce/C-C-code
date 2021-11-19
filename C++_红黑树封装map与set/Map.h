#include"Base_RBTree.h"

namespace dodamce
{
	template<class key, class value>
	class map
	{
		struct KeyOfMap
		{
			const key& operator()(const pair<const key, value>kv)
			{
				return kv.first;
			}
		};
	public:
		bool insert(const pair<const key, value>& val)//mapµÄ²åÈë
		{
			_t.Insert(val);
			return true;
		}
	private:
		RBTree<const key, pair<const key, value>,KeyOfMap>_t;
	};
}