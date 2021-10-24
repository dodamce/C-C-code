#pragma once

#include<iostream>

#include<time.h>

using namespace std;

template<class Key>
struct BSTreeNode
{
	BSTreeNode<Key>*_left;
	BSTreeNode<Key>* _right;
	Key _key;
	BSTreeNode(Key key)
		:_left(nullptr),_right(nullptr),_key(key)
	{}
};

namespace My_Key
{
	template<class Key>
	class BSTree
	{
	public:
		typedef BSTreeNode<Key> Node;
		BSTree()
			:_root(nullptr)
		{}
		//拷贝构造函数涉及深浅拷贝问题

		bool Insert(const Key& key);//向搜索二叉树中插入数据插入成功返回true失败返回false

		//中序遍历打印搜索二叉树
		void PrintBSTree()
		{
			_PrintBSTree(_root);//为了封装所以嵌套子函数，这个最好函数被修饰为私有
		}

		//查找节点，查找成功返回节点指针，失败返回空
		Node* Find(const Key& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else//找到位置
				{
					return cur;
				}
			}
			//当cur为空时说明找不到
			return nullptr;
		}
		
		//删除节点，删除成功返回true失败返回false
		bool Erase(const Key& key);
	private:
		Node* _root;
		void _PrintBSTree(Node* _root)//中序遍历左子树->节点->右子树
		{
			if (_root == nullptr)
				return;
			if(_root->_left)
				_PrintBSTree(_root->_left);
			cout << _root->_key << " ";
			if (_root->_right)
				_PrintBSTree(_root->_right);
		}
	};
}

template<class Key>
bool My_Key::BSTree<Key>::Insert(const Key& key)
{
	if (_root == nullptr)//树为空，新建立一个节点
	{
		_root = new Node(key);
		return true;
	}
	//树不为空，利用搜索二叉树的性质遍历找要插入的位置
	//插入数据大往树右边走，反之向左走
	Node* cur = _root;
	Node* parents = nullptr;//保存上要和cur链接的节点
	while (cur)
	{
		if (cur->_key < key)
		{
			parents = cur;
			cur = cur->_right;
		}
		else if (cur->_key > key)
		{
			parents = cur;
			cur = cur->_left;
		}
		else//重复数据在搜索二叉树中不能存在。
		{
			cout << endl << key << "数据重复" << endl;
			return false;
		}
	}
	cur = new Node(key);
	if (cur->_key < parents->_key)
	{
		parents->_left = cur;
	}
	else
	{
		parents->_right = cur;
	}
	return true;
}

template<class Key>
bool My_Key::BSTree<Key>::Erase(const Key& key)
{
	Node* parents = nullptr;
	Node* cur = _root;
	while (cur)
	{
		if (cur->_key > key)//向左子树找
		{
			parents = cur;
			cur = cur->_left;
		}
		if (cur->_key < key)
		{
			parents = cur;
			cur = cur->_right;
		}
		else//找到要删除的位置了，根据分析这时有三种情况
		{
			if (cur->_left == nullptr)//左节点为空，把孩子交给父节点管理
			{
				if (cur == _root)
				{
					_root = cur->_right;
				}
				else
				{
					if (cur == parents->_left)//cur是父节点的左子树
					{
						parents->_left = cur->_right;
					}
					else//cur是父节点的右子树
					{
						parents->_right = cur->_right;
					}
				}
				delete cur;
				return true;
			}
			else if (cur->_right == nullptr)//右节点为空
			{
				if (cur == _root)
				{
					_root = cur->_left;
				}
				else
				{
					if (cur == parents->_left)
					{
						parents->_left = cur->_left;
					}
					else
					{
						parents->_right = cur->_left;
					}
				}
				return true;
			}
			else//左右节点都不为空，替换法删除
			{
				Node* minRightParents = cur;
				Node* minRight = cur->_right;//找右子树最小值或左子树最大值来替换
				while (minRight->_left)//这里选择找右子树最小值
				{
					minRightParents = minRight;
					minRight = minRight->_left;
				}
				//找到了右树的最小值，开始替换
				cur->_key = minRight->_key;
				//删除替换的值，回到了上面两种情况了，要找这个要删除节点的父节点
				if (minRightParents->_left == minRight)
				{
					minRightParents->_left = minRight->_right;
				}
				else
				{
					minRightParents->_right = minRight->_right;
				}
				delete minRight;
				return true;
			}
		}
	}
	return false;
}