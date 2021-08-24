#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

typedef struct pair
{
	int key;//键值
	char name[10];//数据
}pair;

typedef struct HashTable
{
	int size;
	int capcity;//可存放数据的大小
	pair** Hash;//指向一个数组，数组存放的是pair*
}HashTable;

HashTable* CreatHash(int Cap)
{
	HashTable* NewHash = (HashTable*)malloc(sizeof(HashTable));
	NewHash->capcity = Cap;
	NewHash->size = 0;
	NewHash->Hash = (pair**)malloc(sizeof(pair*) * Cap);
	for (int i = 0; i < Cap; i++)
	{
		NewHash->Hash[i] = NULL;//初始化为空
	}
	return NewHash;
}

//找hash地址
int FindPos(HashTable* dev, int keyD)
{
	int pos = keyD % (dev->capcity);
	int FinPos = pos;
	//当发生哈希冲突时找到没有存放数据的位置，当键相同时覆盖
	if (dev->Hash[pos] != NULL && dev->Hash[pos]->key == keyD)//有数据且键相同
	{
		return pos;
	}
	do
	{
		if (dev->Hash[FinPos] == NULL)//如果是空位置
		{
			return FinPos;
		}
		FinPos = (FinPos + 1) % (dev->capcity);//看下一个位置是否为空
	} while (FinPos != pos);//当FinPos==pos时说明循环一圈都没有空位，这时候返回pos到函数外判断
	return FinPos;
}

//插入数据
void Insert(HashTable* dev, pair val)
{
	int pos = FindPos(dev, val.key);
	if (dev->Hash[pos] == NULL)//返回有空位时
	{
		//先申请内存，在用memcpy拷贝
		dev->Hash[pos] = (pair*)malloc(sizeof(pair));
		memcpy(dev->Hash[pos], &val, sizeof(pair));
		dev->size++;
	}
	else//返回没有空位时，可能是key重复，也可能是存满了
	{
		if (dev->Hash[pos]->key == val.key)//key重复,只要交换数组就行，不用memcpy
		{
			strcpy(dev->Hash[pos]->name, val.name);
		}
		else//存满了
		{
			printf("内存不足，无法插入\n");
		}
	}
}

//打印hsah
void PrintHash(HashTable* dev)
{
	for (int i = 0; i < dev->capcity; i++)
	{
		if (dev->Hash[i] == NULL)
		{
			printf("NULL \n");
		}
		else
		{
			printf("学号%d 姓名%s\n",dev->Hash[i]->key,dev->Hash[i]->name);
		}
	}
}

//测试
int main()
{
	HashTable* Class = CreatHash(5);
	pair Stu[4] = { {1,"小红"},{11,"小刚"},{3,"小明"},{4,"小丽"} };
	for (int i = 0; i < 4; i++)
	{
		Insert(Class, Stu[i]);
	}
	PrintHash(Class);
	printf("\n");
	pair Stu1 = { 21,"小华" };//正常插入
	Insert(Class, Stu1);
	PrintHash(Class);
	printf("\n");
	pair Stu2 = { 1,"丽丽" };//重复覆盖
	Insert(Class, Stu2);
	PrintHash(Class);
	printf("\n");
	pair Stu3 = { 31,"罗斯" };//验证已满
	Insert(Class, Stu3);
	PrintHash(Class);
	return 0;
}