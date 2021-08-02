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
		typedef const T* const_iterator;//const������
		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}

		//��������ʼ��(��Ҫ����ģ�����)
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

		vector(int n, T val)//n��ֵ��ʼ��
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

		//��������
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

		//=����
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

		//������
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

		int capcity()const//��ȡ����Ĵ�С
		{
			return _endofstorage - _start;
		}

		int size()const//��ȡ���ݸ���
		{
			return _finish - _start;
		}

		void reserve(int n)
		{
			if (n > capcity())
			{
				T* tmp = new T[n];
				int sz = size();
				if (_start)//ԭ���ݲ��ǿ�,��Ҫ��������
				{
					for (int i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];//����=�������
					}
					/*memcpy(tmp, _start,sz*sizeof(T));*///ע�����T������string��memcpy���ܽ������_str����ǳ��������deleatʱ��ɾ������
					delete[] _start;//��TΪ�������ͣ��򲻻ᷢ��ǳ�������⣬��TΪ�Զ�������ʱ���ܻ��������
				}
				_start = tmp;
				_finish = _start +sz ;
				_endofstorage = _start + n;
			}
		}

		void resize(int n,T val=T())//����ģ��Ĺ��캯��
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
				reserve(newcapcity);//����
			}
			*_finish = e;
			_finish++;
		}

		//���ݲ���
		void insert(iterator pos, const T&x)
		{
			if (pos == _finish)//û�ҵ��򲻽����κβ���
			{
				return;
			}
			if (_finish == _endofstorage)//���ݺ�Ҫ�ı�posλ�ã�������ݺ�posʧЧ����
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
			//pos += 1;//����posλ������ָ���������ͬ
		}

		iterator erase(iterator pos)//����ɾ��λ�õ���һ��λ��
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

		T&operator[](int i)//��д
		{
			assert(i < size());
			return _start[i];
		}

		T&operator[](int i)const//ֻ����д
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
	void PrintVector(const vector<T>&v)//��ӡvector
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
