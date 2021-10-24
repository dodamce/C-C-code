#include"Binary_TreeR.h"

//单元测试

void Test1()//测试插入，查找，打印
{
	MyR_Key::BSTree<int>Tree;
	for (int i = 10; i > 0; i--)
	{
		Tree.Insert(i);
		Tree.PrintBSTree();
	}
	if (Tree.Find(5) && (!Tree.Find(11)))
	{
		cout << "Pass Find" << endl;
	}
}

void Test2()//测试删除操作
{
	MyR_Key::BSTree<int>Tree;
	for (int i = 10; i > 0; i--)
	{
		Tree.Insert(i);
	}
	Tree.PrintBSTree();
	for (int i = 0; i < 10; i++)
	{
		Tree.Erase(i);
		Tree.PrintBSTree();
	}
}

//测试拷贝构造函数和运算符重载
void Test3()
{
	MyR_Key::BSTree<int>Tree;
	for (int i = 10; i > 0; i--)
	{
		Tree.Insert(i);
	}
	MyR_Key::BSTree<int>TreeCopy(Tree);
	TreeCopy.PrintBSTree();
	MyR_Key::BSTree<int>TreeSame;
	TreeSame = TreeCopy;
	TreeSame.PrintBSTree();
}

int main()
{
	//Test1();
	//Test2();
	Test3();
}