#include<iostream>

class HeapOnly//�����ֻ���ڶ��ϴ���
{
public:
	static HeapOnly* CreatClass()//��̬��Ա�������Բ���Ҫ���������ĳ�Ա����
	{
		return new HeapOnly;
	}

	HeapOnly(const HeapOnly&) = delete;//C++11��������������캯������ʹ��
private:
	HeapOnly()
	{
		std::cout << "���캯��" << std::endl;
	}

	//HeapOnly(const HeapOnly&);//��ֹͨ���������캯������ջ�ϵĶ���
};

void TestHeapOnly()
{
	HeapOnly* hp = HeapOnly::CreatClass();
}

//����һ��
class StackOnly//ֻ����ջ�ϴ����������
{
public:
	static StackOnly CreatClass()
	{
		return StackOnly();//���ÿ������캯��ʵ�ַ��ء�
	}
private:
	StackOnly() {}
};

//������������new
class StackOnly_N
{
public:
	StackOnly_N() {}
private:
	void* operator new(size_t);
	//���ϴ������������������new�ؼ��֣���������е�new������Ϊ��˽�еģ��޷�ʹ��
	void operator delete(void*);
};

void TestStackOnly()
{
    StackOnly s=StackOnly::CreatClass();
	StackOnly_N s1;
	//StackOnly_N s2 = new StackOnly_N;
}

//class Singleton//����ģʽ��
//{
//public:
//
//	//����ģʽ
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
//	//��֤ȫ��ֻ��Ψһʵ���������븳ֵ�������
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	//����ģʽ
//	static Singleton* _Sing;//�����ʼ��
//};
//
//Singleton* Singleton::_Sing = new Singleton;

#include<mutex>

class Singleton//����ģʽ��
{
public:

	//����ģʽ
	static Singleton* GetClass()
	{
		//������һ����Ҫ������������ͬʱ������˫��ⷽʽ����
		if (_Sing == nullptr)
		{
			_mux.lock();
			//���е���������Ѿ�������
			if (_Sing == nullptr)
			{
				_Sing = new Singleton;//���߳�ǰû�г�ʼ���ã�д�����̲߳���ȫ����Ҫ����
			}
			_mux.unlock();
		}
		return _Sing;
	}

	static void DeleatClass()//���Ҫ����������
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
		//����������ʱҪ�������ݵȵ�
	}

private:
	Singleton(int  num = 0) :_Num(num)
	{}

	//���������ڲ���
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

	//��֤ȫ��ֻ��Ψһʵ���������븳ֵ�������
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* _Sing;//�����ʼ��

	static std::mutex _mux;

	static Garbage _gc;//������������Garbage��������
};

//����ģʽ
Singleton* Singleton::_Sing = nullptr;
std::mutex Singleton::_mux;
Singleton::Garbage Singleton::_gc;

int main()
{
	std::cout << Singleton::GetClass() << std::endl;
	std::cout << Singleton::GetClass() << std::endl;//��̬��������ַ��ͬ
	Singleton::GetClass()->Print();
	return 0;
}
