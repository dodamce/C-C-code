#include<iostream>
#include<string.h>
#include<vector>

namespace dodamce
{

	template<class T>
	class Vector
	{
	public:
		Vector()
			:_a(nullptr),_size(0),_capcity(0)
		{}

		~Vector()
		{
			delete[]_a;
		_a = nullptr;
		_size=_capcity=0;
		}
		void push_back(const T& x)
		{
			if (_size == _capcity)
			{
				int newcapcity = _capcity == 0 ? 4 : _capcity * 2;
				T* tmp = new T[newcapcity];
				if (_a != nullptr)
				{
					memcpy(tmp, _a, sizeof(T)*_size);
				}
				_a = tmp;
				_capcity = newcapcity;
			}
			_a[_size] = x;
			_size++;
		}
		int size();
		T& operator[](int pos);
	private:
		T* _a;
		int _size;
		int _capcity;
	};
}

template<class T>
T& dodamce:: Vector<T>::operator[](int pos)
{
	return _a[pos];
}

template<class T>
int dodamce::Vector<T>::size()
{
	return _size;
}
int main()
{
	dodamce::Vector<int>v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	for (int i = 0; i < v1.size(); i++)
	{
		std::cout << v1[i]<<" ";
	}
	return 0;
}