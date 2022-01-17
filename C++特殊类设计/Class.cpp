#include<iostream>

class HeapOnly//这个类只能在堆上创建
{
public:
	static HeapOnly* CreatClass()//静态成员函数可以不需要对象调用类的成员函数
	{
		return new HeapOnly;
	}

	HeapOnly(const HeapOnly&) = delete;//C++11代表这个拷贝构造函数不能使用
private:
	HeapOnly()
	{
		std::cout << "构造函数" << std::endl;
	}

	//HeapOnly(const HeapOnly&);//防止通过拷贝构造函数创建栈上的对象
};

void TestHeapOnly()
{
	HeapOnly* hp = HeapOnly::CreatClass();
}

//方法一：
class StackOnly//只能在栈上创建对象的类
{
public:
	static StackOnly CreatClass()
	{
		return StackOnly();//调用拷贝构造函数实现返回。
	}
private:
	StackOnly() {}
};

//方法二：屏蔽new
class StackOnly_N
{
public:
	StackOnly_N() {}
private:
	void* operator new(size_t);
	//堆上创建对象如果类重载了new关键字，会调用类中的new，但因为是私有的，无法使用
	void operator delete(void*);
};

void TestStackOnly()
{
    StackOnly s=StackOnly::CreatClass();
	StackOnly_N s1;
	//StackOnly_N s2 = new StackOnly_N;
}

//class Singleton//单例模式类
//{
//public:
//
//	//饿汉模式
//	static Singleton* GetClass()
//	{
//		return _Sing;
//	}
//
//	void Print()
//	{
//		std::cout << _Num << std::endl;
//	}
//
//private:
//	Singleton(int  num = 0) :_Num(num)
//	{}
//
//	int _Num;
//
//	//保证全局只有唯一实例，拷贝与赋值构造禁用
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	//饿汉模式
//	static Singleton* _Sing;//类外初始化
//};
//
//Singleton* Singleton::_Sing = new Singleton;

#include<mutex>

class Singleton//单例模式类
{
public:

	//懒汉模式
	static Singleton* GetClass()
	{
		//保护第一次需要加锁，其他不同时，采用双检测方式保护
		if (_Sing == nullptr)
		{
			_mux.lock();
			//运行到这里，服务已经启动了
			if (_Sing == nullptr)
			{
				_Sing = new Singleton;//多线程前没有初始化好，写操作线程不安全，需要加锁
			}
			_mux.unlock();
		}
		return _Sing;
	}

	static void DeleatClass()//如果要清理单例对象
	{
		_mux.lock();
		if (_Sing!=nullptr)
		{
			delete _Sing;
			_Sing = nullptr;
		}
		_mux.unlock();
	}

	void Print()
	{
		std::cout << _Num << std::endl;
	}

	~Singleton()
	{
		//如果程序结束时要保存数据等等
	}

private:
	Singleton(int  num = 0) :_Num(num)
	{}

	//垃圾回收内部类
	class Garbage
	{
	public:
		~Garbage()
		{
			if (_Sing != nullptr)
			{
				delete _Sing;
				_Sing = nullptr;
			}
		}
	};

	int _Num;

	//保证全局只有唯一实例，拷贝与赋值构造禁用
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* _Sing;//类外初始化

	static std::mutex _mux;

	static Garbage _gc;//程序结束后调用Garbage析构函数
};

//懒汉模式
Singleton* Singleton::_Sing = nullptr;
std::mutex Singleton::_mux;
Singleton::Garbage Singleton::_gc;

int main()
{
	std::cout << Singleton::GetClass() << std::endl;
	std::cout << Singleton::GetClass() << std::endl;//静态，两个地址相同
	Singleton::GetClass()->Print();
	return 0;
}
