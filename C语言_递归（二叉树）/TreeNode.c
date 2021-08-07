#include"TreeNode.h"
// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTNode* BinaryTreeCreate(BTDataType* a, int* pi)
{
	if (a[*pi] == '#')
	{
		(*pi) += 1;
		return NULL;
	}
	BTNode* NewTree = (BTNode*)malloc(sizeof(BTNode));
	if (NewTree == NULL)
	{
		exit(-1);
	}
	else
	{
		NewTree->_data = a[*pi];
		*pi += 1;
		NewTree->_left = BinaryTreeCreate(a, pi);
		NewTree->_right = BinaryTreeCreate(a, pi);
		return NewTree;
	}
}
// 二叉树销毁
void BinaryTreeDestory(BTNode** root)
{
	if (*root == NULL)
	{
		return;
	}
	BinaryTreeDestory(&((*root)->_left));
	BinaryTreeDestory(&((*root)->_right));
	free(*root);
	*root = NULL;
}
// 二叉树节点个数
int BinaryTreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right) + 1;
}
// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->_left == NULL && root->_right == NULL)
	{
		return 1;
	}
	return BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right);
}
// 二叉树第k层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}
// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->_data == x)
	{
		return root;
	}
	BTNode* left = BinaryTreeFind(root->_left, x);
	if (left)
	{
		return left;
	}
	BTNode* right = BinaryTreeFind(root->_right, x);
	if (right)
	{
		return right;
	}
	return NULL;
}
// 二叉树前序遍历 
void BinaryTreePrevOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c  ", root->_data);
	BinaryTreePrevOrder(root->_left);
	BinaryTreePrevOrder(root->_right);
}
// 二叉树中序遍历
void BinaryTreeInOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	BinaryTreeInOrder(root->_left);
	printf("%c  ",root->_data);
	BinaryTreeInOrder(root->_right);
}
// 二叉树后序遍历
void BinaryTreePostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	BinaryTreePostOrder(root->_left);
	BinaryTreePostOrder(root->_right);
	printf("%c  ",root->_data);
}
// 层序遍历
void BinaryTreeLevelOrder(BTNode* root)
{
	assert(root);
	Qlist p;
	QlistInit(&p);
	if (root)
	{
		QlistPush(&p, root);
	}
	while (QlistEmpty(&p))
	{
		BTNode* front = QlistFront(&p);
		printf("%c ",front->_data);
		QlistPup(&p);
		if (root->_left)
		{
			QlistPush(&p, root->_left);
		}
		if (root->_right)
		{
			QlistPush(&p, root->_right);
		}
	}
	QlistDestory(&p);
}

// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root)
{
	if (root == NULL)
	{
		return 1;
	}
	if (root->_left == root->_right && root->_left == NULL)
	{
		return 1;
	}
	if ((root->_left == NULL && root->_right != NULL) || root->_left != NULL && root->_right == NULL)
	{
		return 0;
	}
	return BinaryTreeComplete(root->_left) && BinaryTreeComplete(root->_right);
}