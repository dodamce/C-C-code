#include"TreeNode.h"

void test1(BTNode*Tree)
{
	BinaryTreePrevOrder(Tree);
	printf("\n");
	BinaryTreeInOrder(Tree);
	printf("\n");
	BinaryTreePostOrder(Tree);
	printf("\n");
	BinaryTreeLevelOrder(Tree);
	int Size = BinaryTreeSize(Tree);
	int LeaveSize = BinaryTreeLeafSize(Tree);
	int LeaveKSize = BinaryTreeLevelKSize(Tree, 2);
	//BinaryTreeDestory(&Tree);
	if (BinaryTreeComplete(Tree))
	{
		printf("完全二叉树\n");
	}
	else
	{
		printf("非完全二叉树");
	}
	BinaryTreeDestory(&Tree);
}

int main()
{
	BTDataType a[] = "ABD##E#H##CF##G##";
	int i = 0;
	BTNode* Tree = BinaryTreeCreate(a, &i);
	test1(Tree);
	return 0;
}