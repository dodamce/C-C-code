#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

typedef struct pair
{
	int key;//��ֵ
	char name[10];//����
}pair;

typedef struct HashTable
{
	int size;
	int capcity;//�ɴ�����ݵĴ�С
	pair** Hash;//ָ��һ�����飬�����ŵ���pair*
}HashTable;

HashTable* CreatHash(int Cap)
{
	HashTable* NewHash = (HashTable*)malloc(sizeof(HashTable));
	NewHash->capcity = Cap;
	NewHash->size = 0;
	NewHash->Hash = (pair**)malloc(sizeof(pair*) * Cap);
	for (int i = 0; i < Cap; i++)
	{
		NewHash->Hash[i] = NULL;//��ʼ��Ϊ��
	}
	return NewHash;
}

//��hash��ַ
int FindPos(HashTable* dev, int keyD)
{
	int pos = keyD % (dev->capcity);
	int FinPos = pos;
	//��������ϣ��ͻʱ�ҵ�û�д�����ݵ�λ�ã�������ͬʱ����
	if (dev->Hash[pos] != NULL && dev->Hash[pos]->key == keyD)//�������Ҽ���ͬ
	{
		return pos;
	}
	do
	{
		if (dev->Hash[FinPos] == NULL)//����ǿ�λ��
		{
			return FinPos;
		}
		FinPos = (FinPos + 1) % (dev->capcity);//����һ��λ���Ƿ�Ϊ��
	} while (FinPos != pos);//��FinPos==posʱ˵��ѭ��һȦ��û�п�λ����ʱ�򷵻�pos���������ж�
	return FinPos;
}

//��������
void Insert(HashTable* dev, pair val)
{
	int pos = FindPos(dev, val.key);
	if (dev->Hash[pos] == NULL)//�����п�λʱ
	{
		//�������ڴ棬����memcpy����
		dev->Hash[pos] = (pair*)malloc(sizeof(pair));
		memcpy(dev->Hash[pos], &val, sizeof(pair));
		dev->size++;
	}
	else//����û�п�λʱ��������key�ظ���Ҳ�����Ǵ�����
	{
		if (dev->Hash[pos]->key == val.key)//key�ظ�,ֻҪ����������У�����memcpy
		{
			strcpy(dev->Hash[pos]->name, val.name);
		}
		else//������
		{
			printf("�ڴ治�㣬�޷�����\n");
		}
	}
}

//��ӡhsah
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
			printf("ѧ��%d ����%s\n",dev->Hash[i]->key,dev->Hash[i]->name);
		}
	}
}

//����
int main()
{
	HashTable* Class = CreatHash(5);
	pair Stu[4] = { {1,"С��"},{11,"С��"},{3,"С��"},{4,"С��"} };
	for (int i = 0; i < 4; i++)
	{
		Insert(Class, Stu[i]);
	}
	PrintHash(Class);
	printf("\n");
	pair Stu1 = { 21,"С��" };//��������
	Insert(Class, Stu1);
	PrintHash(Class);
	printf("\n");
	pair Stu2 = { 1,"����" };//�ظ�����
	Insert(Class, Stu2);
	PrintHash(Class);
	printf("\n");
	pair Stu3 = { 31,"��˹" };//��֤����
	Insert(Class, Stu3);
	PrintHash(Class);
	return 0;
}