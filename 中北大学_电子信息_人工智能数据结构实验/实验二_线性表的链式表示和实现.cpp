#include<iostream>
#include<assert.h>
#include <algorithm>
#include<vector>

using namespace std;

template<class Val>
struct ListNode
{
	ListNode<Val>* _next;
	Val _val;
	ListNode(const Val& val) :_val(val),_next(nullptr) {}
	Val& operator[](const int Pos)
	{
		ListNode<Val>* cur = _next;
		for (int i = 0; i < Pos; i++)
		{
			cur = cur->_next;
		}
		return cur->_val;
	}
};

template<class Val>
class Cheat
{
	typedef ListNode<Val> Node;
public:

	Cheat() :Size(0), Head(nullptr) {}
	~Cheat()
	{
		//后序删除
		_Desety(Head);
	}
	//插入节点
	void Insert(const Val& val)
	{
		if (Head == nullptr)
		{
			Head = new Node(val);
		}
		else
		{
			Node* tmp = Head;
			while (tmp->_next != nullptr)
			{
				tmp = tmp->_next;
			}
			Node* cur = new Node(val);
			tmp->_next = cur;
		}
		Size++;
	}
	//删除节点
	void Erase(const int Pos)
	{
		if (Pos > Size)
		{
			cout << "链表为空" << endl;
			return;
		}
		Node* cur = Head;
		Node* Bef = nullptr;
		for (int i = 0; i < Pos; i++)
		{
			Bef = cur;
			cur = cur->_next;
		}
		Node* tmp = cur->_next;
		if (Bef != nullptr)
		{
			Bef->_next = tmp;
		}
		else//删除的是头节点
		{
			Head = Head->_next;
		}
		Size--;
		delete cur;
	}

	void Print()
	{
		if (Head == nullptr)
		{
			cout << "表为空" << endl;
			return;
		}
		Node* cur = Head;
		while (cur != nullptr)
		{
			cout << cur->_val << " ";
			cur = cur->_next;
		}
		cout << endl;
	}

	//链表取数据元素，运算符重载
	Val& operator[](const int Pos)
	{
		assert(Pos >= 0 && Pos < Size);//Pos<0||Pos>=Size直接报错
		Node* cur = Head;
		for (int i = 0; i < Pos; i++)
		{
			cur = cur->_next;
		}
		return cur->_val;
	}

	void Reverse()//链表逆置
	{
		if (Size == 0)
		{
			cout << "链表为空" << endl;
			return;
		}
		vector<Val>ret;
		Node* cur = Head;
		while (cur != nullptr)
		{
			ret.push_back(cur->_val);
			cur = cur->_next;
		}
		reverse(ret.begin(), ret.end());
		Node* tmp = Head;
		for (int i = 0; i < ret.size(); i++)
		{
			tmp->_val = ret[i];
			tmp = tmp->_next;
		}
	}

	void Sort()//链表排序,冒泡排序
	{
		cout << "从小到大排序为" << endl;
		vector<Val>ret;
		Node* cur = Head;
		while (cur != nullptr)
		{
			ret.push_back(cur->_val);
			cur = cur->_next;
		}
		sort(ret.begin(), ret.end());
		Node* tmp = Head;
		for (int i = 0; i < ret.size(); i++)
		{
			tmp->_val = ret[i];
			tmp = tmp->_next;
		}
	}

private:
	int Size;
	Node* Head;
	void _Desety(Node*Head)
	{
		if (Head == nullptr)
		{
			return;
		}
		_Desety(Head->_next);
		delete Head;
	}
};

int main()//插入，删除,测试运算符重载，逆置，排序
{
	Cheat<int>cheat;
	for (int i = 0; i < 10; i++)
	{
		cheat.Insert(i);
		cheat.Print();
	}
	cheat[3] = 10;
	cheat.Print();
	cout << cheat[4] << endl;;
	cheat.Print();
	//逆置
	cheat.Reverse();
	cheat.Print();
	cout << endl;
	//排序
	cheat.Sort();
	cheat.Print();
	for (int i = 9;i >=0; i--)
	{
		cheat.Erase(i);
		cheat.Print();
	}
	return 0;
}