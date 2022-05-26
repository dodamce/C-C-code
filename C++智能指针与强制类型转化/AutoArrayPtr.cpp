#include<iostream>
#include<memory>

//1.RAII(构造函数传指针，析构函数释放指针)
//2.重载* ->像指针一样
//3.智能指针拷贝问题
//针对拷贝问题有如下类别的指针
//auto_ptr---->拷贝时管理权限转移，保证一个资源只有一个对象管理，拷贝后原对象悬空（不推荐使用）
//
//C++11   unqiue_ptr (scopted_ptr) 无法拷贝

//C++11   shared_ptr (shared_ptr) 允许拷贝，使用引用计数技术，允许多个智能指针管理一个对象
//但是特殊情况下会导致循环引用

//C++11   weak_ptr   (weak_ptr)  解决shared_ptr循环引用的问题

//struct ListNode{
//	ListNode*next=nullptr;
//	ListNode*prev=nullptr;
//	int val=0;
//	~ListNode(){
//		std::cout << "析构函数调用成功" << std::endl;
//	}
//};

//weak_ptr的模拟实现
namespace My{
	template<class T>
	class weak_ptr{
	public:
		weak_ptr() :ptr(nullptr){}
		weak_ptr(const std::shared_ptr<T>&sp){
			ptr = sp.get();
		}

		weak_ptr<T>&operator=(const std::shared_ptr<T>&dev){
			ptr = dev.get();
			return *this;//不会增加share_ptr引用，防止循环引用。可以像普通指针一样使用
		}

		~weak_ptr(){
			//不参与释放，交给shared_ptr去释放

		}

		T&operator*(){//类似指针访问
			return *ptr;
		}

		T*operator->(){
			return ptr;
		}
	private:
		T*ptr;
	};
}

struct ListNode{
	My::weak_ptr<ListNode>next;
	My::weak_ptr<ListNode>prev;//不增加引用计数
	int val = 0;
	~ListNode(){
		std::cout << "析构函数调用成功" << std::endl;
	}
};

void TestCirlePtr(){
	/*ListNode*node = new ListNode;
	ListNode*node2 = new ListNode;*/
	std::shared_ptr<ListNode>node(new ListNode);
	std::shared_ptr<ListNode>node2(new ListNode);
	//使用weak_ptr避免share_ptr循环引用
	node->next = node2;
	node2->prev = node;
	//delete node; delete node2;
}

//C++11定制删除器,控制释放资源的方式，定义仿函数，使用仿函数来控制删除方法
//仿函数，lammda,包装器，函数指针。

template<class T>
struct DelArr{
	void operator()(const T*dev){
		std::cout << "释放数组" << std::endl;
		delete[]dev;
	}
};

void TestDelete(){
	std::shared_ptr<ListNode>sp(new ListNode[10], DelArr<ListNode>());//定制数组释放方式
}

//C++强制类型转换
//1.static_cast 相关类型与相近类型的转换
//2.reinterpret_cast 不相关类型转换
//3.const_cast 删除变量的const属性
//4.dynamic_cast 子类与父类指针相互转化
/*
	向下转化父类转化为子类 强制类型转化危险，dynamic_cast针对向下转化是安全的
	dynamic_cast不能转化时会返回空。注意：父类必须是多态类型才可以使用dynamic_cast

	向上转化子类转化为父类安全，切片
*/

int main(){
	//TestCirlePtr();
	//TestDelete();
	double num = 1.6;
	int a = static_cast<int>(num);//类似隐形类型转换
	double* p = reinterpret_cast<double*>(&num);//类似强制类型转换
	//const int c = 10;
	//int*ptr = const_cast<int*>(&c);
	//*ptr = 3;
	//std::cout << c << std::endl;//c被修改为3，但是打印c还是10，因为编译器优化，将const变量存到寄存器中。，这里打印的寄存器上c的值
	volatile const int c = 10;//保持内存可见性，不要把c优化到寄存器中。
	int*ptr = const_cast<int*>(&c);
	*ptr = 3;
	std::cout << c << std::endl;//c被修改为3，但是打印c还是10，因为编译器优化，将const变量存到寄存器中。，这里打印的寄存器上c的值
	std::cout << *ptr << std::endl;
	return 0;
}