#include"Binary_TreeR.h"

//µ•‘™≤‚ ‘

void Test1()//≤‚ ‘≤Â»Î£¨≤È’“£¨¥Ú”°
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

void Test2()//≤‚ ‘…æ≥˝≤Ÿ◊˜
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

int main()
{
	//Test1();
	Test2();
}