#pragma once
#include<iostream>

using namespace std;

namespace My
{
	template<class T>
	struct _List_Node//����ڵ�
	{
		T _val;
		struct _List_Node*_next;
		struct _List_Node*_prev;
		_List_Node(const T&val=T())
			:_val(val), _next(nullptr), _prev(nullptr)
		{}
	};

	//��������װ
	template<class T ,class Ref , class Ptr>
	//������ģ�����ʵ����������
	struct List_iterator
	{
		typedef _List_Node<T> node;
		typedef List_iterator<T,Ref,Ptr> Self;
		node* _pnode;

		List_iterator(node*pnode)
			:_pnode(pnode)
		{}

		Ref& operator * ()//const����RefΪconst &����const���󷵻�&
		{
			return _pnode->_val;
		}

		bool operator !=(const Self&s)const //���޸�
		{
			return _pnode != s._pnode;
		}

		Self& operator ++()//ǰ��++
		{
			_pnode = _pnode->_next;
			return *this;
		}

		Self operator++(int)//����++
		{
			Self tmp = *this;//���캯��
			_pnode = _pnode->_prev;
			return tmp;
		}

		Self& operator --()//ǰ��--
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		Self operator --(int)//����--
		{
			Self tmp = *this;
			_pnode = _pnode->_prev;
			return tmp;
		}
	};

	template<class T>
	class list
	{
	public:
		typedef _List_Node<T> node;//�����б�����Ч
		typedef List_iterator<T,T&,T*> iterator;
		typedef List_iterator<T, const T&, const T*> const_iterator;
		list()//���캯��
		{
			_head = new node;//����ģ�庯����Ĭ�Ϲ��캯��
			_head->_next = _head;//˫���ͷ����
			_head->_prev = _head;
		}
		void push_back(const T&x)
		{
			node* NewNode = new node(x);
			node*tail = _head->_prev;
			tail->_next = NewNode;
			_head->_prev = NewNode;
			NewNode->_prev = tail;
			NewNode->_next = _head;
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}
	private:
			node*_head;
	};

	template <class T>
	void PrintList(list<T>&e)//���Ե�����
	{
		list<int>::iterator it = e.begin();
		while (it != e.end())
		{
			*it += 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}