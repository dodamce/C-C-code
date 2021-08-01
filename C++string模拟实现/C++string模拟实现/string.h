#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>

using namespace std;

namespace My
{
	class string
	{
	public:
		//迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _src;
		}
		iterator end()
		{
			return _src + size;
		}
		string(const char*src="")
			:_src(new char[strlen(src)+1])
		{
			strcpy(_src, src);
			size = strlen(_src);
			capacity = size;
		}
		~string()
		{
			delete[]_src;
			_src = nullptr;
			size = 0;
			capacity = 0;
		}
		/*
		string(const string&s)
			:_src(new char[strlen(s._src)+1])
		{
			strcpy(_src, s._src);
		}
		string& operator=(const string&s)
		{
			if (this != &s)
			{
				delete[]_src;
				_src = new char[strlen(s._src) + 1];
				strcpy(_src, s._src);
			}
		}
		*/

		void swap(string &s)
		{
			::swap(_src, s._src);//全局swap  std::swap
			::swap(size, s.size);
			::swap(capacity, s.capacity);
		}

		string(const string&s)
			:_src(nullptr)
		{
			string tmp(s._src);
			this->swap(tmp);
		}
		string& operator=(string s)
		{
			swap(s);
			return *this;
		}
		char& operator[](int i)
		{
			assert(i<size&&i>=0);
			return _src[i];
		}
		const char& operator[](int i)const//const类的字符串只读不写
		{
			assert(i<size&&i>0);
			return _src[i];
		}
		int Size()const
		{
			return size;
		}

		const char* c_str()
		{
			return _src;
		}

		void reserve(size_t i)
		{
			if (i > capacity)
			{
				char*tmp = new char[i + 1];
				strncpy(tmp, _src,size);
				delete[]_src;
				_src = tmp;
				capacity = i;
			}
		}

		void resize(size_t i, char ch='\0')
		{
			if (i > capacity)
			{
				reserve(i);
			}
			memset(_src + size, ch, i - size);
			size = i;
			capacity = size;
			_src[i] = '\0';
		}

		void push_back(char ch)
		{
			if (size == capacity)
			{
				reserve(capacity * 2);
			}
			_src[size] = ch;
			_src[size + 1] = '\0';
			size++;
		}

		void append(const char*str)
		{
			size_t len = size + strlen(str);
			if (len > capacity)
			{
				reserve(len);
			}
			strcpy(_src + size, str);
			size = len;
			capacity = size;
		}

		string & operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string & operator+=(char*soc)
		{
			append(soc);
			return *this;
		}

		void clean()
		{
			size = 0;
		}

		bool operator<(const string& s)
		{
			int ret=strcmp(_src, s._src);
			if (ret<0)
				return true;
			else
				return false;
		}

		bool operator<=(const string& s)
		{
			return *this<s || *this == s;
		}

		bool operator>(const string& s)
		{
			return !((*this) <= s);
		}

		bool operator>=(const string& s)
		{
			return *this > s || *this == s;
		}

		bool operator==(const string& s)
		{
			int ret = strcmp(_src, s._src);
			if (ret == 0)
				return true;
			else
				return false;
		}

		bool operator!=(const string& s)
		{
			return !((*this) == s);
		}

		// 返回c在string中第一次出现的位置

		size_t find(char c, size_t pos = 0) const
		{
			char* tmp = _src;
			tmp += pos;
			int ret = 0;
			while (*tmp != '\0')
			{
				if (*tmp == c)
				{
					return ret;
				}
				ret++;
				tmp++;
			}
			return -1;
		}

		// 在pos位置上插入字符c/字符串str，并返回该字符串

		string& insert(size_t pos, char c)
		{
			assert(pos<size);
			size += 1;
			if (size > capacity)
			{
				reserve(2 * capacity);
			}
			char* next = _src + size - 1;
			char*before = _src + size - 2;
			while (before >= _src + pos)
			{
				*next = *before;
				next--;
				before--;
			}
			_src[pos] = c;
			_src[size] = '\0';
			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos<size);
			int len = strlen(str);
			int newSize = size + len;
			if (newSize > capacity)
			{
				reserve(newSize);
			}
			char* next = _src + newSize - 1;
			char*before = _src + size - 1;
			while (before >= _src + pos)
			{
				*next = *before;
				next--;
				before--;
			}
			for (int i = 0; i < strlen(str); i++)
			{
				_src[pos] = str[i];
				pos++;
			}
			size = newSize;
			_src[size] = '\0';
			return *this;
		}

		// 删除从pos位置上的元素，len个

		string& erase(size_t pos, size_t len=0)
		{
			assert(len <= capacity - pos);
			char* des = _src + pos;
			char* soc = _src + pos + len;
			while (*soc != '\0')
			{
				*des = *soc;
				des++;
				soc++;
			}
			size -= len;
			_src[size] = '\0';
			return *this;
		}


	private:
		char*_src;
		int size;
		int capacity;
	};
}

ostream& operator<<(ostream& out,My::string&s)
{
	for (auto e : s)
	{
		out << e;
	}
	return out;
}

istream& operator>>(istream& in, My::string&s)
{
	s.clean();
	char ch;
	ch = in.get();
	while (ch != ' '&&ch != '\n')
	{
		s += ch;
		ch = in.get();
	}
	return in;
}

istream& getline(istream& in, My::string&s)
{
	s.clean();
	char ch;
	ch = in.get();
	while (ch != '\n')
	{
		s += ch;
		ch = in.get();
	}
	return in;
}