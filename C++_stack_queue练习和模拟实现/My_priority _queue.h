#pragma once

#include<iostream>

#include<vector>

#include"My_functional.h"

namespace My
{
	/*
	类模板没有实例化的时候，不会生成类，就没有Conter=vector<int>,所以不加typename找不到vector中的value_type，不能用class
	*/
	//template<class T,class Conter=std::vector<T>,class Comper=Greater<typename Conter::value_type>>
	template<class T,class Conter=std::vector<T>,class Comper=Greater<T>>
	class priority_queue
	{
	public:
		//typedef typename Conter::value_type VT;
		//typedef class Conter::value_type VT;//错误，不能用class
		//小堆
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
			AdjustUp(_con.size() - 1);//堆操作，向上调整堆
		}

		//堆的删除先将堆顶的数据与最后一个数据交换，再删除

		void AdjustDown(int parent)
		{
			Comper cp;
			int child = 2 * parent + 1;
			while (child < _con.size())
			{
				//选出左右子树中的小的一个
				if (child + 1 < _con.size() && cp(_con[child + 1],_con[child]))
				{
					child++;
				}
				//小堆
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
