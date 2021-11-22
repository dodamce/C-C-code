#include<iostream>
#include<string>
#include<vector>
#define MAX_LEN 10
#define MAX_SIZE 5

bool IsRightCreat = true;//抛异常

using namespace std;

//面向过程思想

//随机生成长度为随机数的字符串
void CreatStr(vector<string>&ArrStr)
{
	IsRightCreat = true;
	srand((unsigned int)time(nullptr));
	ArrStr.resize(MAX_SIZE);
	int Size[3] = { 9,26,26 };
	char Group[3] = { '0','A','a' };
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int Len = rand() % (MAX_LEN)+1;//长度1-10
		for (int j = 0; j < Len; j++)
		{
			int Class = rand() % 3;
			ArrStr[i].push_back(Group[Class] + rand() % Size[Class]);
		}
	}
}

void SortStr(vector<string>&ArrStr)//字符串排序（冒泡排序从小到大）
{
	IsRightCreat = true;
	if (ArrStr.size() == 0)
	{
		IsRightCreat = false;
		return;
	}
	for (int i = 0; i < ArrStr.size() - 1; i++)
	{
		for (int j = 0; j < ArrStr.size() - i - 1; j++)
		{
			if (ArrStr[j] > ArrStr[j + 1])
			{
				swap(ArrStr[j], ArrStr[j + 1]);
			}
		}
	}
}

void PrintStr(vector<string>& ArrStr)
{
	IsRightCreat = true;
	cout << "从小到大" << endl;
	if (ArrStr.size() == 0)
	{
		IsRightCreat = false;
		return;
	}
	for (int i = 0; i < ArrStr.size(); i++)
	{
		cout << i + 1 << ":" << ArrStr[i] << endl;
	}
}

void Test1()
{
	vector<string>ArrStr;
	CreatStr(ArrStr);
	SortStr(ArrStr);
	PrintStr(ArrStr);
}

int main()
{
	Test1();
	return 0;
}