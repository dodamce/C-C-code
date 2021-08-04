#pragma once
#include<iostream>

using namespace std;

namespace My
{
	template<class T>
	struct _List_Node//链表节点
	{
		T _val;
		struct _List_Node*_next;
		struct _List_Node*_prev;
		_List_Node(const T&val=T())
			:_val(val), _next(nullptr), _prev(nullptr)
		{}
	};

	//迭代器封装
	template<class T ,class Ref , class Ptr>
	//利用类模板参数实例化两个类
	struct List_iterator
	{
		typedef _List_Node<T> node;
		typedef List_iterator<T,Ref,Ptr> Self;
		node* _pnode;

		List_iterator(node*pnode)
			:_pnode(pnode)
		{}

		Ref& operator * ()//const对象Ref为const &，非const对象返回&
		{
			return _pnode->_val;
		}

		bool operator !=(const Self&s)const //不修改
		{
			return _pnode != s._pnode;
		}

		Self& operator ++()//前置++
		{
			_pnode = _pnode->_next;
			return *this;
		}

		Self operator++(int)//后置++
		{
			Self tmp = *this;//构造函数
			_pnode = _pnode->_prev;
			return tmp;
		}

		Self& operator --()//前置--
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		Self operator --(int)//后置--
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
		typedef _List_Node<T> node;//在类中别名生效
		typedef List_iterator<T,T&,T*> iterator;
		typedef List_iterator<T, const T&, const T*> const_iterator;
		list()//构造函数
		{
			_head = new node;//调用模板函数的默认构造函数
			_head->_next = _head;//双向带头链表
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
	void PrintList(list<T>&e)//测试迭代器
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