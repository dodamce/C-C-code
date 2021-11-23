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
		:_left(nullptr), _right(nullptr), _parent(nullptr), _val(val), col(RED)//Ĭ�Ͻڵ���ɫ
	{}
};

//�����������
template<class T, class Ref, class Ptr>//ʵ��const��������ͨ����,Ref�����ݵ����ã�Ptr�����ݵ�ָ��
struct TreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef TreeIterator<T, Ref, Ptr> Iterator;
	typedef Ref refence;//���������
	typedef Ptr pointer;
	Node* _root;
	//���캯��
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
		return _root != ptr._root;//�ڵ��ָ�벻��ͬ��
	}

	bool operator ==(const Iterator& ptr)const
	{
		return _root == ptr._root;
	}

	Iterator& operator++()//��Ϊû��ռλint������ǰ��++��Iterator& operator++(int)Ϊ����++
	{
		if (_root->_right)//�Ҳ�Ϊ�գ�����������ߵĽڵ�
		{
			Node* cur = _root->_right;
			while (cur->_left!=nullptr)
			{
				cur = cur->_left;
			}
			_root = cur;
		}
		else//�ұ�Ϊ�գ����������������ߣ��Һ��Ӳ��Ǹ����ҵĽڵ�
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
		if (_root->_left)//���������ҽڵ�
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

//������������ʵ�ַ��������
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

template<class k,class T,class KeyOfValue>//�÷º�����־������map����set
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef TreeIterator<T,T&,T*> iterator;//��ͨ������
	typedef Reserve_Iterator<iterator> reserve_iterator;//���������
	typedef TreeIterator<T, const T&, const T*> const_iterator;
	iterator begin()//������
	{
		Node* tmp = _root;
		//�ҵ�һ������
		while (tmp != nullptr && tmp->_left != nullptr)
		{
			tmp = tmp->_left;
		}
		return iterator(tmp);//���������캯��
	}

	reserve_iterator rbegin()//�����ҽڵ�
	{
		Node* tmp = _root;
		//������
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

	iterator end()//β��������������ҿ�ԭ��Ϊ��
	{
		return iterator(nullptr);
	}

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

	Node* Find(const k& key)//ͨ����ֵ����,���ؽڵ�ָ��
	{
		KeyOfValue kov;//�ж�map����set
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

	pair<iterator, bool>Insert(const T& val)//������Ĳ���
	{
		KeyOfValue kov;
		if (_root == nullptr)
		{
			_root = new Node(val);
			_root->col = BLACK;
			return make_pair(iterator(_root), true);
		}
		//��������������
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
			else//��ֵ�ظ�,����ʧ��
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
		return make_pair(iterator(End), true);
	}
private:
	Node* _root;

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