#include"Base_RBTree.h"//测试封装的map与set与基本红黑树
#include"Map.h"
#include"Set.h"

//void Test()//测试改造的基本红黑树
//{
//	int arr[] = { 2,4,1,7,5,10,6,3 };
//	RBTree<int, int>t;
//	for(const auto&e:arr)
//	{
//		t.Insert(e);
//	}
//}

void Test1()//测试map与set的插入
{
	dodamce::map<int, char>t;
	t.insert(make_pair(1, 'a'));
	t.insert(make_pair(3, 'a'));
	t.insert(make_pair(2,'a'));
	dodamce::set<int>t2;
	t2.insert(10);
	t2.insert(1);
	t2.insert(5);
	//测试迭代器遍历set
	dodamce::set<int>::iterator ptr = t2.begin();
	while (ptr != t2.end())
	{
		cout << *ptr << " " << endl;
		++ptr;
	}
}

int main()
{
	//Test();
	Test1();
	return 0;
}