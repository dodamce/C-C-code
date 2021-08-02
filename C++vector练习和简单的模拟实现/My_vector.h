#include<iostream>
#include<assert.h>
#include<string>


using namespace std;

namespace My
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;//const迭代器
		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}

		//迭代器初始化(需要两个模板参数)
		template < class InputIterator>
		vector(InputIterator begin, InputIterator end)
			:_start(nullptr),
			_finish(nullptr),
			_endofstorage(nullptr)
		{
			while (begin != end)
			{
				push_back(*begin);
				++begin;
			}
		}

		vector(int n, T val)//n个值初始化
			:_start(nullptr),
			_finish(nullptr),
			_endofstorage(nullptr)
		{
			reserve(n);
			for (int i = 0; i < n; i++)
			{
				push_back(val);
			}
			
		}

		~vector()
		{
			if (_start != nullptr)
			{
				delete[]_start;
			}
			_start = _finish = _endofstorage = 0;
		}

		//拷贝函数
		vector(const vector<T>&v)
			:_start(nullptr),
			_finish(nullptr),
			_endofstorage(nullptr)
		{
			reserve(v.capcity());
			for (auto e : v)
			{
				push_back(e);
			}
			/*_start = new T[v.capcity()];
			memcpy(_start, v._start, sizeof(T)*v.size());
			_finish = _start + v.size();
			_endofstorage = _start + v.capcity();*/
		}

		//=重载
		/*vector<T>&operator=(const vector<T>&v)
		{
			if (this != &v)
			{
				delete[]_start;
				_start = new T[v.capcity()];
				memcpy(_start, v._start, sizeof(T)*v.size());
				_finish = _start + v.size();
				_endofstorage = _start + v.capcity();
			}
			return *this;
		}*/

		void swap(vector<int>&v)
		{
			::swap(_start, v._start);
			::swap(_finish, v._finish);
			::swap(_endofstorage, v._endofstorage);
		}

		vector<T>&operator=(const vector<T>&v)
		{
			vector<T>tmp(v);
			swap(tmp);
			return *this;
		}

		//迭代器
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin()const
		{
			return _start;
		}

		 const_iterator end()const
		{
			return _finish;
		}

		int capcity()const//获取对象的大小
		{
			return _endofstorage - _start;
		}

		int size()const//获取数据个数
		{
			return _finish - _start;
		}

		void reserve(int n)
		{
			if (n > capcity())
			{
				T* tmp = new T[n];
				int sz = size();
				if (_start)//原数据不是空,需要拷贝数据
				{
					for (int i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];//利用=重载深拷贝
					}
					/*memcpy(tmp, _start,sz*sizeof(T));*///注意如果T类型是string是memcpy可能将里面的_str进行浅拷贝，在deleat时会删除数据
					delete[] _start;//当T为内置类型，则不会发生浅拷贝问题，当T为自定义类型时可能会出现问题
				}
				_start = tmp;
				_finish = _start +sz ;
				_endofstorage = _start + n;
			}
		}

		void resize(int n,T val=T())//调用模板的构造函数
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n>capcity())
				{
					reserve(n);
				}
				while (_finish < _start + n)
				{
					*_finish = val;
					_finish++;
				}
			}
		}

		void push_back(const T&e)
		{
			if (_finish == _endofstorage)
			{
				int newcapcity = capcity() == 0 ? 5 : 2 * capcity();
				reserve(newcapcity);//增容
			}
			*_finish = e;
			_finish++;
		}

		//数据插入
		void insert(iterator pos, const T&x)
		{
			if (pos == _finish)//没找到则不进行任何操作
			{
				return;
			}
			if (_finish == _endofstorage)//增容后要改变pos位置，解决增容后pos失效问题
			{
				int sz = pos - _start;
				reserve(2 * capcity());
				pos = _start + sz;
			}
			iterator end = _finish;
			while (end > pos)
			{
				*end = *(end - 1);
				end--;
			}
			_finish += 1;
			*pos = x;
			//pos += 1;//更新pos位置让它指向的数据相同
		}

		iterator erase(iterator pos)//返回删除位置的下一个位置
		{
			assert(_finish - _start != 0);
			if (pos == _finish)
			{
				return NULL;
			}
			iterator tmp = pos;
			while (tmp < _finish)
			{
				*tmp = *(tmp + 1);
				tmp += 1;
			}
			_finish -= 1;
			return pos;
		}

		T&operator[](int i)//读写
		{
			assert(i < size());
			return _start[i];
		}

		T&operator[](int i)const//只读不写
		{
			assert(i < size());
			return _start[i];
		}

		void pop_back()
		{
			assert(_finish - _start != 0);
			_finish--;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};

	template<class T>
	void PrintVector(const vector<T>&v)//打印vector
	{
		vector<T>::const_iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it<<" ";
			it++;
		}
		cout << endl;
	}
}
