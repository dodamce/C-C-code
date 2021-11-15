#pragma once

#include<iostream>
using namespace std;

enum Color
{
	RED = 0, BLACK,
};

template<class Key, class Value>
struct RBTreeNode
{
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;
	pair<Key, Value> _kv;
	Color col;
	RBTreeNode(const pair<Key, Value>& val)
		:_left(nullptr), _right(nullptr), _parent(nullptr), _kv(val), col(BLACK)//默认节点颜色
	{}
};

template<class Key, class Value>
class RBTree
{
	typedef RBTreeNode<Key, Value> Node;
public:
	RBTree() :_root(nullptr) {}

	~RBTree()
	{
		_Destory(_root);//后序遍历
		_root = nullptr;
	}

	bool CheckRBTree()
	{
		if (_root == nullptr)
		{
			return true;
		}
		else if(_root->col == RED)
		{
			cout << "根节点为红" << endl;
			return false;
		}
		//先记录最左节点黑的数量
		int NumBack = 0;
		Node* LeftBack = _root;
		while (LeftBack != nullptr)
		{
			if (LeftBack->col == BLACK)
			{
				NumBack++;
			}
			LeftBack = LeftBack->_left;
		}
		int Num = 0;//记录此时黑节点的个数
		return _CheckRBTree(_root, NumBack, Num);//递归函数
	}

	Node* Find(const Key& key)//通过键值查找,返回节点指针
	{
		Node* cur = _root;
		Node* ret = nullptr;
		while (cur != nullptr)
		{
			if (key > cur->_kv.first)
			{
				cur = cur->_right;
			}
			else if (key < cur->_kv.first)
			{
				cur = cur->_left;
			}
			else
			{
				ret = cur;
				break;
			}
		}
		return ret;
	}

	//打印红黑树
	void PrintInord()
	{
		return _PrintInord(_root);
	}

	pair<Node*, bool>Insert(const pair<Key, Value>val)//红黑树的插入
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			_root->col = BLACK;
			return make_pair(_root, true);
		}
		//二叉搜索树插入
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur != nullptr)
		{
			if (cur->_kv.first < val.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > val.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//键值重复,插入失败
			{
				return make_pair(cur, false);
			}
		}
		cur = new Node(val);
		cur->col = RED;
		if (parent->_kv.first > val.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		Node* End = cur;//记录插入位置的节点
		//控制路径
		while (parent != nullptr && parent->col == RED)
		{
			Node* GradParent = parent->_parent;
			if (parent == GradParent->_left)//关键看Uncle节点的颜色
			{
				Node* Uncle = GradParent->_right;
				//情况1：Uncle存在且为红
				if (Uncle && Uncle->col == RED)
				{
					parent->col = Uncle->col = BLACK;
					GradParent->col = RED;
					cur = GradParent;
					parent = cur->_parent;
				}
				else//Uncle不存在或Uncle存在为黑色
				{
					if (cur == parent->_left)//右高，进行右旋
					{
						_Single_Right(GradParent);
						GradParent->col = RED;
						parent->col = BLACK;
					}
					else//折线形状，左右双旋
					{
						_Single_Left(parent);
						_Single_Right(GradParent);
						cur->col = BLACK;
						parent->col = GradParent->col = RED;
					}
					break;//旋转后黑色节点个数不变，直接跳出循环
				}
			}
			else//parent=GradParent->_right
			{
				Node* Uncle = GradParent->_left;
				if (Uncle != nullptr && Uncle->col == RED)
				{
					Uncle->col = parent->col = BLACK;
					GradParent->col = RED;
					cur = GradParent;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)//左高，左旋
					{
						_Single_Left(GradParent);
						GradParent->col = RED;
						parent->col = BLACK;
					}
					else//折线,右左双旋
					{
						_Single_Right(parent);
						_Single_Left(GradParent);
						cur->col = BLACK;
						GradParent->col = RED;
					}
					break;
				}
			}
		}
		_root->col = BLACK;//将根的颜色变为黑色，防止上面的过程将根节点变为红色
		return make_pair(End, true);
	}
private:
	Node* _root;

	void _PrintInord(Node* root)
	{
		if (root == nullptr)
			return;
		_PrintInord(root->_left);
		cout << root->_kv.first << "->" << root->_kv.second << endl;
		_PrintInord(root->_right);
	}

	bool _CheckRBTree(Node* root, const int NumBack, int Num)
	{
		if (root == nullptr)
		{
			//检测这条路上黑节点个数和NumBack
			if (NumBack != Num)
			{
				cout << "黑色节点个数不相同" << endl;
				return false;
			}
			else
			{
				return true;
			}
		}
		//前序遍历
		if (root->col == RED && root->_parent->col == RED)
		{
			cout << "红色节点连续" << endl;
			return false;
		}
		else if (root->col == BLACK)
		{
			Num++;
		}
		return _CheckRBTree(root->_left, NumBack, Num) && _CheckRBTree(root->_right, NumBack, Num);
	}

	void _Destory(Node* root)//后序遍历
	{
		if (root == nullptr)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
	void _Single_Right(Node* parent)//右单旋根据图把对应关系连接起来
	{
		//记录要移动的节点
		Node* SubL = parent->_left;
		Node* SubLR = SubL->_right;

		//连接
		parent->_left = SubLR;
		if (SubL->_right != nullptr)//修改父指针
		{
			SubLR->_parent = parent;
		}
		//连接
		SubL->_right = parent;
		Node* GradParent = parent->_parent;//记录这个节点的父节点，为了修改根节点
		parent->_parent = SubL;//修改父指针
		//调整根节点
		if (parent == _root)//要旋转的节点为根节点
		{
			_root = SubL;
			SubL->_parent = GradParent;
		}
		else//要旋转的节点是子树，修改GradParent指针
		{
			if (GradParent->_left == parent)
			{
				GradParent->_left = SubL;
			}
			else
			{
				GradParent->_right = SubL;
			}
			SubL->_parent = GradParent;
		}
	}

	void _Single_Left(Node* parent)//左旋转
	{
		//记录要移动的节点
		Node* SubR = parent->_right;
		Node* SubRL = SubR->_left;

		//连接
		parent->_right = SubRL;
		if (SubRL != nullptr)
		{
			SubRL->_parent = parent;
		}
		SubR->_left = parent;
		Node* GradParent = parent->_parent;//记录这个节点的父节点，为了修改根节点
		parent->_parent = SubR;

		//调整根节点
		if (parent == _root)
		{
			_root = SubR;
			SubR->_parent = GradParent;
		}
		else //要旋转的节点是子树，修改GradParent指针
		{
			if (GradParent->_left == parent)//旋转的是左子树，连接到左边
			{
				GradParent->_left = SubR;
			}
			else
			{
				GradParent->_right = SubR;//反之
			}
			SubR->_parent = GradParent;
		}
	}
};
