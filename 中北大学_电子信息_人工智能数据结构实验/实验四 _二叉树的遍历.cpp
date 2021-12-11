#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<Windows.h>
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

	~BSTree()
	{
		_Deleat(Head);
	}

	//�������캯��
	BSTree(const BSTree<key>&dev)//ǰ����
	{
		Head=_Copy(dev.Head);
	}

	//��ֵ���������
	BSTree<key>& operator =(const BSTree<key>& dev)
	{
		BSTree<key>copy(dev);
		std::swap(Head, copy.Head);
		return *this;
	}

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

	bool IsRightTree()//�ж��Ƿ�������������
	{
		return _IsRightTree(Head,GetMin(),GetMax());
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

	//ͨ���ڵ������ɾ���ڵ�
	bool DeleteNode(const key& val)
	{
		return _DeleatNode(Head, val);
	}

	//�����ӡ������
	void PrintTree()
	{
		if (Head == nullptr)
		{
			cout<<"��Ϊ��"<<endl;
			return;
		}
		_PrintTree(Head);
		cout << endl;
	}
private:
	Node* Head;

	Node* _Copy(Node* cur)//�������캯��,ǰ�����
	{
		Node* NewHead = nullptr;
		if (cur != nullptr)
		{
			NewHead = new Node(cur->val);
			NewHead->left = _Copy(cur->left);
			NewHead->right = _Copy(cur->right);
		}
		return NewHead;
	}

	//�����ò���
	Node* _Find(Node* Tree, const key& val)
	{
		if (Tree == nullptr)
		{
			return nullptr;
		}
		Node* cur = Tree;
		while (cur!=nullptr)
		{
			if (cur->val > val)
			{
				cur = cur->left;
			}
			else if (cur->val < val)
			{
				cur = cur->right;
			}
			else
			{
				return cur;
			}
		}
		cout << "�Ҳ����ڵ�" << endl;
		return nullptr;
	}

	const key GetMin()//�������С������
	{
		if (Head == nullptr)
		{
			cout << "��Ϊ�գ���������Сֵ" << endl;
			return 0;
		}
		else
		{
			Node* cur = Head;
			while (cur->left != nullptr)
			{
				cur = cur->left;
			}
			return cur->val;
		}
	}

	const key GetMax()//�������������
	{
		if (Head == nullptr)
		{
			cout << "��Ϊ�գ���������Сֵ" << endl;
			return 0;
		}
		else
		{
			Node* cur = Head;
			while (cur->right != nullptr)
			{
				cur = cur->right;
			}
			return cur->val;
		}
	}

	//��ÿ���ڵ���ȡ�������Сֵ�Ƿ�����
	bool _IsRightTree(Node* Head, const key& min, const key& max)
	{
		if (Head == nullptr || Head->val == 0)
		{
			return true;////�սڵ�Ҳ�Ƕ���������
		}
		else if (Head->val<min || Head->val>max)
		{
			return false;
		}
		return _IsRightTree(Head->left, min, Head->val - 1) && _IsRightTree(Head->right, Head->val + 1, max);
	}

	bool _DeleatNode(Node* Tree, const key& val)
	{
		Node* cur = _Find(Tree,val);
		if (cur == nullptr)
		{
			cout << "�Ҳ������֣�ɾ��ʧ��" << endl;
			return false;
		}
		//��Ҫɾ����������Ϊ�ջ����Һ���Ϊ��
		if (cur->left == nullptr)//����Ϊ��
		{
			//���Ҫɾ���Ľ���Ǹ���㲢������Ϊ�գ��滻���ڵ�Ϊ�������ڵ�
			if (cur->parent == nullptr)
			{
				if (cur->right == nullptr)//һ���ڵ�
				{
					BSTree<int>tmp;
					std::swap(Head, tmp.Head);
					return true;
				}
				cur->right->parent = Head->parent;
				Head = cur->right;
				free(cur);
			}
			//���Ǹ��ڵ㣬��ֱ���жϵ���ָ��
			else
			{
				if (cur->right != nullptr)
				{
					cur->right->parent = cur->parent;//�޸ĸ��ڵ�
				}
				if (cur == cur->parent->left)
				{
					cur->parent->left = cur->right;
					free(cur);
				}
				else
				{
					cur->parent->right = cur->right;
					free(cur);
				}
			}
		}
		else if (cur->right == nullptr)
		{
			//���Ҫɾ���Ľ���Ǹ���㲢���Һ���Ϊ�գ��滻���ڵ�Ϊ�������ڵ�
			if (cur->parent == nullptr)
			{
				if (cur->left == nullptr)
				{
					BSTree<int>tmp;
					std::swap(Head, tmp.Head);
					return true;
				}
				cur->left->parent = Head->parent;
				Head = cur->left;
				free(cur);
			}
			//���Ǹ��ڵ㣬��ֱ���жϵ���ָ��
			else
			{
				if (cur->left != nullptr)
				{
					cur->left->parent = cur->parent;
				}
				if (cur == cur->parent->left)
				{
					cur->parent->left = cur->left;
					free(cur);
				}
				else
				{
					cur->parent->right = cur->left;
					free(cur);
				}
			}
		}
		//��Ҫɾ���������Һ��Ӷ���Ϊ��(�滻ɾ����)
		else
		{
			Node* repalce = cur->right;
			//�ҵ�Ҫ�滻�Ľ��(Ҫɾ�������������ߵ��Ǹ��������滻���)
			while (repalce->left)
			{
				repalce = repalce->left;
			}
			//�滻����
			cur->val = repalce->val;
			//ɾ������ڵ��������߼��ظ��ˣ����Եݹ�ʵ��ɾ�����������ֵ
			_DeleatNode(cur->right, repalce->val);
		}
		return true;
	}

	void _Deleat(Node*Head)//����
	{
		if (Head == nullptr)
		{
			return;
		}
		_Deleat(Head->left);
		_Deleat(Head->right);
		free(Head);
	}
	void _PrintTree(Node* _head)//����
	{
		if (_head == nullptr)
			return;
		_PrintTree(_head->left);
		cout << _head->val << " ";
		_PrintTree(_head->right);
	}
};

