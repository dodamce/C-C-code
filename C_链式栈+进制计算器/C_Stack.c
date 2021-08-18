#include<stdio.h>

#include<stdlib.h>

#include<stdbool.h>

typedef int NodeDate;

typedef struct Node//链表节点
{
	NodeDate val;
	struct Node* next;
}Node;

//创建节点
Node* CreatNode(NodeDate x)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->val = x;
	return newNode;
}


//栈的结构
typedef struct Stack
{
	int size;//栈的大小
	Node* StackTop;//栈顶
}Stack;

//创建栈
Stack* CreatStack()
{
	Stack*newStack = (Stack*)malloc(sizeof(Stack));
	newStack->size = 0;
	newStack->StackTop = NULL;
	return newStack;
}

//返回栈的大小
int size(Stack*tmp)
{
	return tmp->size;
}

//判断是否为空
bool empty(Stack*tmp)
{
	return tmp->size == 0;
}

//入栈,这里采用头插法入栈（相当于插队，后进先出）栈顶指针要永远指向头节点
void push(Stack*PStack,NodeDate x)
{
	Node*newNode = CreatNode(x);
	newNode->next = PStack->StackTop;
	PStack->StackTop = newNode;
	PStack->size++;
}

//出栈
void pop(Stack*PStack)
{
	if (empty(PStack))
		printf("栈为空，无法删除\n");
	else
	{
		Node*next = PStack->StackTop->next;//先保存下一个节点再删除
		free(PStack->StackTop);
		PStack->StackTop = next;
		PStack->size--;
	}
}

//获取栈顶的数据
NodeDate top(Stack*PStack)
{
	if (empty(PStack))
	{
		printf("栈为空，没有数据\n");
		return;
	}
	else
		return PStack->StackTop->val;
}

//销毁栈
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

//打印栈(假设为int类型)
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
