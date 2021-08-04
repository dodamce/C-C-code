#include"Slist.h"

void StackInit(Stack* ps)
{
	assert(ps);
	ps->_top = 0;
	ps->_capacity = 4;
	ps->_a = (STDataType*)malloc(sizeof(STDataType) * (ps->_capacity));
}

void CheckCapcity(Stack* ps)
{
	assert(ps);
	if (ps->_top == ps->_capacity)
	{
		ps->_a = (STDataType*)realloc(ps->_a, sizeof(STDataType) * (ps->_capacity) * 2);
		ps->_capacity = 2 * (ps->_capacity);
	}
	if (ps->_a == NULL)
	{
		printf("realloc fail\n");
		exit(-1);
	}
}

void StackPush(Stack* ps, STDataType data)
{
	assert(ps);
	CheckCapcity(ps);
	ps->_a[ps->_top] = data;
	ps->_top++;
}

void PrintStack(Stack* ps)
{
	assert(ps);
	for (int i = 0; i < ps->_top; i++)
	{
		printf("%d ", ps->_a[i]);
	}
	printf("\n");
}

// 出栈
void StackPop(Stack* ps)
{
	assert(ps);
	assert(StackEmpty(ps));
	ps->_top--;
}
// 获取栈顶元素
STDataType StackTop(Stack* ps)
{
	assert(ps);
	assert(StackEmpty(ps));
	return ps->_a[(ps->_top)-1];
}
// 获取栈中有效元素个数
int StackSize(Stack* ps)
{
	assert(ps);
	return ps->_top;
}
// 检测栈是否为空，如果为空返回非零结果，如果不为空返回0 
int StackEmpty(Stack* ps)
{
	assert(ps);
	if (ps->_top == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
// 销毁栈
void StackDestroy(Stack* ps)
{
	ps->_capacity = 0;
	ps->_top = 0;
	free(ps->_a);
	
}

bool isValid(char* s) {
	Stack st;
	StackInit(&st);
	while (*s)
	{
		if (*s == '[' || *s == '(' || *s == '{')
		{
			StackPush(&st, *s);
			++s;
		}
		else
		{
			if (StackEmpty(&st))
			{
				StackDestroy(&st);
				return false;
			}
			else
			{
				char top = StackTop(&st);
				if (top =='{' && *s != '}' || top == '[' && *s != ']' )//|| top = '(' && *s != ')')
				{
					return false;
				}
				else
				{
					StackPop(&st);
					++s;
				}
			}
		}
	}
	bool ret = StackEmpty(&st);
	StackDestroy(&st);
	return ret;

}