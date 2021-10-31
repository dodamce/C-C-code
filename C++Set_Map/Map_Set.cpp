#include<iostream>
#include<map>
#include<set>
#include<string>

using namespace std;

//序列式容器:vector deque list ->内存中存储数据

//关联式容器:map/set    /unordered_map/unordered_set ->搜索内存中储存的数据
//     平衡二叉搜索树        哈希表


/*

二叉搜索树的Key模型 ->set

二叉搜索树的Key_Value模型 ->map

*/


void Test_Set1()//set模型插入(二叉搜索树插入模型)，set打印(中序遍历二叉搜索树)
{
	set<int> s;
	s.insert(10);
	s.insert(4);
	s.insert(1);
	s.insert(6);
	s.insert(2);
	s.insert(13);
	//底层是平衡二叉搜索树，STL中迭代器遍历相当与中序遍历,打印后就变成有序的了
	set<int>::iterator ptr = s.begin();
	while (ptr != s.end())
	{
		cout << *ptr << endl;
		ptr++;
	}
	//C++11范围for打印，底层实现为迭代器
	cout << endl;
	for (auto& e : s)//引用减少拷贝
	{
		cout << e << endl;
	}
}

void Test_Set2()//验证set的去重功能
{
	//set插入不能有重复，重复插入会插入失败

	set<int>s;
	s.insert(19);
	s.insert(19);//只会保留一份19
	for (auto& e : s)
		cout << e << endl;
}

void Test_Set3()//set应用，单词匹配(搜索树的查找)
{
	set<string>WordStr;
	WordStr.insert("Hello");
	WordStr.insert("Left");
	WordStr.insert("Right");
	WordStr.insert("Map");
	WordStr.insert("Set");
	//...导入单词
	string Word;
	cin >> Word;
	set<string>::iterator ptr = WordStr.find(Word);//迭代器查找
    //set->find()查找成功返回找到位置的迭代器，失败返回这个容器的末尾
	if (ptr != WordStr.end())
	{
		cout << "单词匹配成功" << endl;
	}
	else
	{
		cout << "单词匹配错误" << endl;
	}
}

void Test_Set4()//反向遍历搜索树(反向迭代器)反向打印二叉搜索树
{
	set<int> s;
	s.insert(10);
	s.insert(4);
	s.insert(1);
	s.insert(6);
	s.insert(2);
	s.insert(13);
	set<int>::reverse_iterator bptr = s.rbegin();//反向迭代器
	while (bptr != s.rend())
	{
		cout << *bptr << endl;
		bptr++;
	}
}

//注意：set对应的是搜索树的key模型，插入后的数值不能被修改，否则可能破坏搜索树的性质
/*
   set<int>a;
   a.insert(1);
   set<int>::iterate p=a.begin();
   *p+=1;（错误，set插入的值不能修改）
*/

template<class T>//打印set模板函数
void PrintSet(const set<T>& tmp)
{
	for (const auto& e : tmp)
		cout << e << " ";
	cout << endl;
}

void Test_Set5()//set的删除操作
{
	set<int> s;
	s.insert(10);
	s.insert(4);
	s.insert(1);
	s.insert(6);
	s.insert(2);
	s.insert(13);
	for (const auto& e : s)
		cout << e << endl;
	s.erase(10);//直接删除值
	PrintSet(s);
	s.erase(s.find(2));//删除迭代器位置的元素
	PrintSet(s);
	//删除没有的数值
	//s.erase(100);->没有找到不执行任何操作
	//s.erase(s.find(100));->调用find函数找不到会出现非法访问内存问题
}

void Test_Set6()
{
	set<int> s;
	s.insert(10);
	s.insert(4);
	s.insert(1);
	set<int>s2;
	s2.insert(6);
	s2.insert(2);
	s2.insert(13);
	PrintSet(s); PrintSet(s2);
	cout << endl;
	s.swap(s2);
	PrintSet(s); PrintSet(s2);
//注意在C++11前调用容器自己的swap和std::swap不同，效率比std::swap高
}

//上面的为set其插入的数据不能重复，否则插入无效

//下面的multiset结构操作和set相同，但是这个容器数据可以重复，查找只返回第一个找到这个元素的迭代器
//删除时删除所有相同值的元素

template<class T>
void PrintMiltsSet(const multiset<T>& s)
{
	for (const auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

void Test_MiltisSet7()//测试multiset的操作
{
	set<int>s;
	s.insert(10);
	s.insert(10);
	s.insert(20);//只会保留一份10
	PrintSet(s);
	multiset<int>s2;//允许冗余，2份10
	s2.insert(10);
	s2.insert(10);
	s2.insert(20);
	PrintMiltsSet(s2);
	//查找
	multiset<int>::iterator ptr = s2.find(10);
	while (*ptr == 10)//验证multiset查找是找第一个对应元素,最后会打印两份10
	{
		cout << "Find:" << *ptr << endl;
		ptr++;
	}
	//cout << s2.count(10) << endl;//打印对应元素的个数
	s.erase(10);
	PrintSet(s);
	s2.erase(10);
	PrintMiltsSet(s2);
}


int main()
{
	//Test_Set1();
	//Test_Set2();
	//Test_Set3();
	//Test_Set4();
	//Test_Set5();
	//Test_Set6();
	//Test_MiltisSet7();

	return 0;
}