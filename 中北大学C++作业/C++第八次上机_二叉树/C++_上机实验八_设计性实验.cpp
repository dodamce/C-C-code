//判断二叉树是否相等

#include<iostream>
#include<vector>

using namespace std;

typedef int TreeNodeDate;

struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	TreeNodeDate _val;
	TreeNode(const TreeNodeDate& val) :_val(val), left(nullptr), right(nullptr) {}
};

class Tree
{
public:
	typedef TreeNode  Node;
	Tree() :_head(nullptr) {}
	void Insert(const vector<int>& Vet)
	{
		_head=_Insert(Vet, 0, Vet.size()-1);
	}
	//判断两个二叉树是否相同
	friend bool IsSameTree(const Tree& T1, const Tree& T2);
private:	
	Node* _head;
	Node* _Insert(const vector<int>& Vet, int begin, int end)
	{
		if (begin > end)
		{
			return nullptr;
		}
		int mid = (begin + end) / 2;
		TreeNode*head = new TreeNode(Vet[mid]);//前序遍历
		head->left = _Insert(Vet, begin, mid - 1);
		head->right =_Insert(Vet, mid + 1, end);
		return head;
	}
};

typedef TreeNode Node;
bool _IsSameTree(Node* p1, Node* p2)
{
	if (p1 == nullptr && p2 == nullptr)
		return true;
	if (p1 == nullptr || p2 == nullptr)
		return false;
	return p1->_val == p2->_val && _IsSameTree(p1->left, p2->left)
		&& _IsSameTree(p1->right, p2->right);
}

bool IsSameTree(const Tree& T1, const Tree& T2)
{
	return _IsSameTree(T1._head, T2._head);
}

void Test1()//测试数组转化为二叉树是否正确
{
	vector<int>Arr = { 1,2,3,4,5,6,7 };
	Tree Tr;
	Tr.Insert(Arr);
}

int main()
{
	Test1();
	vector<int>Arr = { 1,2,3,4,5,6,7 };
	vector<int>Arr2 = { 1,2,3,4,5,7 };
	Tree t1;
	t1.Insert(Arr);
	Tree t2;
	t2.Insert(Arr2);
	if (IsSameTree(t1, t2))
	{
		cout << "Same Tree" << endl;
	}
	else
	{
		cout << "Not Same Tree" << endl;
	}
	return 0;
}