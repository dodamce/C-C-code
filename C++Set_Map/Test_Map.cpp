#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>//仿函数头文件(greater/less)
#include<queue>

using namespace std;

template<class T1,class T2>
void PrintMap(const map<T1, T2>& tmp)
{
	//auto为（map<T1,T2>::iterator）模板迭代器
	auto ptr = tmp.begin();
	while (ptr != tmp.end())
	{
		cout << ptr->first << "->" << ptr->second << endl;//打印时要分别指明key和value
		ptr++;
	}
	cout << endl;
}

void Test_Map()//测试map的插入
{
	//pair<key,value>,map中是按照key值排序的
	map<int, double>m;
	//构造匿名对象插入，pair是数据一个数据类型
	m.insert(pair<int, double>(1, 1.2));
	//利用宏函数make_pair来插入数据
	m.insert(make_pair(3, 1.2));//（make_pair是模板函数，可以推测数据类型）
	m.insert(pair<int, double>(2, 3.4));
	m.insert(make_pair(6, 7.2));
	PrintMap(m);
}

//map和set的key值不能被修改，map比set多了value其中value可以修改
void Test_Map2()
{
	typedef std::map<std::string, std::string> Dict;
	typedef std::pair<std::string, std::string> Dict_Pair;
	typedef std::map<std::string, std::string>::iterator Dict_Iterator;
	Dict dic;
	dic.insert(Dict_Pair("find", "查找"));
	dic.insert(Dict_Pair("left", "左"));
	dic.insert(Dict_Pair("right", "右"));
	dic.insert(Dict_Pair("apple", "苹果"));
	Dict_Iterator ptr = dic.begin();
	PrintMap(dic);
	while (ptr != dic.end())
	{
		//修改second
		ptr->second.insert(0,"{");
		ptr->second += "}";
		++ptr;
	}
	PrintMap(dic);
	Dict_Iterator ptrF = dic.find("left");//查找键值
	if (ptrF != dic.end())
	{
		//找到了，添加意思
		//在括号前添加新意思，插入的位置为size-1
		ptrF->second.insert(ptrF->second.size() - 1, ",剩余");
	}
	else
	{
		cout << "添加失败" << endl;
	}
	PrintMap(dic);
}

void Cout1(const vector<string>&ArrStr, map<string, int>&coutMap)
{
	//计数方法1
	for (const auto& str : ArrStr)
	{
		map<string, int>::iterator cout = coutMap.find(str);
		if (cout != coutMap.end())//找到了，表示数量的second++
		{
			cout->second++;
		}
		else//找不到插入这种水果
		{
			coutMap.insert(make_pair(str, 1));
		}
	}
	//打印搜索树
	//PrintMap(coutMap);//（默认按照string从小到大排列）
	map<string, int>::iterator ptr = coutMap.begin();
	while (ptr != coutMap.end())
	{
		cout << ptr->first << "->" << ptr->second << endl;//打印时要分别指明key和value
		ptr++;
	}
	cout << endl;
}

void Cout2(const vector<string>& ArrStr, map<string, int>& coutMap)
{
	for (const auto& str : ArrStr)
	{
		//先将所有水果插入，检查ret的bool
		pair<map<string, int>::iterator, bool>ret = coutMap.insert(make_pair(str, 1));
		//auto ret=coutMap.insert(make_pair(str,1));
		if (ret.second == false)//水果出现过
		{
			ret.first->second++;//表示水果数量的值++
		}
	}

	//打印map
	for (const auto& e : coutMap)
	{
		cout << e.first << "->" << e.second << endl;
	}
}

void Cout(const vector<string>& ArrStr, map<string, int>& coutMap)
{
	for (const auto& str : ArrStr)
	{
		coutMap[str]++;
	}
	//打印map
	for (const auto& e : coutMap)
	{
		cout << e.first << "->" << e.second << endl;
	}
	cout << endl;
}

bool CompMapStrInt(map<string, int>::iterator x, map<string, int>::iterator y)
{
	return x->second > y->second;//排降序,从大到小
}

struct CompMapStrInt2
{
	bool operator()(map<string, int>::iterator x, map<string, int>::iterator y)
	{
		return x->second < y->second;//从大到小 建小堆
	}
};

void PrintSort(map<string, int>& coutMap)
{
	vector<map<string, int>::iterator>Arr;
	//将数据放入Arr中
	map<string, int>::iterator ptr = coutMap.begin();
	while (ptr != coutMap.end())
	{
		Arr.push_back(ptr);
		ptr++;
	}
	//排序
	/*std::sort(Arr.begin(), Arr.end(), CompMapStrInt);*/
	std::sort(Arr.begin(), Arr.end(), CompMapStrInt2());
	//打印map
	for (const auto& e : Arr)
	{
		cout << e->first << "->" << e->second << endl;
	}
}

void PrintSort2(map<string, int>& coutMap)
{
	multimap<int, string>coutMapInt;
	for (const auto& str : coutMap)
	{
		coutMapInt.insert(make_pair(str.second, str.first));
	}
	//打印coutMapInt
	for (const auto& str : coutMapInt)
	{
		cout << str.first << "->" << str.second << endl;
	}
}

void PrintSort3(map<string, int>& coutMap)
{
	multimap<int, string,greater<int>>coutMapInt;//排升序
	for (const auto& str : coutMap)
	{
		coutMapInt.insert(make_pair(str.second, str.first));
	}
	//打印coutMapInt
	for (const auto& str : coutMapInt)
	{
		cout << str.first << "->" << str.second << endl;
	}
}

void PrintSort4(map<string, int>& coutMap)
{
	typedef map<string, int>::iterator MapIter;
	priority_queue<MapIter, vector<MapIter>, CompMapStrInt2>pq;
	map<string, int>::iterator ptr = coutMap.begin();
	while (ptr != coutMap.end())
	{
		pq.push(ptr);
		ptr++;
	}
	//打印pq
	int Size = pq.size();
	for (int i = 0; i < Size; i++)
	{
		MapIter tmp= pq.top();
		cout << tmp->first << "->" << tmp->second << endl;
		pq.pop();
	}
}

//map统计次数，并按照次数排序
void CoutByMap()
{
	vector<string>ArrStr = { "柚子","柚子","香蕉","苹果","香蕉","哈密瓜","哈密瓜","哈密瓜","柚子","柚子","榴莲","苹果" };
	map<string, int>coutMap;
	Cout(ArrStr, coutMap);
	PrintSort4(coutMap);
}

int main()
{
	//Test_Map();
	//Test_Map2();
	CoutByMap();
	return 0;
}