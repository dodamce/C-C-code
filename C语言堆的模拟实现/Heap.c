#include"Heap.h"

void Swap(HeapDate* x, HeapDate* y)
{
	HeapDate tmp = *x;
	*x = *y;
	*y = tmp;
}

void AdjustDown(HeapDate* a, int n, int parent)//�������
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (a[child] > a[child + 1] && child + 1 < n)
		{
			child++;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
//��ʼ����
void HeapInit(Heap* php, HeapDate* x, int n)
{
	assert(php);
	php->a = (HeapDate*)malloc(sizeof(HeapDate) * n);
	if (php->a == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	else
	{
		memcpy(php->a, x, sizeof(HeapDate)*n);
		php->capicity = n;
		php->size = n;
		for (int i = (php->size - 1 - 1) / 2; i >= 0; i--)
		{
			AdjustDown(php->a, php->size, i);
		}
	}
}
//���ٴ����Ķ�
void HeapDestory(Heap* php)
{
	assert(php);
	free(php->a);
	php->a = NULL;
	php->capicity = php->size = 0;
}
void AdjustUp(int*a,int child)
{
	int parents = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parents])
		{
			Swap(&a[child], &a[parents]);

			child = parents;
			parents = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}
//����в�������
void HeapPush(Heap* php, HeapDate x)
{
	assert(php);
	if (php->capicity == php->size)
	{
		HeapDate* tmp = (HeapDate*)realloc(php->a, sizeof(HeapDate) * (php->capicity) * 2);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		php->a = tmp;
		php->capicity *= 2;
	}
	php->a[php->size] = x;
	php->size++;
	AdjustUp(php->a, php->size - 1);
}
//ɾ���Ѷ����ݣ������������ȣ�
void HeapPop(Heap* php)
{
	assert(php);
	Swap(&php->a[0], &php->a[php->size - 1]);
	php->size--;
	AdjustDown(php->a, php->size, 0);
}
//��öѵĴ�С
int HeapSize(Heap* php)
{
	assert(php);
	return php->size;
}
//��öѶ�������
HeapDate HeapTop(Heap* php)
{
	assert(php);
	return php->a[0];
}
//�ж϶��Ƿ�Ϊ��
bool HeapEmpty(Heap* php)
{
	assert(php);
	if (php->size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	//return php->size==0;���Ϊ�վͷ����棬��Ϊ�վͷ��ؼ�
}
//�Զ���������ʽ��ӡ��
int maxdeap(Heap*php)
{
	assert(php);
	double n = 0.0;
	n = 1.0 * log(php->size) / log(2);
	if (n - (int)n != 0)
	{
		n = (int)n + 1;
	}
	return (int)n;
}
void HeapPrint(Heap* php)
{
	//��ȡ�����������
	int n = maxdeap(php);
	int flag = 0;
	int num = 1;
	for (int i = 0; i < php->size; i++)
	{
		flag++;
		printf("%d ", php->a[i]);
		if (flag == num)
		{
			printf("\n");
			num = num * 2;
			flag = 0;
		}
	}
	printf("\n\n");
}

int* getLeastNumbers(int* arr, int arrSize, int k, int* returnSize) {
	Heap p;
	HeapInit(&p, arr, arrSize);
	int* retArr = (int*)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++)
	{
		retArr[i] = HeapTop(&p);
		HeapPop(&p);
	}
	HeapDestory(&p);
	*returnSize = k;
	return retArr;
}