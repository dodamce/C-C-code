#include"Binary_TreeR.h"

//��Ԫ����

void Test1()//���Բ��룬���ң���ӡ
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

void Test2()//����ɾ������
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