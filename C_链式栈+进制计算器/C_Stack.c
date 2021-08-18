#include<stdio.h>

#include<stdlib.h>

#include<stdbool.h>

typedef int NodeDate;

typedef struct Node//����ڵ�
{
	NodeDate val;
	struct Node* next;
}Node;

//�����ڵ�
Node* CreatNode(NodeDate x)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->val = x;
	return newNode;
}


//ջ�Ľṹ
typedef struct Stack
{
	int size;//ջ�Ĵ�С
	Node* StackTop;//ջ��
}Stack;

//����ջ
Stack* CreatStack()
{
	Stack*newStack = (Stack*)malloc(sizeof(Stack));
	newStack->size = 0;
	newStack->StackTop = NULL;
	return newStack;
}

//����ջ�Ĵ�С
int size(Stack*tmp)
{
	return tmp->size;
}

//�ж��Ƿ�Ϊ��
bool empty(Stack*tmp)
{
	return tmp->size == 0;
}

//��ջ,�������ͷ�巨��ջ���൱�ڲ�ӣ�����ȳ���ջ��ָ��Ҫ��Զָ��ͷ�ڵ�
void push(Stack*PStack,NodeDate x)
{
	Node*newNode = CreatNode(x);
	newNode->next = PStack->StackTop;
	PStack->StackTop = newNode;
	PStack->size++;
}

//��ջ
void pop(Stack*PStack)
{
	if (empty(PStack))
		printf("ջΪ�գ��޷�ɾ��\n");
	else
	{
		Node*next = PStack->StackTop->next;//�ȱ�����һ���ڵ���ɾ��
		free(PStack->StackTop);
		PStack->StackTop = next;
		PStack->size--;
	}
}

//��ȡջ��������
NodeDate top(Stack*PStack)
{
	if (empty(PStack))
	{
		printf("ջΪ�գ�û������\n");
		return;
	}
	else
		return PStack->StackTop->val;
}

//����ջ
void Destory(Stack*PStack)
{

	while (PStack->StackTop)
	{
		Node*tmp = PStack->StackTop->next;
		free(PStack->StackTop);
		PStack->StackTop = tmp;
	}
	free(PStack);
}

//��ӡջ(����Ϊint����)
void Print(Stack*PStack)
{
	Node*tmp = PStack->StackTop;
	while (tmp)
	{
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
}

int main()
{
	Stack*MyStack = CreatStack();
	int num = 111;
	while (num)
	{
		push(MyStack, num % 8);
		num /= 8;
	}
	Print(MyStack);
	return 0;
}
