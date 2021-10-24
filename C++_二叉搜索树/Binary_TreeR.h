#pragma once

#include<iostream>

using namespace std;

template<class Key>
struct BSTreeNode
{
	BSTreeNode<Key>* _left;
	BSTreeNode<Key>* _right;
	Key _key;
	BSTreeNode(Key key)
		:_left(nullptr), _right(nullptr), _key(key)
	{}
};

namespace MyR_Key
{
	template<class Key>
	class BSTree
	{
		typedef BSTreeNode<Key> Node;
	public:
		BSTree()
			:_root(nullptr)
		{}

		//节点查找
		Node* Find(const Key& key)
		{
			return _Find(_root, key);//体现了封装，简化用户使用，这里选择嵌套一层,这个最好函数被修饰为私有
		}

		//节点插入
		bool Insert(const Key& key)
		{
			return _Insert(_root, key);
		}

		//节点中序打印
		void PrintBSTree()
		{
			_PrintBSTree(_root);
			cout << endl;
		}

		bool Erase(const Key& key)
		{
			return _Erase(_root, key);
		}

	private:
		Node* _root;

		bool _Erase(Node*& root, const Key& key);//声明

		Node* _Find(Node* root, const Key& key)
		{
			if (root == nullptr)
			{
				return nullptr;
			}

			if (root->_key > key)
			{
				_Find(root->_left, key);
			}
			else if (root->_key < key)
			{
				_Find(root->_right, key);
			}
			else
			{
				return root;
			}
		}
		
		bool _Insert(Node*& root, const Key& key)
		{
			if (root == nullptr)
			{
				root = new Node(key);//root是root->left别名相当于root->left=new BSTreeNode(key)
				return true;
			}

			if (root->_key > key)
			{
				_Insert(root->_left, key);
			}
			else if (root->_key < key)
			{
				_Insert(root->_right, key);
			}
			else//数字相同，不做处理
			{
				return false;
			}
		}

		void _PrintBSTree(Node* root)//中序遍历左子树->节点->右子树
		{
			if (root == nullptr)
				return;
			if (root->_left)
				_PrintBSTree(root->_left);
			cout << root->_key << " ";
			if (root->_right)
				_PrintBSTree(root->_right);
		}
	};
}

template<class Key>
bool MyR_Key::BSTree<Key>::_Erase(Node*& root, const Key& key)
{
	if (root == nullptr)//没找到对于的位置
	{
		return false;
	}
	
	if (root->_key > key)
	{
		_Erase(root->_left, key);
	}
	else if (root->_key < key)
	{
		_Erase(root->_right, key);
	}
	else //找到要删除的位置
	{
		if (root->_left == nullptr)
		{
			Node* del = root;
			root = root->_right;//root是父节点的叶节点的引用相当于root->left=root->left->right;
			delete del;
		}
		else if (root->_right == nullptr)
		{
			Node* del = root;
			root = root->_left;
			delete del;
		}
		else //左右节点都不为空(替换法)
		{
			Node* minRight = root->_right;
			while (minRight->_left)
			{
				minRight = minRight->_left;
			}
			Key tmp = minRight->_key;//先保存右子树的最小值
			_Erase(root->_right, tmp);//递归删除右子树的最小值
			root->_key = tmp;//将右子树的最小值赋给要删除节点
		}
	}
}