//��Ԫ����
void Test1()//���Զ����������Ĳ��룬ɾ�����жϣ���ӡ�ӿڣ�
{
	BSTree<int>T;
	T.Insert(10);
	T.Insert(1);
	T.Insert(1);
	T.Insert(3);
	T.Insert(11);
	T.PrintTree();
	if (T.Find(11) != nullptr && T.Find(10000) == nullptr)
	{
		cout << "���Һ�����ȷ" << endl;
	}
	else
	{
		cout << "���Һ�������ȷ" << endl;
	}
	if (T.IsRightTree())
	{
		cout << "�Ƕ���������" << endl;
	}
	else
	{
		cout << "������󣬲��Ƕ���������" << endl;
	}
	T.DeleteNode(10);
	T.DeleteNode(3);
	T.DeleteNode(11);
}

void MoveDeleat()
{
	srand((unsigned int)time(0));
	BSTree<int>Tree;
	int Max = rand() % 10 + 10;//10��19��С������
	vector<int>tmp;
	cout << "��ʼ��������" << endl;
	for (int i = 0; i < Max; i++)
	{
		int Num = rand() % 10 + 10;
		if (Tree.Insert(Num))
		{
			Tree.PrintTree();
			if (Tree.IsRightTree())
			{
				cout << "������ȷ���Ƕ���������" << endl;
			}
			Sleep(500);
			tmp.push_back(Num);
		}
	}
	Sleep(1000);
	cout << "ɾ����ʼ" << endl << endl;;
	Sleep(500);
	for (int i = 0; i < tmp.size(); i++)
	{
		Tree.PrintTree();
		Tree.DeleteNode(tmp[i]);
		Sleep(500);
	}
	cout << "ɾ���ɹ�" << endl;
}

int main()
{
	BSTree<int>Tree;
	int input = 0;
	int Num = 0;
	int falg = 0;
	while (1)
	{
		if (falg == 1)
		{
			cout << "�˳��ɹ�" << endl;
			break;
		}
		cout << "1.���� 2.ɾ�� 3.��ӡ 4.���� 5.�ж��Ƿ��Ƕ��������� 6.�˳� 7.��̬��ʾɾ������" << endl;
		cin >> input;
		switch (input)
		{
		case 1:
			system("cls");
			cout << "����Ҫ�����ֵ" << endl;
			cin >> Num;
			Tree.Insert(Num);
			system("cls");
			break;
		case 2 :
			system("cls");
			Tree.PrintTree();
			cout << "Ҫɾ����ֵ" << endl;
			cin >> Num;
			Tree.DeleteNode(Num);
			break;
		case 3:
			system("cls");
			cout << "���������������" << endl;
			Tree.PrintTree();
			break;
		case 4:
			cout << "Ҫ���ҵ�ֵ" << endl;
			cin >> Num;
			if (Tree.Find(Num))
			{
				cout << "�ҵ���" << endl;
			}
			break;
		case 5:
			if (Tree.IsRightTree())
			{
				cout << "�Ƕ���������" << endl;
			}
			else
			{
				cout << "���ṹ����" << endl;
			}
			break;
		case 6:
			falg = 1;
			break;
		case 7:
			cout << "������鶯̬ɾ������" << endl;
			MoveDeleat();
			break;
		default:
			break;
		}
	}
	return 0;
}