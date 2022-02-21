#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<time.h>
#include<stdio.h>

std::mutex Lock;

using namespace std;

void fun(int n)
{
	Lock.lock();
	for (size_t i = 0; i < n; i++)
	{
		cout <<this_thread::get_id()<<"��" << i << endl;
	}
	Lock.unlock();
}

void Test1()
{
	//�̳߳�
	int N = 0;
	cin >> N;
	vector<thread>Tthread;
	Tthread.resize(N);
	for (auto& th : Tthread)
	{
		th = thread(fun, 100);
		//��ӡ�߳�id
		//cout << th.get_id() << endl;
	}
	//�����߳�
	for (auto& th : Tthread)
	{
		th.join();
	}
}

void Test2()//�߳�Ч�ʲ���
{
	//�̳߳�
	int N = 0;
	cin >> N;
	vector<thread>Tthread;
	Tthread.resize(N);
	mutex mtx;
	int num = 10;
	int sum = 0;//ʵ�����
	clock_t start, end;
	start = clock();
	for (auto& th : Tthread)
	{
		th = thread([&mtx, &num, &sum]
		{
			for (int i = 0; i < num; i++)
			{
				mtx.lock();
				sum++;
				cout << this_thread::get_id() << ":" << sum << endl;
				//����
				std::this_thread::sleep_for(std::chrono::milliseconds(500));//����1��
				mtx.unlock();
			}
		});
		//��ӡ�߳�id
		//cout << th.get_id() << endl;
	}
	//�����߳�
	for (auto& th : Tthread)
	{
		th.join();
	}
	cout << "sum�ܺ�" << sum << endl;
	end = clock();
	printf("time=%f\n", (double)(end - start) / CLK_TCK);//�ú�������ֵ��Ӳ���δ�����Ҫ������룬��Ҫ����CLK_TCK
}

//C++11ԭ����++
#include<atomic>
void Test3()
{
//�̳߳�
	int N = 0;
	cin >> N;
	vector<thread>Tthread;
	Tthread.resize(N);
	mutex mtx;
	int num = 10000000;
	atomic<int> sum = 0;//ʵ��ԭ�����
	clock_t start, end;
	start = clock();
	for (auto& th : Tthread)
	{
	th = thread([&mtx, &num, &sum]
		{
			for (int i = 0; i < num; i++)
			{
				sum ++ ;//����������
			}
		});
	//��ӡ�߳�id
	//cout << th.get_id() << endl;
	}
	//�����߳�
	for (auto& th : Tthread)
	{
		th.join();
	}
	cout << "sum�ܺ�" << sum << endl;
	end = clock();
	printf("time=%f\n", (double)(end - start) / CLK_TCK);//�ú�������ֵ��Ӳ���δ�����Ҫ������룬��Ҫ����CLK_TCK
}

//lock_guard���� unique_lock
//RAII
namespace NUC
{
	template<class Lock>
	class lock_guard
	{
	public:
		lock_guard(Lock&LOCK)
			:_Lock(LOCK)
		{
			std::cout << "����" << endl;
			_Lock.lock();
		}

		~lock_guard()
		{
			std::cout << "����" << endl;
			_Lock.unlock();
		}

		lock_guard(lock_guard& copy) = delete;
	private:
		std::mutex& _Lock;
	};
}
void Test4()
{
	//Ϊ�˱�֤��Դ��һ�����ͷţ�������Ϊ�������쳣�ȴ�����ת�����޷��ͷ��������RAII
	mutex mtx;
	//NUC::lock_guard<std::mutex>Lock_Gard(mtx);//�Զ��ͷ���Դ
	//�����ֲ���Դʹ�þֲ���
	{
		NUC::lock_guard<std::mutex>Lock_Gard(mtx);//�Զ��ͷ���Դ
		FILE* p = fopen("ReadMe.txt", "r");
		if (p == nullptr)
		{
			//����Ҫ�Լ��ͷ���Դ��������������Զ�����
		}
		else
		{
			//.....
		}
	}
}

//��������
#include<condition_variable>
void test5()
{
	int size = 100;
	mutex lock;
	condition_variable cond;//��������
	bool flag = true;
	thread t1([&]() {//ȫ�����ò�׽
		//��ӡ����
		int num = 1;
		while(num<=size)
		{
			unique_lock<mutex>mtx(lock);
			cond.wait(mtx, [&flag]()->bool {return flag; });
			cout <<this_thread::get_id() <<":" << num << endl;
			num += 2;
			flag = false;
			cond.notify_one();//�����߳�
		}
	});

	thread t2([&]() {
		//��ӡż��
		int num = 2;
		while (num <= size)
		{
			unique_lock<mutex>mtx(lock);
			cond.wait(mtx, [&flag]()->bool {return !flag; });
			cout << this_thread::get_id() << ":" << num << endl;
			num += 2;
			flag = true;
			cond.notify_one();//�����߳�
		}
	});
	t1.join();t2.join();
}


int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}