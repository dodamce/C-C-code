#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<stdbool.h>

#define MAX 10

typedef struct StuDate
{
	int num;//学号
	int grade;//成绩

}StuDate;

typedef struct Queue
{
	int size;
	StuDate StuQueue[MAX];//最多放10个学生信息
}Queue;

Queue* CreatQueue()
{
	Queue* NewQueue = (Queue*)malloc(sizeof(Queue));
	NewQueue->size = 0;
	//对学生信息数组初始化
	memset(NewQueue->StuQueue, 0, sizeof(StuDate) * MAX);
	return NewQueue;
}

int QueueSize(Queue* dev)
{
	return dev->size;
}

bool Empty(Queue* dev)
{
	return dev->size == 0;//为空返回真
}

//入队操作
void push(Queue* dev, StuDate val)
{
	if (dev->size == MAX)
	{
		printf("队列满，无法入队\n");
		return;
	}
	dev->StuQueue[dev->size] = val;
	dev->size++;
}

//出队
void pop(Queue* dev)
{
	if (Empty(dev))
	{
		printf("队列为空，无法出队\n");
		return;
	}
	//寻找优先度最高的节点
	int MaxStu = 0;
	for (int i = 1; i < dev->size; i++)
	{
		if (dev->StuQueue[MaxStu].grade < dev->StuQueue[i].grade)
		{
			MaxStu = i;
		}
	}
	//覆盖数据达到删除
	for (int i = MaxStu; i < dev->size - 1; i++)
	{
		dev->StuQueue[i] = dev->StuQueue[i + 1];
	}
	dev->size--;
}

//获取队顶元素操作
StuDate top(Queue* dev)
{
	if (Empty(dev))
	{
		printf("队列为空。\n");
		return;
	}
	//寻找优先度最高的节点
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
	StuDate tmp;//获取文件数据
	FILE* fp = fopen("grade.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}

	//循环读入数据
	while (fscanf(fp, "%d %d\n", &tmp.num, &tmp.grade) != EOF)
	{
		push(Stu, tmp);
	}
	fclose(fp);
	int menu = 1;//排名
	printf("排名\t学号\t成绩\t\n");
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