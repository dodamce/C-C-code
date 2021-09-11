#pragma once

#include<iostream>

#include<vector>

#include"My_functional.h"

namespace My
{
	/*
	��ģ��û��ʵ������ʱ�򣬲��������࣬��û��Conter=vector<int>,���Բ���typename�Ҳ���vector�е�value_type��������class
	*/
	//template<class T,class Conter=std::vector<T>,class Comper=Greater<typename Conter::value_type>>
	template<class T,class Conter=std::vector<T>,class Comper=Greater<T>>
	class priority_queue
	{
	public:
		//typedef typename Conter::value_type VT;
		//typedef class Conter::value_type VT;//���󣬲�����class
		//С��
		void AdjustUp(int child)
		{
			Comper cp;
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (cp(_con[child] , _con[parent]))
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);
			AdjustUp(_con.size() - 1);//�Ѳ��������ϵ�����
		}

		//�ѵ�ɾ���Ƚ��Ѷ������������һ�����ݽ�������ɾ��

		void AdjustDown(int parent)
		{
			Comper cp;
			int child = 2 * parent + 1;
			while (child < _con.size())
			{
				//ѡ�����������е�С��һ��
				if (child + 1 < _con.size() && cp(_con[child + 1],_con[child]))
				{
					child++;
				}
				//С��
				if (cp(_con[child], _con[parent]))
				{
					std::swap(_con[parent], _con[child]);
					parent = child;
					child = parent + 1;
				}
				else
				{
					break;
				}
			}
		}

		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}

		T top()
		{
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

	private:
		Conter _con;
	};
}
