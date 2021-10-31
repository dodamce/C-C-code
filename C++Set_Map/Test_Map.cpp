#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>//�º���ͷ�ļ�(greater/less)
#include<queue>

using namespace std;

template<class T1,class T2>
void PrintMap(const map<T1, T2>& tmp)
{
	//autoΪ��map<T1,T2>::iterator��ģ�������
	auto ptr = tmp.begin();
	while (ptr != tmp.end())
	{
		cout << ptr->first << "->" << ptr->second << endl;//��ӡʱҪ�ֱ�ָ��key��value
		ptr++;
	}
	cout << endl;
}

void Test_Map()//����map�Ĳ���
{
	//pair<key,value>,map���ǰ���keyֵ�����
	map<int, double>m;
	//��������������룬pair������һ����������
	m.insert(pair<int, double>(1, 1.2));
	//���ú꺯��make_pair����������
	m.insert(make_pair(3, 1.2));//��make_pair��ģ�庯���������Ʋ��������ͣ�
	m.insert(pair<int, double>(2, 3.4));
	m.insert(make_pair(6, 7.2));
	PrintMap(m);
}

//map��set��keyֵ���ܱ��޸ģ�map��set����value����value�����޸�
void Test_Map2()
{
	typedef std::map<std::string, std::string> Dict;
	typedef std::pair<std::string, std::string> Dict_Pair;
	typedef std::map<std::string, std::string>::iterator Dict_Iterator;
	Dict dic;
	dic.insert(Dict_Pair("find", "����"));
	dic.insert(Dict_Pair("left", "��"));
	dic.insert(Dict_Pair("right", "��"));
	dic.insert(Dict_Pair("apple", "ƻ��"));
	Dict_Iterator ptr = dic.begin();
	PrintMap(dic);
	while (ptr != dic.end())
	{
		//�޸�second
		ptr->second.insert(0,"{");
		ptr->second += "}";
		++ptr;
	}
	PrintMap(dic);
	Dict_Iterator ptrF = dic.find("left");//���Ҽ�ֵ
	if (ptrF != dic.end())
	{
		//�ҵ��ˣ������˼
		//������ǰ�������˼�������λ��Ϊsize-1
		ptrF->second.insert(ptrF->second.size() - 1, ",ʣ��");
	}
	else
	{
		cout << "���ʧ��" << endl;
	}
	PrintMap(dic);
}

void Cout1(const vector<string>&ArrStr, map<string, int>&coutMap)
{
	//��������1
	for (const auto& str : ArrStr)
	{
		map<string, int>::iterator cout = coutMap.find(str);
		if (cout != coutMap.end())//�ҵ��ˣ���ʾ������second++
		{
			cout->second++;
		}
		else//�Ҳ�����������ˮ��
		{
			coutMap.insert(make_pair(str, 1));
		}
	}
	//��ӡ������
	//PrintMap(coutMap);//��Ĭ�ϰ���string��С�������У�
	map<string, int>::iterator ptr = coutMap.begin();
	while (ptr != coutMap.end())
	{
		cout << ptr->first << "->" << ptr->second << endl;//��ӡʱҪ�ֱ�ָ��key��value
		ptr++;
	}
	cout << endl;
}

void Cout2(const vector<string>& ArrStr, map<string, int>& coutMap)
{
	for (const auto& str : ArrStr)
	{
		//�Ƚ�����ˮ�����룬���ret��bool
		pair<map<string, int>::iterator, bool>ret = coutMap.insert(make_pair(str, 1));
		//auto ret=coutMap.insert(make_pair(str,1));
		if (ret.second == false)//ˮ�����ֹ�
		{
			ret.first->second++;//��ʾˮ��������ֵ++
		}
	}

	//��ӡmap
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
	//��ӡmap
	for (const auto& e : coutMap)
	{
		cout << e.first << "->" << e.second << endl;
	}
	cout << endl;
}

bool CompMapStrInt(map<string, int>::iterator x, map<string, int>::iterator y)
{
	return x->second > y->second;//�Ž���,�Ӵ�С
}

struct CompMapStrInt2
{
	bool operator()(map<string, int>::iterator x, map<string, int>::iterator y)
	{
		return x->second < y->second;//�Ӵ�С ��С��
	}
};

void PrintSort(map<string, int>& coutMap)
{
	vector<map<string, int>::iterator>Arr;
	//�����ݷ���Arr��
	map<string, int>::iterator ptr = coutMap.begin();
	while (ptr != coutMap.end())
	{
		Arr.push_back(ptr);
		ptr++;
	}
	//����
	/*std::sort(Arr.begin(), Arr.end(), CompMapStrInt);*/
	std::sort(Arr.begin(), Arr.end(), CompMapStrInt2());
	//��ӡmap
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
	//��ӡcoutMapInt
	for (const auto& str : coutMapInt)
	{
		cout << str.first << "->" << str.second << endl;
	}
}

void PrintSort3(map<string, int>& coutMap)
{
	multimap<int, string,greater<int>>coutMapInt;//������
	for (const auto& str : coutMap)
	{
		coutMapInt.insert(make_pair(str.second, str.first));
	}
	//��ӡcoutMapInt
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
	//��ӡpq
	int Size = pq.size();
	for (int i = 0; i < Size; i++)
	{
		MapIter tmp= pq.top();
		cout << tmp->first << "->" << tmp->second << endl;
		pq.pop();
	}
}

//mapͳ�ƴ����������մ�������
void CoutByMap()
{
	vector<string>ArrStr = { "����","����","�㽶","ƻ��","�㽶","���ܹ�","���ܹ�","���ܹ�","����","����","����","ƻ��" };
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