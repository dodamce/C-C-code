#include"Sort.h"
//插入排序
void InsertSort(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int end = i;
		int tmp = arr[end + 1];
		while (end >= 0)
		{
			if (tmp < arr[end])
			{
				arr[end + 1] = arr[end];
				--end;
			}
			else
			{
				break;
			}
		}
		arr[end + 1] = tmp;
	}
}

//希尔排序

void ShellSort(int* arr, int size)
{
	int grap = size;
	while (grap > 1)
	{
		grap = grap / 3 + 1;
		for (int i = 0; i < size - grap; i++)
		{
			int end = i;
			int tmp = arr[i + grap];
			while (end >= 0)
			{
				if (tmp < arr[end])
				{
					arr[end + grap] = arr[end];
					end = end - grap;
				}
				else
				{
					break;
				}
			}
			arr[end + grap] = tmp;
		}
	}
}

//选择排序法

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void SelectSort(int* arr, int size)
{
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		int max = left;
		int min = left;
		for (int i = left; i < right; i++)
		{
			if (arr[i] < arr[min])
			{
				min = i;
			}
			if (arr[i] > arr[max])
			{
				max = i;
			}
		}
		swap(&arr[left], &arr[min]);
		//注意如果最大值在最左边，交换后此位置放的是最小值，最大值的位置改变，要更新一下坐标
		if (max == left)
		{
			max = min;
		}
		swap(&arr[right], &arr[max]);
		++left;
		--right;
	}
}

//堆排序

void AdjustDwon(int* a, int n, int root)
{
	int parent = root;
	int child = 2 * parent + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child] < a[child + 1])
		{
			child++;
		}
		if (a[child] > a[parent])
		{
			swap(&a[child], &a[parent]);
		}
		else
		{
			break;
		}
	}

}
void HeapSort(int* a, int n)
{
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDwon(a, n, i);
	}
	int end = n - 1;
	while (end > 0)
	{
		swap(&a[0], &a[end]);
		AdjustDwon(a, end, 0);
		end--;
	}
}

//冒泡排序
void BubbleSort(int* a, int n)
{
	for (int i = 1; i < n - 1; i++)
	{
		int exchange = 1;
		for (int j = 0; j < n - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				exchange = 0;
				swap(&a[j], &a[j + 1]);
			}
		}
		if (exchange == 1)
		{
			break;
		}
	}
}

int GetMidIndex(int* a, int left, int right)//三数取中
{
	int mid = (left + right) >> 1;
	if (a[left] > a[mid])
	{
		if (a[mid] > a[right])
		{
			return mid;
		}
		else if (a[right] > a[left])
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	else     //a[left]<a[mid]
	{
		if (a[mid] < a[right])
		{
			return mid;
		}
		else if (a[right] < a[left])
		{
			return left;
		}
		else
		{
			return right;
		}
	}
}

// 快速排序递归实现
// 快速排序hoare版本
int PartSort1(int* a, int left, int right)
{
	int mid = GetMidIndex(a, left, right);
	swap(&a[left], &a[mid]);
	int key = left;
	while (left < right)
	{
		while (a[right] >= a[key] && right > left)
		{
			right--;
		}
		while (a[left] <= a[key] && left < right)
		{
			left++;
		}
		swap(&a[left], &a[right]);
	}
	swap(&a[key], &a[left]);
	return left;
}
// 快速排序挖坑法
int PartSort2(int* a, int left, int right)
{
	int mid = GetMidIndex(a, left, right);
	swap(&a[left], &a[mid]);
	int key = a[left];
	while (left < right)
	{
		while (left < right&&a[right]>=key)
		{
			--right;
		}
		a[left] = a[right];
		while (left<right&&a[left]<=key)
		{
			++left;
		}
		a[right] = a[left];
	}
	a[left] = key;
	return left;
}
// 快速排序前后指针法
int PartSort3(int* a, int left, int right)
{
	int mid = GetMidIndex(a, left, right);
	swap(&a[left], &a[mid]);
	int key = left;
	int prev = left;
	int cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] < a[key] && ++prev != cur)
		{
			swap(&a[cur], &a[prev]);
		}
		++cur;
	}
	swap(&a[key], &a[prev]);
	return prev;
}

void QuickSort(int* a, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	if (right - left > 20)
	{
		int key = PartSort1(a, left, right);
		QuickSort(a, left, key - 1);
		QuickSort(a, key + 1, right);
	}
	else
	{
		InsertSort(a + left, right - left + 1);
	}
}

// 快速排序 非递归实现
void QuickSortNonR(int* a, int left, int right)
{
	Stack q;
	StackInit(&q);
	StackPush(&q, left);
	StackPush(&q, right);
	while (!StackEmpty(&q))
	{
		int right = StackTop(&q);
		StackPop(&q);
		int left = StackTop(&q);
		StackPop(&q);
		int key=PartSort1(a, left, right);
		if (left < key - 1)
		{
			StackPush(&q, left);
			StackPush(&q, key - 1);
		}
		if (right > key + 1)
		{
			StackPush(&q, key + 1);
			StackPush(&q, right);
		}
	}
	StackDestroy(&q);
}

void _MergeSort(int* a, int* tmp, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) >> 1;
	_MergeSort(a, tmp, left, mid);
	_MergeSort(a, tmp, mid + 1, right);
	_Merge(a, tmp, left, mid, mid + 1, right);
}

// 归并排序递归实现
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	_MergeSort(a, tmp, 0, n - 1);
}
// 归并排序非递归实现

void _Merge(int* a, int* tmp, int begin1, int end1, int begin2, int end2)
{
	int i = begin1;
	int tmp2 = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[i++] = a[begin1++];
		}
		else
		{
			tmp[i++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[i++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[i++] = a[begin2++];
	}
	for (int j = tmp2; j <= end2; j++)
	{
		a[j] = tmp[j];
	}
}

void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int*) * n);
	if(tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	int grap = 1;
	while (grap < n)
	{
		for (int i = 0; i < n; i += 2 * grap)
		{
			int begin1 = i;
			int end1 = i + grap - 1;
			int begin2 = i + grap;
			int end2 = i + 2 * grap - 1;
			if (begin2 >= n)
			{
				break;
			}
			if (end2 >= n)
			{
				end2 = n - 1;
			}
			_Merge(a, tmp, begin1, end1, begin2, end2);
		}
		grap = grap * 2;
	}
	free(tmp);
}

// 计数排序
void CountSort(int* a, int n)
{
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = a[i];
		}
	}
	int rage = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * rage);
	if (count == NULL)
	{
		exit(-1);
	}
	memset(count, 0, sizeof(int) * rage);
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;
	}
	int i = 0;
	for (int j = 0; j < rage; j++)
	{
		while (count[j]--)
		{
			a[i++] = min + j;
		}
	}
}