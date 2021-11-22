#include<iostream>

using namespace std;

//������,������뷽ʽ��������������keyģ�͵Ĳ��������ʵ��
template<class key>
struct BSTNode
{
	BSTNode* left;
	BSTNode* right;
	BSTNode* parent;
	key val;
	BSTNode(const key& _val) :left(nullptr), right(nullptr), parent(nullptr), val(_val) {}
};

template<class key>
class BSTree
{
public:
	typedef BSTNode<key> Node;

	BSTree() :Head(nullptr) {}

	//���������,�����������ͬ��ֵ
	bool Insert(const key& _val)
	{
		if (Head == nullptr)
		{
			Head = new Node(_val);
			return true;
		}
		else
		{
			Node* tmp = Head;
			Node* Bef = nullptr;
			while (tmp != nullptr)
			{
				if (tmp->val > _val)
				{
					Bef = tmp;
					tmp = tmp->left;
				}
				else if (tmp->val < _val)
				{
					Bef = tmp;
					tmp = tmp->right;
				}
				else//�ҵ���ͬ��ֵ
				{
					cout << "�����ظ�" << endl;
					return false;
				}
			}
			Node* cur = new Node(_val);
			cur->parent = Bef;
			if (Bef->val > _val)
			{
				Bef->left = cur;
			}
			else
			{
				Bef->right = cur;
			}
			return true;
		}
	}

	//���ҽڵ㣬���ؽڵ�ָ��
	Node* Find(const key& pos)
	{
		Node* find = Head;
		while (find != nullptr)
		{
			if (find->val > pos)
			{
				find = find->left;
			}
			else if (find->val < pos)
			{
				find = find->right;
			}
			else //�ҵ���
			{
				return find;
			}
		}
		cout << "�����޴�����" << endl;
		return find;
	}

	//ɾ���ڵ�

	//�����ӡ������
	void PrintTree()
	{
		_PrintTree(Head);
		cout << endl;
	}
private:
	Node* Head;
	void _PrintTree(Node* _head)//����
	{
		if (_head == nullptr)
			return;
		_PrintTree(_head->left);
		cout << _head->val << " ";
		_PrintTree(_head->right);
	}
};

int main()
{
	BSTree<int>T;
	T.Insert(10);
	T.Insert(1);
	T.Insert(1);
	T.Insert(3);
	T.Insert(11);
	T.PrintTree();
	if (T.Find(11) != nullptr&&T.Find(10000)==nullptr)
	{
		cout << "���Һ�����ȷ" << endl;
	}
	else
	{
		cout << "���Һ�������ȷ" << endl;
	}
	return 0;
}