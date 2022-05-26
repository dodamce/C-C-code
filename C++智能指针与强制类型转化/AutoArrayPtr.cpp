#include<iostream>
#include<memory>

//1.RAII(���캯����ָ�룬���������ͷ�ָ��)
//2.����* ->��ָ��һ��
//3.����ָ�뿽������
//��Կ�����������������ָ��
//auto_ptr---->����ʱ����Ȩ��ת�ƣ���֤һ����Դֻ��һ���������������ԭ�������գ����Ƽ�ʹ�ã�
//
//C++11   unqiue_ptr (scopted_ptr) �޷�����

//C++11   shared_ptr (shared_ptr) ��������ʹ�����ü�������������������ָ�����һ������
//������������»ᵼ��ѭ������

//C++11   weak_ptr   (weak_ptr)  ���shared_ptrѭ�����õ�����

//struct ListNode{
//	ListNode*next=nullptr;
//	ListNode*prev=nullptr;
//	int val=0;
//	~ListNode(){
//		std::cout << "�����������óɹ�" << std::endl;
//	}
//};

//weak_ptr��ģ��ʵ��
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
			return *this;//��������share_ptr���ã���ֹѭ�����á���������ָͨ��һ��ʹ��
		}

		~weak_ptr(){
			//�������ͷţ�����shared_ptrȥ�ͷ�

		}

		T&operator*(){//����ָ�����
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
	My::weak_ptr<ListNode>prev;//���������ü���
	int val = 0;
	~ListNode(){
		std::cout << "�����������óɹ�" << std::endl;
	}
};

void TestCirlePtr(){
	/*ListNode*node = new ListNode;
	ListNode*node2 = new ListNode;*/
	std::shared_ptr<ListNode>node(new ListNode);
	std::shared_ptr<ListNode>node2(new ListNode);
	//ʹ��weak_ptr����share_ptrѭ������
	node->next = node2;
	node2->prev = node;
	//delete node; delete node2;
}

//C++11����ɾ����,�����ͷ���Դ�ķ�ʽ������º�����ʹ�÷º���������ɾ������
//�º�����lammda,��װ��������ָ�롣

template<class T>
struct DelArr{
	void operator()(const T*dev){
		std::cout << "�ͷ�����" << std::endl;
		delete[]dev;
	}
};

void TestDelete(){
	std::shared_ptr<ListNode>sp(new ListNode[10], DelArr<ListNode>());//���������ͷŷ�ʽ
}

//C++ǿ������ת��
//1.static_cast ���������������͵�ת��
//2.reinterpret_cast ���������ת��
//3.const_cast ɾ��������const����
//4.dynamic_cast �����븸��ָ���໥ת��
/*
	����ת������ת��Ϊ���� ǿ������ת��Σ�գ�dynamic_cast�������ת���ǰ�ȫ��
	dynamic_cast����ת��ʱ�᷵�ؿա�ע�⣺��������Ƕ�̬���Ͳſ���ʹ��dynamic_cast

	����ת������ת��Ϊ���లȫ����Ƭ
*/

int main(){
	//TestCirlePtr();
	//TestDelete();
	double num = 1.6;
	int a = static_cast<int>(num);//������������ת��
	double* p = reinterpret_cast<double*>(&num);//����ǿ������ת��
	//const int c = 10;
	//int*ptr = const_cast<int*>(&c);
	//*ptr = 3;
	//std::cout << c << std::endl;//c���޸�Ϊ3�����Ǵ�ӡc����10����Ϊ�������Ż�����const�����浽�Ĵ����С��������ӡ�ļĴ�����c��ֵ
	volatile const int c = 10;//�����ڴ�ɼ��ԣ���Ҫ��c�Ż����Ĵ����С�
	int*ptr = const_cast<int*>(&c);
	*ptr = 3;
	std::cout << c << std::endl;//c���޸�Ϊ3�����Ǵ�ӡc����10����Ϊ�������Ż�����const�����浽�Ĵ����С��������ӡ�ļĴ�����c��ֵ
	std::cout << *ptr << std::endl;
	return 0;
}