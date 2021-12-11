#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<Windows.h>
using namespace std;

//三叉链,这里插入方式按照搜索二叉树key模型的插入规则来实现
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

	//拷贝构造函数
	BSTree(const BSTree<key>&dev)//前序构造
	{
		Head=_Copy(dev.Head);
	}

	//赋值运算符重载
	BSTree<key>& operator =(const BSTree<key>& dev)
	{
		BSTree<key>copy(dev);
		std::swap(Head, copy.Head);
		return *this;
	}

	//插入二叉树,不允许插入相同的值
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
				else//找到相同的值
				{
					cout << "数字重复" << endl;
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

	bool IsRightTree()//判断是否是搜索二叉树
	{
		return _IsRightTree(Head,GetMin(),GetMax());
	}

	//查找节点，返回节点指针
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
			else //找到了
			{
				return find;
			}
		}
		cout << "树中无此数字" << endl;
		return find;
	}

	//通过节点的数字删除节点
	bool DeleteNode(const key& val)
	{
		return _DeleatNode(Head, val);
	}

	//中序打印二叉树
	void PrintTree()
	{
		if (Head == nullptr)
		{
			cout<<"树为空"<<endl;
			return;
		}
		_PrintTree(Head);
		cout << endl;
	}
private:
	Node* Head;

	Node* _Copy(Node* cur)//拷贝构造函数,前序遍历
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

	//树内置查找
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
		cout << "找不到节点" << endl;
		return nullptr;
	}

	const key GetMin()//获得树最小的数字
	{
		if (Head == nullptr)
		{
			cout << "树为空，不存在最小值" << endl;
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

	const key GetMax()//获得树最大的数字
	{
		if (Head == nullptr)
		{
			cout << "树为空，不存在最小值" << endl;
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

	//查每个节点能取的最大最小值是否满足
	bool _IsRightTree(Node* Head, const key& min, const key& max)
	{
		if (Head == nullptr || Head->val == 0)
		{
			return true;////空节点也是二叉搜索树
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
			cout << "找不到数字，删除失败" << endl;
			return false;
		}
		//①要删除结点的左孩子为空或者右孩子为空
		if (cur->left == nullptr)//左孩子为空
		{
			//如果要删除的结点是根结点并且左孩子为空，替换根节点为右树根节点
			if (cur->parent == nullptr)
			{
				if (cur->right == nullptr)//一个节点
				{
					BSTree<int>tmp;
					std::swap(Head, tmp.Head);
					return true;
				}
				cur->right->parent = Head->parent;
				Head = cur->right;
				free(cur);
			}
			//不是根节点，则直接判断调整指向
			else
			{
				if (cur->right != nullptr)
				{
					cur->right->parent = cur->parent;//修改父节点
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
			//如果要删除的结点是根结点并且右孩子为空，替换根节点为左树根节点
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
			//不是根节点，则直接判断调整指向
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
		//②要删除结点的左右孩子都不为空(替换删除法)
		else
		{
			Node* repalce = cur->right;
			//找到要替换的结点(要删除结点右树最左边的那个结点就是替换结点)
			while (repalce->left)
			{
				repalce = repalce->left;
			}
			//替换数据
			cur->val = repalce->val;
			//删除这个节点和上面的逻辑重复了，可以递归实现删除右树的这个值
			_DeleatNode(cur->right, repalce->val);
		}
		return true;
	}

	void _Deleat(Node*Head)//后序
	{
		if (Head == nullptr)
		{
			return;
		}
		_Deleat(Head->left);
		_Deleat(Head->right);
		free(Head);
	}
	void _PrintTree(Node* _head)//中序
	{
		if (_head == nullptr)
			return;
		_PrintTree(_head->left);
		cout << _head->val << " ";
		_PrintTree(_head->right);
	}
};

//单元测试
void Test1()//测试二叉搜索树的插入，删除，判断，打印接口；
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
		cout << "查找函数正确" << endl;
	}
	else
	{
		cout << "查找函数不正确" << endl;
	}
	if (T.IsRightTree())
	{
		cout << "是二叉搜索树" << endl;
	}
	else
	{
		cout << "插入错误，不是二叉搜索树" << endl;
	}
	T.DeleteNode(10);
	T.DeleteNode(3);
	T.DeleteNode(11);
}

void MoveDeleat()
{
	srand((unsigned int)time(0));
	BSTree<int>Tree;
	int Max = rand() % 10 + 10;//10到19大小的数组
	vector<int>tmp;
	cout << "开始插入数据" << endl;
	for (int i = 0; i < Max; i++)
	{
		int Num = rand() % 10 + 10;
		if (Tree.Insert(Num))
		{
			Tree.PrintTree();
			if (Tree.IsRightTree())
			{
				cout << "插入正确，是二叉搜索树" << endl;
			}
			Sleep(500);
			tmp.push_back(Num);
		}
	}
	Sleep(1000);
	cout << "删除开始" << endl << endl;;
	Sleep(500);
	for (int i = 0; i < tmp.size(); i++)
	{
		Tree.PrintTree();
		Tree.DeleteNode(tmp[i]);
		Sleep(500);
	}
	cout << "删除成功" << endl;
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
			cout << "退出成功" << endl;
			break;
		}
		cout << "1.插入 2.删除 3.打印 4.查找 5.判断是否是二叉搜索树 6.退出 7.动态演示删除过程" << endl;
		cin >> input;
		switch (input)
		{
		case 1:
			system("cls");
			cout << "输入要插入的值" << endl;
			cin >> Num;
			Tree.Insert(Num);
			system("cls");
			break;
		case 2 :
			system("cls");
			Tree.PrintTree();
			cout << "要删除的值" << endl;
			cin >> Num;
			Tree.DeleteNode(Num);
			break;
		case 3:
			system("cls");
			cout << "树的中序遍历如下" << endl;
			Tree.PrintTree();
			break;
		case 4:
			cout << "要查找的值" << endl;
			cin >> Num;
			if (Tree.Find(Num))
			{
				cout << "找到了" << endl;
			}
			break;
		case 5:
			if (Tree.IsRightTree())
			{
				cout << "是二叉搜索树" << endl;
			}
			else
			{
				cout << "树结构错误" << endl;
			}
			break;
		case 6:
			falg = 1;
			break;
		case 7:
			cout << "随机数组动态删除如下" << endl;
			MoveDeleat();
			break;
		default:
			break;
		}
	}
	return 0;
}