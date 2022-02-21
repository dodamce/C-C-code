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
		cout <<this_thread::get_id()<<"：" << i << endl;
	}
	Lock.unlock();
}

void Test1()
{
	//线程池
	int N = 0;
	cin >> N;
	vector<thread>Tthread;
	Tthread.resize(N);
	for (auto& th : Tthread)
	{
		th = thread(fun, 100);
		//打印线程id
		//cout << th.get_id() << endl;
	}
	//回收线程
	for (auto& th : Tthread)
	{
		th.join();
	}
}

void Test2()//线程效率测试
{
	//线程池
	int N = 0;
	cin >> N;
	vector<thread>Tthread;
	Tthread.resize(N);
	mutex mtx;
	int num = 10;
	int sum = 0;//实现相加
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
				//休眠
				std::this_thread::sleep_for(std::chrono::milliseconds(500));//休眠1秒
				mtx.unlock();
			}
		});
		//打印线程id
		//cout << th.get_id() << endl;
	}
	//回收线程
	for (auto& th : Tthread)
	{
		th.join();
	}
	cout << "sum总和" << sum << endl;
	end = clock();
	printf("time=%f\n", (double)(end - start) / CLK_TCK);//该函数返回值是硬件滴答数，要换算成秒，需要除以CLK_TCK
}

//C++11原子性++
#include<atomic>
void Test3()
{
//线程池
	int N = 0;
	cin >> N;
	vector<thread>Tthread;
	Tthread.resize(N);
	mutex mtx;
	int num = 10000000;
	atomic<int> sum = 0;//实现原子相加
	clock_t start, end;
	start = clock();
	for (auto& th : Tthread)
	{
	th = thread([&mtx, &num, &sum]
		{
			for (int i = 0; i < num; i++)
			{
				sum ++ ;//类似自旋锁
			}
		});
	//打印线程id
	//cout << th.get_id() << endl;
	}
	//回收线程
	for (auto& th : Tthread)
	{
		th.join();
	}
	cout << "sum总和" << sum << endl;
	end = clock();
	printf("time=%f\n", (double)(end - start) / CLK_TCK);//该函数返回值是硬件滴答数，要换算成秒，需要除以CLK_TCK
}

//lock_guard—— unique_lock
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
			std::cout << "加锁" << endl;
			_Lock.lock();
		}

		~lock_guard()
		{
			std::cout << "解锁" << endl;
			_Lock.unlock();
		}

		lock_guard(lock_guard& copy) = delete;
	private:
		std::mutex& _Lock;
	};
}
void Test4()
{
	//为了保证资源锁一定会释放，避免因为程序抛异常等代码跳转导致无法释放锁的情况RAII
	mutex mtx;
	//NUC::lock_guard<std::mutex>Lock_Gard(mtx);//自动释放资源
	//保护局部资源使用局部域
	{
		NUC::lock_guard<std::mutex>Lock_Gard(mtx);//自动释放资源
		FILE* p = fopen("ReadMe.txt", "r");
		if (p == nullptr)
		{
			//不需要自己释放资源，出了作用域后自动销毁
		}
		else
		{
			//.....
		}
	}
}

//条件变量
#include<condition_variable>
void test5()
{
	int size = 100;
	mutex lock;
	condition_variable cond;//条件变量
	bool flag = true;
	thread t1([&]() {//全部引用捕捉
		//打印奇数
		int num = 1;
		while(num<=size)
		{
			unique_lock<mutex>mtx(lock);
			cond.wait(mtx, [&flag]()->bool {return flag; });
			cout <<this_thread::get_id() <<":" << num << endl;
			num += 2;
			flag = false;
			cond.notify_one();//唤醒线程
		}
	});

	thread t2([&]() {
		//打印偶数
		int num = 2;
		while (num <= size)
		{
			unique_lock<mutex>mtx(lock);
			cond.wait(mtx, [&flag]()->bool {return !flag; });
			cout << this_thread::get_id() << ":" << num << endl;
			num += 2;
			flag = true;
			cond.notify_one();//唤醒线程
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