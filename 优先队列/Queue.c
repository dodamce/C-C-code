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
	Node* head;//��ͷ��β���д�С
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
	return tmp->size == 0;//Ϊ�շ�����
}

//��Ӳ���(β�巨)
void PushQueue(Queue* dev, NodeDate x)
{
	Node* NewNode = CreatNode(x);
	if (dev->size == 0)
	{
		dev->head = dev->tail = NewNode;
	}
	else
	{
		dev->tail->next = NewNode;//β�巨
		dev->tail = NewNode;
	}
	dev->size++;
}

//���Ӳ���(�Ƚ��ȳ�)ͷɾ��
void PopQueue(Queue* dev)
{
	if (dev->size == 0)
		printf("����Ϊ��\n");
	else
	{
		Node* tmp = dev->head->next;
		free(dev->head);
		dev->head = tmp;
		dev->size--;
	}
}

//��ȡ��ͷԪ��
NodeDate TopQueue(Queue* dev)
{
	if (dev->size == 0)
	{
		printf("����Ϊ��\n");
		return;
	}
	return dev->head->val;
}

//��ӡ����
void Print(Queue* dev)
{
	if (empty(dev))
	{
		printf("����Ϊ��\n");
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

//���ٶ���
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
	free(dev);//����Ч������Ϊ���βζ�ʵ�β����Ӱ��
}

//����
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