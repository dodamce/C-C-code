#include"Binary_Tree.h"

#define MAXSIZE 10

#define TESTSIZE 1

//单元测试
void Test1()//测试插入与打印操作
{
	My_Key::BSTree<int>Tree;
	Tree.Insert(3);
	Tree.Insert(2);
	Tree.Insert(0);
	Tree.Insert(6);
	Tree.Insert(0);
	Tree.PrintBSTree();
	Tree.Insert(6);
	Tree.PrintBSTree();
}

void Test2()//测试查找操作
{
	My_Key::BSTree<int>Tree;
	srand((unsigned int)time(nullptr));
	int arr[MAXSIZE] = { 0 };//随机填充数组
	for (int i = 0; i < MAXSIZE; i++)
	{
		arr[i] = rand() % 100 + 1;//控制随机数范围
		Tree.Insert(arr[i]);
	}
	Tree.PrintBSTree();
	//生成随机查找数字
	My_Key::BSTree<int>* TreePtr = nullptr;
	TreePtr = (My_Key::BSTree<int>*)Tree.Find(arr[(rand() % MAXSIZE)]);
	//这里需要从My_Key::BSTree<int>*到BSTree<int>*必须要强转一下，我当时没想到命名空间会出现这样的问题，但是不想大改了
	if (TreePtr == nullptr)
		cout << "没有这个数字" << endl;
	else
		cout << "BSTree有这个数字" << endl;
	TreePtr= (My_Key::BSTree<int>*)Tree.Find(1001);
	if (TreePtr == nullptr)
		cout << "没有这个数字" << endl;
	else
		cout << "BSTree有这个数字" << endl;
}

void Test3()//测试删除节点功能
{
	My_Key::BSTree<int>Tree;
	int arr[TESTSIZE] = { 2 };
	for (int i = 0; i < TESTSIZE; i++)
	{
		Tree.Insert(arr[i]);
	}
	Tree.PrintBSTree();
	cout << endl;
	for (int i = 0; i < TESTSIZE; i++)
	{
		Tree.Erase(arr[i]);
		Tree.PrintBSTree();
		cout << endl;
	}
	cout << endl;
	srand((unsigned int)time(nullptr));
	int arr2[MAXSIZE] = { 0 };//随机填充数组
	for (int i = 0; i < MAXSIZE; i++)
	{
		arr2[i] = rand() % 100 + 1;//控制随机数范围
		Tree.Insert(arr2[i]);
	}
	Tree.PrintBSTree();
	cout << endl;
	for (int i = 0; i < MAXSIZE; i++)
	{
		Tree.Erase(arr2[i]);
		Tree.PrintBSTree();
		cout << endl;
	}
}

int main()
{
	//Test1();
	//Test2();
	Test3();
}