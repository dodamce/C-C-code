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
		//�������캯���漰��ǳ��������

		bool Insert(const Key& key);//�������������в������ݲ���ɹ�����trueʧ�ܷ���false

		//���������ӡ����������
		void PrintBSTree()
		{
			_PrintBSTree(_root);//Ϊ�˷�װ����Ƕ���Ӻ����������ú���������Ϊ˽��
		}

		//���ҽڵ㣬���ҳɹ����ؽڵ�ָ�룬ʧ�ܷ��ؿ�
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
				else//�ҵ�λ��
				{
					return cur;
				}
			}
			//��curΪ��ʱ˵���Ҳ���
			return nullptr;
		}
		
		//ɾ���ڵ㣬ɾ���ɹ�����trueʧ�ܷ���false
		bool Erase(const Key& key);
	private:
		Node* _root;
		void _PrintBSTree(Node* _root)//�������������->�ڵ�->������
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
	if (_root == nullptr)//��Ϊ�գ��½���һ���ڵ�
	{
		_root = new Node(key);
		return true;
	}
	//����Ϊ�գ��������������������ʱ�����Ҫ�����λ��
	//�������ݴ������ұ��ߣ���֮������
	Node* cur = _root;
	Node* parents = nullptr;//������Ҫ��cur���ӵĽڵ�
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
		else//�ظ������������������в��ܴ��ڡ�
		{
			cout << endl << key << "�����ظ�" << endl;
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
		if (cur->_key > key)//����������
		{
			parents = cur;
			cur = cur->_left;
		}
		if (cur->_key < key)
		{
			parents = cur;
			cur = cur->_right;
		}
		else//�ҵ�Ҫɾ����λ���ˣ����ݷ�����ʱ���������
		{
			if (cur->_left == nullptr)//��ڵ�Ϊ�գ��Ѻ��ӽ������ڵ����
			{
				if (cur == _root)
				{
					_root = cur->_right;
				}
				else
				{
					if (cur == parents->_left)//cur�Ǹ��ڵ��������
					{
						parents->_left = cur->_right;
					}
					else//cur�Ǹ��ڵ��������
					{
						parents->_right = cur->_right;
					}
				}
				delete cur;
				return true;
			}
			else if (cur->_right == nullptr)//�ҽڵ�Ϊ��
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
			else//���ҽڵ㶼��Ϊ�գ��滻��ɾ��
			{
				Node* minRightParents = cur;
				Node* minRight = cur->_right;//����������Сֵ�����������ֵ���滻
				while (minRight->_left)//����ѡ������������Сֵ
				{
					minRightParents = minRight;
					minRight = minRight->_left;
				}
				//�ҵ�����������Сֵ����ʼ�滻
				cur->_key = minRight->_key;
				//ɾ���滻��ֵ���ص���������������ˣ�Ҫ�����Ҫɾ���ڵ�ĸ��ڵ�
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