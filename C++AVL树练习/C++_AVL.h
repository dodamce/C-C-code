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

	int _bf;//ƽ������
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

	//[]���������
	Val& operator[](const Key& key)
	{
		pair<Node*, bool>ret = Insert(make_pair(key, Val()));//���ò��뺯���ķ���ֵ
		return ret.first->_KV.second;
	}

	pair<Node*,bool> Insert(const pair<Key, Val>& kv)//��AVL���в���ڵ�,����ɹ��������λ�õ�ָ���true��ʧ�ܷ������λ�õ�ָ���false
	{
		//���ڵ�Ϊ��
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return make_pair(_root, true);
		}
		//��ͨƽ��������Ĳ���(�������ֵ����)
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
			else//�ҵ��ظ���ֵ�˳�ѭ��
			{
				return make_pair(cur, false);
			}
		}
		//cur==nullptr
		cur = new Node(kv);
		Node* NewCur = cur;//�����²���Ľڵ�,������
		if (parent->_KV.first > kv.first)
		{
			cur->_Parent = parent;//������һ���ڵ�
			parent->_Left = cur;
		}
		else
		{
			cur->_Parent = parent;
			parent->_Right = cur;
		}
		/*------------------------------------------------ */
			//����ƽ�����ӣ���-��
		while (parent != nullptr)
		{
			//�жϲ���λ��
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
				break;//˵���������Ȼ����AVL��������Ҫ�����ˣ����������
			}
			else if (parent->_bf == 1 || parent->_bf == -1)//�߶ȸı䣬�������ϵ���
			{
				cur = parent;
				parent = parent->_Parent;//�������ϵ���
			}
			else if (parent->_bf == 2 || parent->_bf == -2)//������AVL����������Ҫ�������ṹ
			{
				//��ת����Ӧ���ֲ�ͬ����ת�����ڵ��ƽ������
				if (parent->_bf == -2)
				{
					if (cur->_bf == -1)//�ҵ���
					{
						_Single_Right(parent);
					}
					else if (cur->_bf == 1)//����˫��
					{
						_Single_LeftRight(parent);
					}
				}
				else//parent->_bf==2
				{
					if (cur->_bf == 1)//����
					{
						_Single_Left(parent);
					}
					else if (cur->_bf == -1)//����˫��
					{
						_Single_RightLeft(parent);
					}
				}
				break;
			}
			else//��������
			{
				assert(false);
			}
		}
		return make_pair(NewCur, true);
	}

	Node* Find(const Key& key)//ͨ����ֵ�����Ҷ�Ӧ��ֵ�ڵ㣬�ɹ����ض�Ӧ�ڵ��ָ�룬ʧ�ܷ��ؿ�
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

	void PrintTree()//�����ӡAVL��
	{
		_PrintTree(_root);
	}

	bool IsAVLTree()//����Ƿ���AVL��
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
		if (RightHeight - LeftHeight != _root->_bf)//��������
		{
			cout << "ƽ�����Ӵ���" << endl;
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
	void _Single_Right(Node* parent)//�ҵ�������ͼ�Ѷ�Ӧ��ϵ��������
	{
		//��¼Ҫ�ƶ��Ľڵ�
		Node* SubL = parent->_Left;
		Node* SubLR = SubL->_Right;

		//����
		parent->_Left = SubLR;
		if (SubL->_Right != nullptr)//�޸ĸ�ָ��
		{
			SubLR->_Parent = parent;
		}
		//����
		SubL->_Right = parent;
		Node* GradParent = parent->_Parent;//��¼����ڵ�ĸ��ڵ㣬Ϊ���޸ĸ��ڵ�
		parent->_Parent = SubL;//�޸ĸ�ָ��
		//�޸�ƽ������Ϊ0
		parent->_bf = 0; SubL->_bf = 0;
		//�������ڵ�
		if (parent == _root)//Ҫ��ת�Ľڵ�Ϊ���ڵ�
		{
			_root = SubL;
			SubL->_Parent = GradParent;
		}
		else//Ҫ��ת�Ľڵ����������޸�GradParentָ��
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

	void _Single_Left(Node* parent)//����ת
	{
		//��¼Ҫ�ƶ��Ľڵ�
		Node* SubR = parent->_Right;
		Node* SubRL = SubR->_Left;

		//����
		parent->_Right = SubRL;
		if (SubRL != nullptr)
		{
			SubRL->_Parent = parent;
		}
		SubR->_Left = parent;
		Node* GradParent = parent->_Parent;//��¼����ڵ�ĸ��ڵ㣬Ϊ���޸ĸ��ڵ�
		parent->_Parent = SubR;

		//�޸�ƽ������
		parent->_bf = 0; SubR->_bf = 0;
		//�������ڵ�
		if (parent == _root)
		{
			_root = SubR;
			SubR->_Parent = GradParent;
		}
		else //Ҫ��ת�Ľڵ����������޸�GradParentָ��
		{
			if (GradParent->_Left == parent)//��ת���������������ӵ����
			{
				GradParent->_Left = SubR;
			}
			else
			{
				GradParent->_Right = SubR;//��֮
			}
			SubR->_Parent = GradParent;
		}
	}

	void _Single_LeftRight(Node* parent)//����˫��
	{
		//��¼�ڵ��λ��
		Node* SubL = parent->_Left;
		Node* SubLR = SubL->_Right;
		//��������������
		_Single_Left(parent->_Left);
		_Single_Right(parent);
		//����SubRL�ж���ʲô����,�޸�ƽ������
		if (SubLR->_bf == 1)//���뵽��������
		{
			SubLR->_bf = 0;
			SubL->_bf = -1;
			parent->_bf = 0;
		}
		else if (SubLR->_bf == -1)//���뵽��������
		{
			parent->_bf = 1;
			SubL->_bf = 0;
			SubLR->_bf = 0;
		}
		else if (SubLR->_bf == 0)//��������������ֻ�������ڵ�,�����ڵ��ƽ�����Ӷ�Ϊ0��
		{
			parent->_bf = 0;
			SubL->_bf = 0;
			SubLR->_bf = 0;
		}
		else//��������
		{
			assert(false);
		}
	}

	void _Single_RightLeft(Node* parent)//����˫��
	{
		//��¼�ڵ��λ��
		Node* SubR = parent->_Right;
		Node* SubRL = SubR->_Left;
		//��������������
		_Single_Right(parent->_Right);
		_Single_Left(parent);
		//����SubRL�ж���ʲô����,�޸�ƽ������
		if (SubRL->_bf == 1)//���뵽��������
		{
			SubRL->_bf = 0;
			SubR->_bf = 0;
			parent->_bf = -1;
		}
		else if (SubRL->_bf == -1)//���뵽��������
		{
			parent->_bf = 0;
			SubRL->_bf = 0;
			SubR->_bf = 1;
		}
		else if (SubRL->_bf == 0)//��������������ֻ�������ڵ�,�����ڵ��ƽ�����Ӷ�Ϊ0��
		{
			parent->_bf = 0;
			SubR->_bf = 0;
			SubRL->_bf = 0;
		}
		else//��������
		{
			assert(false);
		}
	}
};



