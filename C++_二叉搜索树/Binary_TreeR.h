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

		//�ڵ����
		Node* Find(const Key& key)
		{
			return _Find(_root, key);//�����˷�װ�����û�ʹ�ã�����ѡ��Ƕ��һ��,�����ú���������Ϊ˽��
		}

		//�ڵ����
		bool Insert(const Key& key)
		{
			return _Insert(_root, key);
		}

		//�ڵ������ӡ
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

		bool _Erase(Node*& root, const Key& key);//����

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
				root = new Node(key);//root��root->left�����൱��root->left=new BSTreeNode(key)
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
			else//������ͬ����������
			{
				return false;
			}
		}

		void _PrintBSTree(Node* root)//�������������->�ڵ�->������
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
	if (root == nullptr)//û�ҵ����ڵ�λ��
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
	else //�ҵ�Ҫɾ����λ��
	{
		if (root->_left == nullptr)
		{
			Node* del = root;
			root = root->_right;//root�Ǹ��ڵ��Ҷ�ڵ�������൱��root->left=root->left->right;
			delete del;
		}
		else if (root->_right == nullptr)
		{
			Node* del = root;
			root = root->_left;
			delete del;
		}
		else //���ҽڵ㶼��Ϊ��(�滻��)
		{
			Node* minRight = root->_right;
			while (minRight->_left)
			{
				minRight = minRight->_left;
			}
			Key tmp = minRight->_key;//�ȱ�������������Сֵ
			_Erase(root->_right, tmp);//�ݹ�ɾ������������Сֵ
			root->_key = tmp;//������������Сֵ����Ҫɾ���ڵ�
		}
	}
}


