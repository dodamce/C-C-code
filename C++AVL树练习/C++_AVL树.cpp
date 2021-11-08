#include"C++_AVL.h"
#include<vector>



void TestAVL_Insert()//������AVL���Ĳ����Ƿ���ȷ,���Ҽ���Ƿ���AVL��
{
	vector<int>Arr = { 16, 4, 2,29, 9, 26, 10, 25 };
	AVLTree<int, int>AVL;
	for (const auto& e : Arr)
	{
		AVL.Insert(make_pair(e, 1));
		//cout << "����" << e << "->" << AVL.IsAVLTree() << endl;
	}
	AVL.PrintTree();
	if (AVL.IsAVLTree())
	{
		cout << "AVL��" << endl;
	}

	//�����޸�AVL����ֵ
	AVL[0] = 100;
	AVL[2] = 30;
	AVL.PrintTree();
}

int main()
{
	TestAVL_Insert();
	return 0;
}