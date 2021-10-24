#include"Binary_Tree.h"

#define MAXSIZE 10

#define TESTSIZE 1

//��Ԫ����
void Test1()//���Բ������ӡ����
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

void Test2()//���Բ��Ҳ���
{
	My_Key::BSTree<int>Tree;
	srand((unsigned int)time(nullptr));
	int arr[MAXSIZE] = { 0 };//����������
	for (int i = 0; i < MAXSIZE; i++)
	{
		arr[i] = rand() % 100 + 1;//�����������Χ
		Tree.Insert(arr[i]);
	}
	Tree.PrintBSTree();
	//���������������
	My_Key::BSTree<int>* TreePtr = nullptr;
	TreePtr = (My_Key::BSTree<int>*)Tree.Find(arr[(rand() % MAXSIZE)]);
	//������Ҫ��My_Key::BSTree<int>*��BSTree<int>*����Ҫǿתһ�£��ҵ�ʱû�뵽�����ռ��������������⣬���ǲ�������
	if (TreePtr == nullptr)
		cout << "û���������" << endl;
	else
		cout << "BSTree���������" << endl;
	TreePtr= (My_Key::BSTree<int>*)Tree.Find(1001);
	if (TreePtr == nullptr)
		cout << "û���������" << endl;
	else
		cout << "BSTree���������" << endl;
}

void Test3()//����ɾ���ڵ㹦��
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
	int arr2[MAXSIZE] = { 0 };//����������
	for (int i = 0; i < MAXSIZE; i++)
	{
		arr2[i] = rand() % 100 + 1;//�����������Χ
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