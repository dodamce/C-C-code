#include<stdio.h>

#include<stdlib.h>

#include<stdbool.h>

typedef int NodeDate;

typedef struct Node
{
	NodeDate val;
	struct Node* next;

}Node;

typedef struct  Queue
{
	Node* head;//队头队尾队列大小
	Node* tail;
	int size;
}Queue;

Node* CreatNode(NodeDate x)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->val = x;
	NewNode->next = NULL;
	return NewNode;
}

Queue* CreatQueue()
{
	Queue* NewQueue = (Queue*)malloc(sizeof(Queue));
	NewQueue->head = NULL;
	NewQueue->tail = NULL;
	NewQueue->size = 0;
	return NewQueue;
}

int sizeQueue(Queue* tmp)
{
	return tmp->size;
}

bool empty(Queue* tmp)
{
	return tmp->size == 0;//为空返回真
}

//入队操作(尾插法)
void PushQueue(Queue* dev, NodeDate x)
{
	Node* NewNode = CreatNode(x);
	if (dev->size == 0)
	{
		dev->head = dev->tail = NewNode;
	}
	else
	{
		dev->tail->next = NewNode;//尾插法
		dev->tail = NewNode;
	}
	dev->size++;
}

//出队操作(先进先出)头删法
void PopQueue(Queue* dev)
{
	if (dev->size == 0)
		printf("队列为空\n");
	else
	{
		Node* tmp = dev->head->next;
		free(dev->head);
		dev->head = tmp;
		dev->size--;
	}
}

//获取对头元素
NodeDate TopQueue(Queue* dev)
{
	if (dev->size == 0)
	{
		printf("队列为空\n");
		return;
	}
	return dev->head->val;
}

//打印队列
void Print(Queue* dev)
{
	if (empty(dev))
	{
		printf("队列为空\n");
		return;
	}
	Node* tmp = dev->head;
	for (int i = 0; i < dev->size; i++)
	{
		printf("%d ",tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
}

//销毁队列
void Destry(Queue* dev)
{
	if (dev == NULL)
		return;
	while (dev->head != dev->tail)
	{
		Node* tmp = dev->head->next;
		free(dev->head);
		dev->head = tmp;
	}
	free(dev);//不起效果，因为是形参对实参不造成影响
}

//测试
int main()
{
	Queue* lpQueue = CreatQueue();
	Print(lpQueue);
	PushQueue(lpQueue, 1);
	PushQueue(lpQueue, 2);
	Print(lpQueue);
	PopQueue(lpQueue);
	Print(lpQueue);
	NodeDate tmp = TopQueue(lpQueue);
	printf("%d",tmp);
	Destry(lpQueue);
	//lpQueue->size = 0;
	lpQueue = NULL;
	return 0;
}