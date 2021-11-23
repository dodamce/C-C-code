#pragma once

#include<iostream>
using namespace std;

enum Color
{
	RED = 0, BLACK, 
};

template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _val;
	Color col;
	RBTreeNode(const T& val)
		:_left(nullptr), _right(nullptr), _parent(nullptr), _val(val), col(RED)//默认节点颜色
	{}
};

//红黑树迭代器
template<class T, class Ref, class Ptr>//实现const迭代和普通迭代,Ref是数据的引用，Ptr是数据的指针
struct TreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef TreeIterator<T, Ref, Ptr> Iterator;
	typedef Ref refence;//反向迭代器
	typedef Ptr pointer;
	Node* _root;
	//构造函数
	TreeIterator(Node*root)
		:_root(root)
	{}

	Ref operator*()
	{
		return _root->_val;
	}

	Ptr operator->()
	{
		return &(_root->_val);
	}

	bool operator !=(const Iterator&ptr)const
	{
		return _root != ptr._root;//节点的指针不相同。
	}

	bool operator ==(const Iterator& ptr)const
	{
		return _root == ptr._root;
	}

	Iterator& operator++()//因为没有占位int所以是前置++，Iterator& operator++(int)为后置++
	{
		if (_root->_right)//右不为空，找右树最左边的节点
		{
			Node* cur = _root->_right;
			while (cur->_left!=nullptr)
			{
				cur = cur->_left;
			}
			_root = cur;
		}
		else//右边为空，沿着三叉链往上走，找孩子不是父亲右的节点
		{
			Node* cur = _root;
			Node* parent = _root->_parent;
			while (parent != nullptr && cur == parent->_right)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_root = parent;
		}
		return *this;
	}

	

	Iterator& operator--()
	{
		if (_root->_left)//左树的最右节点
		{
			Node* cur = _root->_left;
			while (cur->_right != nullptr)
			{
				cur = cur->_right;
			}
			_root = cur;
		}
		else
		{
			Node* cur = _root;
			Node* parent = cur->_parent;
			while (parent != nullptr && cur == parent->_left)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_root = parent;
		}
		return *this;
	}
};

//迭代器适配器实现反向迭代器
template<class RIterator>
struct Reserve_Iterator
{
	typedef typename RIterator::refence Ref;
	typedef typename RIterator::pointer Ptr;
	typedef Reserve_Iterator<RIterator> Iterator;
	Reserve_Iterator(RIterator ptr) :_it(ptr) {}

	Ref operator*()
	{
		return *_it;
	}

	Ref operator->()
	{
		return *_it.operator->();
	}

	Iterator& operator++()
	{
		--_it;
		return *this;
	}

	Iterator& operator--()
	{
		++_it;
		return *this;
	}

	bool operator!=(const Iterator& dev)
	{
		return _it != dev._it;
	}

	bool operator==(const Iterator& dev)
	{
		return _it == dev._it;
	}

	RIterator _it;
};

template<class k,class T,class KeyOfValue>//用仿函数标志到底是map还是set
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef TreeIterator<T,T&,T*> iterator;//普通迭代器
	typedef Reserve_Iterator<iterator> reserve_iterator;//反向迭代器
	typedef TreeIterator<T, const T&, const T*> const_iterator;
	iterator begin()//迭代器
	{
		Node* tmp = _root;
		//找第一个数据
		while (tmp != nullptr && tmp->_left != nullptr)
		{
			tmp = tmp->_left;
		}
		return iterator(tmp);//迭代器构造函数
	}

	reserve_iterator rbegin()//找最右节点
	{
		Node* tmp = _root;
		//找最右
		while (tmp != nullptr && tmp->_right != nullptr)
		{
			tmp = tmp->_right;
		}
		return reserve_iterator(iterator(tmp));
	}

	reserve_iterator rend()
	{
		return reserve_iterator(iterator(nullptr));
	}

	iterator end()//尾迭代器遵守左闭右开原则，为空
	{
		return iterator(nullptr);
	}

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

	Node* Find(const k& key)//通过键值查找,返回节点指针
	{
		KeyOfValue kov;//判断map还是set
		Node* cur = _root;
		Node* ret = nullptr;
		while (cur != nullptr)
		{
			if (kov(key) > kov(cur->_val))
			{
				cur = cur->_right;
			}
			else if (kov(key) < kov(cur->_val))
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

	pair<iterator, bool>Insert(const T& val)//红黑树的插入
	{
		KeyOfValue kov;
		if (_root == nullptr)
		{
			_root = new Node(val);
			_root->col = BLACK;
			return make_pair(iterator(_root), true);
		}
		//二叉搜索树插入
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur != nullptr)
		{
			if (kov(cur->_val) < kov(val))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kov(cur->_val) > kov(val))
			{
				parent = cur;
				cur = cur->_left;
			}
			else//键值重复,插入失败
			{
				return make_pair(iterator(cur), false);
			}
		}
		cur = new Node(val);
		cur->col = RED;
		if (kov(parent->_val) > kov(val))
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
		return make_pair(iterator(End), true);
	}
private:
	Node* _root;

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