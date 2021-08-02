#include<iostream>
#include<assert.h>


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

		~vector()
		{
			if (_start != nullptr)
			{
				delete[]_start;
			}
			_start = _finish = _endofstorage = 0;
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
					memcpy(tmp, _start,sz*sizeof(T));
					delete[] _start;
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
