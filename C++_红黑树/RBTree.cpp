#include"RBTree.h"
#include<stdlib.h>
#include<time.h>

void Test()//²âÊÔ²åÈë´òÓ¡ºìºÚÊ÷£¬ÅĞ¶ÏºìºÚÊ÷
{
	int arr[] = { 3,2,5,1,7,11,6,15 };
	RBTree<int, int>t;
	for (const auto& e : arr)
	{
		t.Insert(make_pair(e, e));
	}
	t.PrintInord();
	if (t.CheckRBTree())
	{
		cout << "Is RedBlackTree" << endl;
	}
	else
	{
		cout << "Is Not RedBlackTree" << endl;
	}
}

//Ëæ»ú²åÈëºìºÚÊ÷
void Test2()
{
	int n = 100000;
	RBTree<int, int>t;
	srand((unsigned int)time(0));
	for (int i = 0; i < n; i++)
	{
		int tmp = rand();
		t.Insert(make_pair(tmp,tmp));
	}
	t.PrintInord();
}

int main()
{
	//Test();
	Test2();
	return 0;
}