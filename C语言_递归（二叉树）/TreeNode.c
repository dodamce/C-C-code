#include"TreeNode.h"
// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
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
// ����������
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
// �������ڵ����
int BinaryTreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right) + 1;
}
// ������Ҷ�ӽڵ����
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
// ��������k��ڵ����
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
// ����������ֵΪx�Ľڵ�
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
// ������ǰ����� 
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
// �������������
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
// �������������
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
// �������
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

// �ж϶������Ƿ�����ȫ������
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