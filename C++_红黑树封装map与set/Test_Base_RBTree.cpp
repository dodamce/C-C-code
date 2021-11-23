#include"Base_RBTree.h"//测试封装的map与set与基本红黑树
#include"Map.h"
#include"Set.h"
//#include"tmp_map.h"

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
	cout << endl;
	//迭代器遍历map
	dodamce::map<int, char>::iterator mptr = t.begin();
	while (mptr != t.end())
	{
		cout << mptr->first << "->" << mptr->second << endl;
		++mptr;
	}
	cout << endl;
	//反向迭代器遍历
	dodamce::set<int>::reserve_iterator rptr = t2.rbegin();
	while (rptr != t2.rend())
	{
		cout << *rptr << " " << endl;
		++rptr;
	}
	//反向迭代器遍历
	dodamce::map<int, char>::reserve_iterator mrptr = t.rbegin();
	while (mrptr != t.rend())
	{
		cout << mrptr.operator->().first << "->" << mrptr.operator->().second << endl;
		++mrptr;
	}
	dodamce::map<string, string>s;
	s["abc"] = "def";
}

//测试map[]运算符重载

//void Test2()//map的迭代器
//{
//	dodamce::map<int, char>t;
//	t.insert(make_pair(1, 'a'));
//	t.insert(make_pair(3, 'a'));
//	t.insert(make_pair(2, 'a'));
//	dodamce::map<int, char>::iterator ptr = t.begin();
//	while (ptr != t.end())
//	{
//		cout << ptr->first << "->" << ptr->second << endl;
//		++ptr;
//	}
//}

//void Test3()
//{
//	bit::::map<string, string>s;
//	s["def"] = "abc";
//}

int main()
{
	//Test();
	Test1();
	//Test2();
	//Test3();
	return 0;
}