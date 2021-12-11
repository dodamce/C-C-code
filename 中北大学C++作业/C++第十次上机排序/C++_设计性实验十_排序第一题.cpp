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
	//方法一：重载比较规则，为了sort库函数可以使用
	bool operator<(const ShopSystemNode& dev)//从小到大
	{
		return this->key < dev.key;
	}
};

class ShopSystem
{
	typedef ShopSystemNode Node;
	typedef vector<Node>::iterator iterator;
public:
	bool Insert(const Node&val)//插入,不允许key重复
	{
		//查重
		if (_FindShop(val.key) != library.end())
		{
			cout << "商品编号重复，插入失败" << endl;
			return false;
		}
		library.push_back(val);
		return true;
	}
	bool PopShop(const int key)//通过商品标号删除
	{
		//查找
		iterator pos = _FindShop(key);
		if (pos == library.end())
		{
			cout << "无此商品编号，删除失败" << endl;
			return false;
		}
		library.erase(pos);
		return true;
	}
	void PrintShopList()
	{
		cout << "商品管理系统" << endl;
		if (library.size() == 0)
		{
			cout << "商品列表为空" << endl;
		}
		else
		{
			int size = library.size();
			for (int i = 0; i < size; i++)
			{
				printf("商品编号：%d\t商品名称：%s\t单价：%d\t库存数量：%d\n"
				,library[i].key,library[i].name.c_str(),library[i].money,library[i].capcity);
			}
		}
	}

	const vector<Node> FindShop(const string&option)//查找商品表中所有符合某种条件的商品信息，将找到的信息放到数组中
	{
		vector<string> Option = { "名称" ,"单价","库存" };
		vector<Node>ret;
		if (option == Option[0])//选择的是名称查找
		{
			cout << "输入要查找的水果" << endl;
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
			cout << "输入要查找的单价" << endl;
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
			cout << "输入要查找的库存数量" << endl;
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
	bool SortShop()//按照商品标号进行排序从小到大
	{
		if (library.size() < 2)
		{
			return true;
		}
		//最简单的方法：C++库排序<algorithm>时间复杂度(O(N*logN))
		/*
		std::sort(library.begin(), library.end());//从小到大
		return true;
		*/
		//方法一：冒泡排序时间复杂度O(N^2)
		//BubbleSort(library);
	}
private:

	//查找商品编号返回数组迭代器
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
		return library.end();//没找到
	}
	vector<Node>library;
};

void Test1()//测试插入商品
{
	ShopSystem shop;
	shop.PrintShopList();//测试打印空表
	ShopSystemNode tmp(123, "苹果", 3, 234);
	shop.Insert(tmp);
	shop.PrintShopList();
	ShopSystemNode tmp2(123, "香蕉", 3, 234);
	shop.Insert(tmp2);
	shop.PrintShopList();
}

void Test2()//测试删除商品
{
	ShopSystem shop;
	ShopSystemNode tmp(123, "苹果", 3, 234);
	shop.Insert(tmp);
	ShopSystemNode tmp2(124, "香蕉", 3, 234);
	shop.Insert(tmp2);
	ShopSystemNode tmp3(125, "榴莲", 3, 234);
	shop.Insert(tmp3);
	shop.PrintShopList();
	cout << "删除" << endl;
	shop.PopShop(124);//删除124号水果
	shop.PrintShopList();
	shop.PopShop(12466);//删除不存在的商品
}
void Test3()//测试商品查找
{
	ShopSystem shop;
	ShopSystemNode tmp(123, "苹果", 3, 600);
	shop.Insert(tmp);
	ShopSystemNode tmp2(124, "香蕉", 4, 234);
	shop.Insert(tmp2);
	ShopSystemNode tmp3(125, "榴莲", 3, 234);
	shop.Insert(tmp3);
	shop.PrintShopList();
	cout << "查找" << endl;
	vector<ShopSystemNode>ret;
	string option = "名称";
	ret=shop.FindShop(option);
	for (const auto& e : ret)
	{
		//打印商品
		printf("商品编号：%d\t商品名称：%s\t单价：%d\t库存数量：%d\n"
			, e.key,e.name.c_str(),e.money,e.capcity);
	}
	option = "单价";
	ret = shop.FindShop(option);
	for (const auto& e : ret)
	{
		//打印商品
		printf("商品编号：%d\t商品名称：%s\t单价：%d\t库存数量：%d\n"
			, e.key, e.name.c_str(), e.money, e.capcity);
	}
	option = "库存数量";
	ret = shop.FindShop(option);
	for (const auto& e : ret)
	{
		//打印商品
		printf("商品编号：%d\t商品名称：%s\t单价：%d\t库存数量：%d\n"
			, e.key, e.name.c_str(), e.money, e.capcity);
	}
}

void Test4()
{
	ShopSystem shop;
	ShopSystemNode tmp(200, "苹果", 3, 600);
	shop.Insert(tmp);
	ShopSystemNode tmp2(124, "香蕉", 4, 234);
	shop.Insert(tmp2);
	ShopSystemNode tmp3(300, "榴莲", 3, 234);
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