#include<iostream>

using namespace std;

//三叉链,这里插入方式按照搜索二叉树key模型的插入规则来实现
template<class key>
struct BSTNode
{
	BSTNode* left;
	BSTNode* right;
	BSTNode* parent;
	key val;
	BSTNode(const key& _val) :left(nullptr), right(nullptr), parent(nullptr), val(_val) {}
};

template<class key>
class BSTree
{
public:
	typedef BSTNode<key> Node;

	BSTree() :Head(nullptr) {}

	//插入二叉树,不允许插入相同的值
	bool Insert(const key& _val)
	{
		if (Head == nullptr)
		{
			Head = new Node(_val);
			return true;
		}
		else
		{
			Node* tmp = Head;
			Node* Bef = nullptr;
			while (tmp != nullptr)
			{
				if (tmp->val > _val)
				{
					Bef = tmp;
					tmp = tmp->left;
				}
				else if (tmp->val < _val)
				{
					Bef = tmp;
					tmp = tmp->right;
				}
				else//找到相同的值
				{
					cout << "数字重复" << endl;
					return false;
				}
			}
			Node* cur = new Node(_val);
			cur->parent = Bef;
			if (Bef->val > _val)
			{
				Bef->left = cur;
			}
			else
			{
				Bef->right = cur;
			}
			return true;
		}
	}

	//查找节点，返回节点指针
	Node* Find(const key& pos)
	{
		Node* find = Head;
		while (find != nullptr)
		{
			if (find->val > pos)
			{
				find = find->left;
			}
			else if (find->val < pos)
			{
				find = find->right;
			}
			else //找到了
			{
				return find;
			}
		}
		cout << "树中无此数字" << endl;
		return find;
	}

	//删除节点

	//中序打印二叉树
	void PrintTree()
	{
		_PrintTree(Head);
		cout << endl;
	}
private:
	Node* Head;
	void _PrintTree(Node* _head)//中序
	{
		if (_head == nullptr)
			return;
		_PrintTree(_head->left);
		cout << _head->val << " ";
		_PrintTree(_head->right);
	}
};

int main()
{
	BSTree<int>T;
	T.Insert(10);
	T.Insert(1);
	T.Insert(1);
	T.Insert(3);
	T.Insert(11);
	T.PrintTree();
	if (T.Find(11) != nullptr&&T.Find(10000)==nullptr)
	{
		cout << "查找函数正确" << endl;
	}
	else
	{
		cout << "查找函数不正确" << endl;
	}
	return 0;
}