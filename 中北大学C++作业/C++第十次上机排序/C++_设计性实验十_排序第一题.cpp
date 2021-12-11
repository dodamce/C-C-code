#include<iostream>
#include<vector>
#include<string>
#include<stdio.h>
#include<algorithm>

using namespace std;


struct ShopSystemNode
{
	int key;
	string name;
	int money;
	int capcity;
	ShopSystemNode(int Key, const string& Name, int Money, int Capcity)
		:key(Key),name(Name),money(Money),capcity(Capcity)
	{}
	//����һ�����رȽϹ���Ϊ��sort�⺯������ʹ��
	bool operator<(const ShopSystemNode& dev)//��С����
	{
		return this->key < dev.key;
	}
};

class ShopSystem
{
	typedef ShopSystemNode Node;
	typedef vector<Node>::iterator iterator;
public:
	bool Insert(const Node&val)//����,������key�ظ�
	{
		//����
		if (_FindShop(val.key) != library.end())
		{
			cout << "��Ʒ����ظ�������ʧ��" << endl;
			return false;
		}
		library.push_back(val);
		return true;
	}
	bool PopShop(const int key)//ͨ����Ʒ���ɾ��
	{
		//����
		iterator pos = _FindShop(key);
		if (pos == library.end())
		{
			cout << "�޴���Ʒ��ţ�ɾ��ʧ��" << endl;
			return false;
		}
		library.erase(pos);
		return true;
	}
	void PrintShopList()
	{
		cout << "��Ʒ����ϵͳ" << endl;
		if (library.size() == 0)
		{
			cout << "��Ʒ�б�Ϊ��" << endl;
		}
		else
		{
			int size = library.size();
			for (int i = 0; i < size; i++)
			{
				printf("��Ʒ��ţ�%d\t��Ʒ���ƣ�%s\t���ۣ�%d\t���������%d\n"
				,library[i].key,library[i].name.c_str(),library[i].money,library[i].capcity);
			}
		}
	}

	const vector<Node> FindShop(const string&option)//������Ʒ�������з���ĳ����������Ʒ��Ϣ�����ҵ�����Ϣ�ŵ�������
	{
		vector<string> Option = { "����" ,"����","���" };
		vector<Node>ret;
		if (option == Option[0])//ѡ��������Ʋ���
		{
			cout << "����Ҫ���ҵ�ˮ��" << endl;
			string dev;cin >> dev;
			iterator pos = library.begin();
			while (pos != library.end())
			{
				if (pos->name == dev)
				{
					ret.push_back(*pos);
				}
				pos++;
			}
		}
		else if (option == Option[1])
		{
			cout << "����Ҫ���ҵĵ���" << endl;
			int dev = 0; cin >> dev;
			iterator pos = library.begin();
			while (pos != library.end())
			{
				if (pos->money == dev)
				{
					ret.push_back(*pos);
				}
				pos++;
			}
		}
		else
		{
			cout << "����Ҫ���ҵĿ������" << endl;
			int dev = 0; cin >> dev;
			iterator pos = library.begin();
			while (pos != library.end())
			{
				if (pos->capcity == dev)
				{
					ret.push_back(*pos);
				}
				pos++;
			}
		}
		return ret;
	}
	bool SortShop()//������Ʒ��Ž��������С����
	{
		if (library.size() < 2)
		{
			return true;
		}
		//��򵥵ķ�����C++������<algorithm>ʱ�临�Ӷ�(O(N*logN))
		/*
		std::sort(library.begin(), library.end());//��С����
		return true;
		*/
		//����һ��ð������ʱ�临�Ӷ�O(N^2)
		//BubbleSort(library);
	}
private:

	//������Ʒ��ŷ������������
	iterator _FindShop(const int Key)
	{
		iterator begin = library.begin();
		while (begin != library.end())
		{
			if (begin->key == Key)
			{
				return begin;
			}
			begin++;
		}
		return library.end();//û�ҵ�
	}
	vector<Node>library;
};

void Test1()//���Բ�����Ʒ
{
	ShopSystem shop;
	shop.PrintShopList();//���Դ�ӡ�ձ�
	ShopSystemNode tmp(123, "ƻ��", 3, 234);
	shop.Insert(tmp);
	shop.PrintShopList();
	ShopSystemNode tmp2(123, "�㽶", 3, 234);
	shop.Insert(tmp2);
	shop.PrintShopList();
}

void Test2()//����ɾ����Ʒ
{
	ShopSystem shop;
	ShopSystemNode tmp(123, "ƻ��", 3, 234);
	shop.Insert(tmp);
	ShopSystemNode tmp2(124, "�㽶", 3, 234);
	shop.Insert(tmp2);
	ShopSystemNode tmp3(125, "����", 3, 234);
	shop.Insert(tmp3);
	shop.PrintShopList();
	cout << "ɾ��" << endl;
	shop.PopShop(124);//ɾ��124��ˮ��
	shop.PrintShopList();
	shop.PopShop(12466);//ɾ�������ڵ���Ʒ
}
void Test3()//������Ʒ����
{
	ShopSystem shop;
	ShopSystemNode tmp(123, "ƻ��", 3, 600);
	shop.Insert(tmp);
	ShopSystemNode tmp2(124, "�㽶", 4, 234);
	shop.Insert(tmp2);
	ShopSystemNode tmp3(125, "����", 3, 234);
	shop.Insert(tmp3);
	shop.PrintShopList();
	cout << "����" << endl;
	vector<ShopSystemNode>ret;
	string option = "����";
	ret=shop.FindShop(option);
	for (const auto& e : ret)
	{
		//��ӡ��Ʒ
		printf("��Ʒ��ţ�%d\t��Ʒ���ƣ�%s\t���ۣ�%d\t���������%d\n"
			, e.key,e.name.c_str(),e.money,e.capcity);
	}
	option = "����";
	ret = shop.FindShop(option);
	for (const auto& e : ret)
	{
		//��ӡ��Ʒ
		printf("��Ʒ��ţ�%d\t��Ʒ���ƣ�%s\t���ۣ�%d\t���������%d\n"
			, e.key, e.name.c_str(), e.money, e.capcity);
	}
	option = "�������";
	ret = shop.FindShop(option);
	for (const auto& e : ret)
	{
		//��ӡ��Ʒ
		printf("��Ʒ��ţ�%d\t��Ʒ���ƣ�%s\t���ۣ�%d\t���������%d\n"
			, e.key, e.name.c_str(), e.money, e.capcity);
	}
}

void Test4()
{
	ShopSystem shop;
	ShopSystemNode tmp(200, "ƻ��", 3, 600);
	shop.Insert(tmp);
	ShopSystemNode tmp2(124, "�㽶", 4, 234);
	shop.Insert(tmp2);
	ShopSystemNode tmp3(300, "����", 3, 234);
	shop.Insert(tmp3);
	shop.PrintShopList();
	cout << endl;
	shop.SortShop();
	shop.PrintShopList();
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();
	return 0;
}