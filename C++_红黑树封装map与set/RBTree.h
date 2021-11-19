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
		:_left(nullptr), _right(nullptr), _parent(nullptr), _kv(val), col(BLACK)//Ĭ�Ͻڵ���ɫ
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
		_Destory(_root);//�������
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
			cout << "���ڵ�Ϊ��" << endl;
			return false;
		}
		//�ȼ�¼����ڵ�ڵ�����
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
		int Num = 0;//��¼��ʱ�ڽڵ�ĸ���
		return _CheckRBTree(_root, NumBack, Num);//�ݹ麯��
	}

	Node* Find(const Key& key)//ͨ����ֵ����,���ؽڵ�ָ��
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

	//��ӡ�����
	void PrintInord()
	{
		return _PrintInord(_root);
	}

	pair<Node*, bool>Insert(const pair<Key, Value>val)//������Ĳ���
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			_root->col = BLACK;
			return make_pair(_root, true);
		}
		//��������������
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
			else//��ֵ�ظ�,����ʧ��
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
		Node* End = cur;//��¼����λ�õĽڵ�
		//����·��
		while (parent != nullptr && parent->col == RED)
		{
			Node* GradParent = parent->_parent;
			if (parent == GradParent->_left)//�ؼ���Uncle�ڵ����ɫ
			{
				Node* Uncle = GradParent->_right;
				//���1��Uncle������Ϊ��
				if (Uncle && Uncle->col == RED)
				{
					parent->col = Uncle->col = BLACK;
					GradParent->col = RED;
					cur = GradParent;
					parent = cur->_parent;
				}
				else//Uncle�����ڻ�Uncle����Ϊ��ɫ
				{
					if (cur == parent->_left)//�Ҹߣ���������
					{
						_Single_Right(GradParent);
						GradParent->col = RED;
						parent->col = BLACK;
					}
					else//������״������˫��
					{
						_Single_Left(parent);
						_Single_Right(GradParent);
						cur->col = BLACK;
						parent->col = GradParent->col = RED;
					}
					break;//��ת���ɫ�ڵ�������䣬ֱ������ѭ��
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
					if (cur == parent->_right)//��ߣ�����
					{
						_Single_Left(GradParent);
						GradParent->col = RED;
						parent->col = BLACK;
					}
					else//����,����˫��
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
		_root->col = BLACK;//��������ɫ��Ϊ��ɫ����ֹ����Ĺ��̽����ڵ��Ϊ��ɫ
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
			//�������·�Ϻڽڵ������NumBack
			if (NumBack != Num)
			{
				cout << "��ɫ�ڵ��������ͬ" << endl;
				return false;
			}
			else
			{
				return true;
			}
		}
		//ǰ�����
		if (root->col == RED && root->_parent->col == RED)
		{
			cout << "��ɫ�ڵ�����" << endl;
			return false;
		}
		else if (root->col == BLACK)
		{
			Num++;
		}
		return _CheckRBTree(root->_left, NumBack, Num) && _CheckRBTree(root->_right, NumBack, Num);
	}

	void _Destory(Node* root)//�������
	{
		if (root == nullptr)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
	void _Single_Right(Node* parent)//�ҵ�������ͼ�Ѷ�Ӧ��ϵ��������
	{
		//��¼Ҫ�ƶ��Ľڵ�
		Node* SubL = parent->_left;
		Node* SubLR = SubL->_right;

		//����
		parent->_left = SubLR;
		if (SubL->_right != nullptr)//�޸ĸ�ָ��
		{
			SubLR->_parent = parent;
		}
		//����
		SubL->_right = parent;
		Node* GradParent = parent->_parent;//��¼����ڵ�ĸ��ڵ㣬Ϊ���޸ĸ��ڵ�
		parent->_parent = SubL;//�޸ĸ�ָ��
		//�������ڵ�
		if (parent == _root)//Ҫ��ת�Ľڵ�Ϊ���ڵ�
		{
			_root = SubL;
			SubL->_parent = GradParent;
		}
		else//Ҫ��ת�Ľڵ����������޸�GradParentָ��
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

	void _Single_Left(Node* parent)//����ת
	{
		//��¼Ҫ�ƶ��Ľڵ�
		Node* SubR = parent->_right;
		Node* SubRL = SubR->_left;

		//����
		parent->_right = SubRL;
		if (SubRL != nullptr)
		{
			SubRL->_parent = parent;
		}
		SubR->_left = parent;
		Node* GradParent = parent->_parent;//��¼����ڵ�ĸ��ڵ㣬Ϊ���޸ĸ��ڵ�
		parent->_parent = SubR;

		//�������ڵ�
		if (parent == _root)
		{
			_root = SubR;
			SubR->_parent = GradParent;
		}
		else //Ҫ��ת�Ľڵ����������޸�GradParentָ��
		{
			if (GradParent->_left == parent)//��ת���������������ӵ����
			{
				GradParent->_left = SubR;
			}
			else
			{
				GradParent->_right = SubR;//��֮
			}
			SubR->_parent = GradParent;
		}
	}
};
