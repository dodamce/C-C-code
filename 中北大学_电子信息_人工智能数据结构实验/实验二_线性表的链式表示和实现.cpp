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
		//����ɾ��
		_Desety(Head);
	}
	//����ڵ�
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
	//ɾ���ڵ�
	void Erase(const int Pos)
	{
		if (Pos > Size)
		{
			cout << "����Ϊ��" << endl;
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
		else//ɾ������ͷ�ڵ�
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
			cout << "��Ϊ��" << endl;
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

	//����ȡ����Ԫ�أ����������
	Val& operator[](const int Pos)
	{
		assert(Pos >= 0 && Pos < Size);//Pos<0||Pos>=Sizeֱ�ӱ���
		Node* cur = Head;
		for (int i = 0; i < Pos; i++)
		{
			cur = cur->_next;
		}
		return cur->_val;
	}

	void Reverse()//��������
	{
		if (Size == 0)
		{
			cout << "����Ϊ��" << endl;
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

	void Sort()//��������,ð������
	{
		cout << "��С��������Ϊ" << endl;
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

int main()//���룬ɾ��,������������أ����ã�����
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
	//����
	cheat.Reverse();
	cheat.Print();
	cout << endl;
	//����
	cheat.Sort();
	cheat.Print();
	for (int i = 9;i >=0; i--)
	{
		cheat.Erase(i);
		cheat.Print();
	}
	return 0;
}