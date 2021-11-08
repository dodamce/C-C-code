#include"C++_AVL.h"
#include<vector>



void TestAVL_Insert()//检测插入AVL树的操作是否正确,并且检查是否是AVL树
{
	vector<int>Arr = { 16, 4, 2,29, 9, 26, 10, 25 };
	AVLTree<int, int>AVL;
	for (const auto& e : Arr)
	{
		AVL.Insert(make_pair(e, 1));
		//cout << "插入" << e << "->" << AVL.IsAVLTree() << endl;
	}
	AVL.PrintTree();
	if (AVL.IsAVLTree())
	{
		cout << "AVL树" << endl;
	}

	//测试修改AVL树的值
	AVL[0] = 100;
	AVL[2] = 30;
	AVL.PrintTree();
}

int main()
{
	TestAVL_Insert();
	return 0;
}