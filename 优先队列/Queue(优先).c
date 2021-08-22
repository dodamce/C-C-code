#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<stdbool.h>

#define MAX 10

typedef struct StuDate
{
	int num;//ѧ��
	int grade;//�ɼ�

}StuDate;

typedef struct Queue
{
	int size;
	StuDate StuQueue[MAX];//����10��ѧ����Ϣ
}Queue;

Queue* CreatQueue()
{
	Queue* NewQueue = (Queue*)malloc(sizeof(Queue));
	NewQueue->size = 0;
	//��ѧ����Ϣ�����ʼ��
	memset(NewQueue->StuQueue, 0, sizeof(StuDate) * MAX);
	return NewQueue;
}

int QueueSize(Queue* dev)
{
	return dev->size;
}

bool Empty(Queue* dev)
{
	return dev->size == 0;//Ϊ�շ�����
}

//��Ӳ���
void push(Queue* dev, StuDate val)
{
	if (dev->size == MAX)
	{
		printf("���������޷����\n");
		return;
	}
	dev->StuQueue[dev->size] = val;
	dev->size++;
}

//����
void pop(Queue* dev)
{
	if (Empty(dev))
	{
		printf("����Ϊ�գ��޷�����\n");
		return;
	}
	//Ѱ�����ȶ���ߵĽڵ�
	int MaxStu = 0;
	for (int i = 1; i < dev->size; i++)
	{
		if (dev->StuQueue[MaxStu].grade < dev->StuQueue[i].grade)
		{
			MaxStu = i;
		}
	}
	//�������ݴﵽɾ��
	for (int i = MaxStu; i < dev->size - 1; i++)
	{
		dev->StuQueue[i] = dev->StuQueue[i + 1];
	}
	dev->size--;
}

//��ȡ�Ӷ�Ԫ�ز���
StuDate top(Queue* dev)
{
	if (Empty(dev))
	{
		printf("����Ϊ�ա�\n");
		return;
	}
	//Ѱ�����ȶ���ߵĽڵ�
	int MaxStu = 0;
	for (int i = 1; i < dev->size; i++)
	{
		if (dev->StuQueue[MaxStu].grade < dev->StuQueue[i].grade)
		{
			MaxStu = i;
		}
	}
	return dev->StuQueue[MaxStu];
}


int main()
{
	Queue* Stu = CreatQueue();
	StuDate tmp;//��ȡ�ļ�����
	FILE* fp = fopen("grade.txt", "r");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��\n");
		return -1;
	}

	//ѭ����������
	while (fscanf(fp, "%d %d\n", &tmp.num, &tmp.grade) != EOF)
	{
		push(Stu, tmp);
	}
	fclose(fp);
	int menu = 1;//����
	printf("����\tѧ��\t�ɼ�\t\n");
	while (!Empty(Stu))
	{
		StuDate tmp = top(Stu);
		printf("%d\t%d\t%d\t\n",menu,tmp.num,tmp.grade);
		pop(Stu);
		menu++;
	}
	free(Stu);
	Stu = NULL;
	return 0;
}