#pragma once

#include<iostream>
#include<assert.h>

using namespace std;

template<class Key,class Val>
struct AVLNode
{
	AVLNode<Key, Val>* _Left;
	AVLNode<Key, Val>* _Right;
	AVLNode<Key, Val>* _Parent;

	int _bf;//平衡因子
	pair<Key, Val> _KV;
	AVLNode(const pair<Key, Val>& kv) :_Left(nullptr), _Right(nullptr)
		, _Parent(nullptr), _bf(0), _KV(kv)
	{}
};

template<class Key, class Val>
class AVLTree
{
public:
	typedef AVLNode<Key, Val> Node;
	AVLTree() :_root(nullptr) {}

	~AVLTree()
	{
		_Destory(_root);
	}

	//[]运算符重载
	Val& operator[](const Key& key)
	{
		pair<Node*, bool>ret = Insert(make_pair(key, Val()));//利用插入函数的返回值
		return ret.first->_KV.second;
	}

	pair<Node*,bool> Insert(const pair<Key, Val>& kv)//向AVL树中插入节点,插入成功返回这个位置的指针和true，失败返回这个位置的指针和false
	{
		//根节点为空
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return make_pair(_root, true);
		}
		//普通平衡二叉树的插入(不允许键值冗余)
		Node* parent = nullptr; Node* cur = _root;
		while (cur != nullptr)
		{
			if (kv.first > cur->_KV.first)
			{
				parent = cur;
				cur = cur->_Right;
			}
			else if (kv.first < cur->_KV.first)
			{
				parent = cur;
				cur = cur->_Left;
			}
			else//找到重复键值退出循环
			{
				return make_pair(cur, false);
			}
		}
		//cur==nullptr
		cur = new Node(kv);
		Node* NewCur = cur;//保存新插入的节点,来返回
		if (parent->_KV.first > kv.first)
		{
			cur->_Parent = parent;//链接上一个节点
			parent->_Left = cur;
		}
		else
		{
			cur->_Parent = parent;
			parent->_Right = cur;
		}
		/*------------------------------------------------ */
			//更新平衡因子（右-左）
		while (parent != nullptr)
		{
			//判断插入位置
			if (parent->_Left == cur)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent->_bf == 0)
			{
				break;//说明插入后仍然满足AVL树，不需要调整了，插入结束。
			}
			else if (parent->_bf == 1 || parent->_bf == -1)//高度改变，继续向上调整
			{
				cur = parent;
				parent = parent->_Parent;//继续向上调整
			}
			else if (parent->_bf == 2 || parent->_bf == -2)//不满足AVL树特征，需要调整树结构
			{
				//旋转，对应四种不同的旋转，看节点的平衡因子
				if (parent->_bf == -2)
				{
					if (cur->_bf == -1)//右单旋
					{
						_Single_Right(parent);
					}
					else if (cur->_bf == 1)//左右双旋
					{
						_Single_LeftRight(parent);
					}
				}
				else//parent->_bf==2
				{
					if (cur->_bf == 1)//左单旋
					{
						_Single_Left(parent);
					}
					else if (cur->_bf == -1)//右左双旋
					{
						_Single_RightLeft(parent);
					}
				}
				break;
			}
			else//发生错误
			{
				assert(false);
			}
		}
		return make_pair(NewCur, true);
	}

	Node* Find(const Key& key)//通过键值来查找对应键值节点，成功返回对应节点的指针，失败返回空
	{
		Node* cur = _root;
		while (cur!=nullptr)
		{
			if (cur->_KV.first < key)
			{
				cur = cur->_Right;
			}
			else if (cur->_KV.first > key)
			{
				cur = cur->_Left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}

	void PrintTree()//中序打印AVL树
	{
		_PrintTree(_root);
	}

	bool IsAVLTree()//检查是否是AVL树
	{
		return _IsAVLTree(_root);
	}

private:
	Node* _root;

	void _Destory(Node* root)
	{
		if (root == nullptr)
			return;
		_Destory(root->_Left);
		_Destory(root->_Right);
		delete root;
	}

	bool _IsAVLTree(Node* _root)
	{
		if (_root == nullptr)
			return true;
		int LeftHeight = _Height(_root->_Left);
		int RightHeight = _Height(_root->_Right);
		if (RightHeight - LeftHeight != _root->_bf)//发生错误
		{
			cout << "平衡因子错误" << endl;
			return false;
		}
		bool tmp = abs(LeftHeight - RightHeight) < 2;
		bool tmp2 = _IsAVLTree(_root->_Left);
		bool tmp3 = _IsAVLTree(_root->_Right);
		/*return abs(LeftHeight - RightHeight) < 2
			&& _IsAVLTree(_root->_Left) && _IsAVLTree(_root->_Right);*/
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int LeftTreeHeight = _Height(root->_Left);
		int RightTreeHeight = _Height(root->_Right);
		return max(LeftTreeHeight, RightTreeHeight) + 1;
	}

	void _PrintTree(Node* root)
	{
		if (root == nullptr)
			return;
		_PrintTree(root->_Left);
		cout << root->_KV.first << "->" << root->_KV.second << endl;
		_PrintTree(root->_Right);
	}
	void _Single_Right(Node* parent)//右单旋根据图把对应关系连接起来
	{
		//记录要移动的节点
		Node* SubL = parent->_Left;
		Node* SubLR = SubL->_Right;

		//连接
		parent->_Left = SubLR;
		if (SubL->_Right != nullptr)//修改父指针
		{
			SubLR->_Parent = parent;
		}
		//连接
		SubL->_Right = parent;
		Node* GradParent = parent->_Parent;//记录这个节点的父节点，为了修改根节点
		parent->_Parent = SubL;//修改父指针
		//修改平衡因子为0
		parent->_bf = 0; SubL->_bf = 0;
		//调整根节点
		if (parent == _root)//要旋转的节点为根节点
		{
			_root = SubL;
			SubL->_Parent = GradParent;
		}
		else//要旋转的节点是子树，修改GradParent指针
		{
			if (GradParent->_Left == parent)
			{
				GradParent->_Left = SubL;
			}
			else
			{
				GradParent->_Right = SubL;
			}
			SubL->_Parent = GradParent;
		}
	}

	void _Single_Left(Node* parent)//左旋转
	{
		//记录要移动的节点
		Node* SubR = parent->_Right;
		Node* SubRL = SubR->_Left;

		//连接
		parent->_Right = SubRL;
		if (SubRL != nullptr)
		{
			SubRL->_Parent = parent;
		}
		SubR->_Left = parent;
		Node* GradParent = parent->_Parent;//记录这个节点的父节点，为了修改根节点
		parent->_Parent = SubR;

		//修改平衡因子
		parent->_bf = 0; SubR->_bf = 0;
		//调整根节点
		if (parent == _root)
		{
			_root = SubR;
			SubR->_Parent = GradParent;
		}
		else //要旋转的节点是子树，修改GradParent指针
		{
			if (GradParent->_Left == parent)//旋转的是左子树，连接到左边
			{
				GradParent->_Left = SubR;
			}
			else
			{
				GradParent->_Right = SubR;//反之
			}
			SubR->_Parent = GradParent;
		}
	}

	void _Single_LeftRight(Node* parent)//左右双旋
	{
		//记录节点的位置
		Node* SubL = parent->_Left;
		Node* SubLR = SubL->_Right;
		//先左旋，再右旋
		_Single_Left(parent->_Left);
		_Single_Right(parent);
		//根据SubRL判断是什么类型,修改平衡因子
		if (SubLR->_bf == 1)//插入到右子树上
		{
			SubLR->_bf = 0;
			SubL->_bf = -1;
			parent->_bf = 0;
		}
		else if (SubLR->_bf == -1)//插入到左子树上
		{
			parent->_bf = 1;
			SubL->_bf = 0;
			SubLR->_bf = 0;
		}
		else if (SubLR->_bf == 0)//特殊情况，插入后只有三个节点,三个节点的平衡因子都为0。
		{
			parent->_bf = 0;
			SubL->_bf = 0;
			SubLR->_bf = 0;
		}
		else//发生错误
		{
			assert(false);
		}
	}

	void _Single_RightLeft(Node* parent)//右左双旋
	{
		//记录节点的位置
		Node* SubR = parent->_Right;
		Node* SubRL = SubR->_Left;
		//先右旋，再左旋
		_Single_Right(parent->_Right);
		_Single_Left(parent);
		//根据SubRL判断是什么类型,修改平衡因子
		if (SubRL->_bf == 1)//插入到右子树上
		{
			SubRL->_bf = 0;
			SubR->_bf = 0;
			parent->_bf = -1;
		}
		else if (SubRL->_bf == -1)//插入到左子树上
		{
			parent->_bf = 0;
			SubRL->_bf = 0;
			SubR->_bf = 1;
		}
		else if (SubRL->_bf == 0)//特殊情况，插入后只有三个节点,三个节点的平衡因子都为0。
		{
			parent->_bf = 0;
			SubR->_bf = 0;
			SubRL->_bf = 0;
		}
		else//发生错误
		{
			assert(false);
		}
	}
};



