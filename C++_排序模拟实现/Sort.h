#pragma once

#include<iostream>

#include<vector>

#include<stack>

using namespace std;

//打印排序好的数组
template<class T>
void Print(const vector<T>& dev)
{
	for (int i = 0; i < dev.size(); i++)
	{
		cout << dev[i] << " ";
	}
	cout << endl;
}

//将数组排序,从小到大
template<class T>
class Sort
{
public:
	static void Bubble_Sort(vector<T>&);//1.冒泡排序
	static void Insert_Sort(vector<T>&);//2.插入排序

	//希尔排序与选择排序的思想类似
	//希尔排序思想是先大区间进行排序，让大的数字尽量往数组后面走，小的数字尽量往前面走。
	static void Shell_Sort(vector<T>&);//3.希尔排序

	static void Select_Sort(vector<T>&);//4.选择排序

	//堆排序，在建堆的时候需要向下调整算法,从小到大排序建立大堆
	static void AdujstDown(vector<T>& dev, int root,int end)//从root出开始向下调整
	{//end用于记录要调整的数组大小，大小为end-root,一定要记得传入这个参数
		int parents = root;
		int child = 2 * parents + 1;
		while (child < end)
		{
			if (child + 1 < end && dev[child] < dev[child + 1])/*存在右节点*/
			{
				child++;
			}
			if (dev[parents] < dev[child])
			{
				swap(dev[parents], dev[child]);
			}
			parents = child;
			child = 2 * parents + 1;
		}
	}
	static void Heap_Sort(vector<T>&);//堆排序（上面的调整算法与堆排序相互匹配，可以建立大堆或者小堆）
	//大堆对于从小到大，小堆对象从大到小

	//快速排序
	/*
	* 快速排序的思路是：
     1.选出一个key单趟排序，排序的结果是key前的数字都比key小
     key后的数字都比key大。这样key在数组的位置就放好了。
     2.然后选择递归或者栈处理key之前和key之后的数组。
	*/
	static void Quick_Sort(vector<T>&, int left,int right);//快速排序递归写法
	static void Quick_Sort_stack(vector<T>& dev, int left, int right);//快速排序非递归写法

	//计数排序
	//找到最大值，最小值。创建一个数组，把原数组中的元素按照数量放到新创建的数组中去
	static void Count_Sort(vector<T>&);
};

template<class T>
void Sort<T>::Bubble_Sort(vector<T>& dev)//冒泡排序
{
	for (int i = 0; i < dev.size(); i++)
	{
		for (int j = 0; j < dev.size() - i - 1; j++)
		{
			if (dev[j] > dev[j + 1])
			{
				swap(dev[j], dev[j + 1]);
			}
		}
	}
}

template<class T>
void Sort<T>::Insert_Sort(vector<T>& dev)
{
	for (int i = 0; i < dev.size() - 1; i++)
	{
		int end = i;
		while (end >= 0)
		{
			if (dev[end + 1] < dev[end])//从后向前开始筛选
			{
				swap(dev[end], dev[end + 1]);
				--end;
			}
			else
			{
				break;
			}
		}
	}
}

template<class T>
void Sort<T>::Shell_Sort(vector<T>& dev)
{
	int grep = dev.size();
	while (grep > 1)
	{
		grep = grep / 3 + 1;//使grep一定最后为1，当最后为1的时候希尔排序变成插入排序
		for (int i = 0; i < dev.size() - grep; i++)
		{
			int end = i;
			while (end >= 0)
			{
				if (dev[end] > dev[end + grep])
				{
					swap(dev[end], dev[end + grep]);
					end = end - grep;
				}
				else
				{
					break;
				}
			}
		}
	}
}

template<class T>
void Sort<T>::Select_Sort(vector<T>& dev)//选择排序需要记录的是最大值，最小值的下标
{
	int left = 0; int right = dev.size() - 1;
	while (left <= right)//当左标记与右标记相遇，排序结束
	{
		int max = left;
		int min = right;
		for (int i = left; i < right; i++)//一次排序可以排出两个数据
		{
			if (dev[max] < dev[i])
			{
				max = i;
			}
			if (dev[min] > dev[i])
			{
				min = i;
			}
		}
		swap(dev[left], dev[min]);
		//如果此时left处正好为最大值，交换后left处变为最小值，此时需要更新最大值的位置
		if (max == left)
		{
			max = min;
		}
		swap(dev[right], dev[max]);
		++left; --right;
	}
}

template<class T>
void Sort<T>::Heap_Sort(vector<T>&dev)
{
	//建堆
	for (int i = (dev.size() - 1 - 1) / 2; i >= 0; i--)//因为最后的节点只有一个，没有必要向下调整
	{
		AdujstDown(dev, i, dev.size());//对每个数据都进行向下调整
	}
	int end = dev.size() - 1;
	//堆顶数据最大，最大的在数组最后，与数组最后一个交换
	while (end > 0)
	{
		swap(dev[0], dev[end]);
		//交换完后向下调整
		AdujstDown(dev, 0, end);
		end--;
	}
}

//快速排序

/*
注意：
1.key的选择很影响这个排序的效率，如果这个数组本就接近有序，key选取的不合适快速排序退化成冒泡排序。

针对这种情况key的选择用三数取中来实现
*/

//三数取中优化
//我们选择数组的开头，数组的结尾，数组的中间这三个数据进行比较
//选择这三个数中间大小的数做key.
template<class T>
int GetMidIndex(vector<T>& dev,int left,int right)//要求区间为left到right,返回中间值的下标
{
	int mid = (left + right) / 2;
	if (dev[left] > dev[mid])
	{
		if (dev[mid] > dev[right])
		{
			return mid;
		}
		else if (dev[right] > dev[left])
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	else
	{
		if (dev[mid] < dev[right])
		{
			return mid;
		}
		else if (dev[right] < dev[left])
		{
			return left;
		}
		else
		{
			return right;
		}
	}
}

//1.选出一个key单趟排序，排序的结果是key前的数字都比key小
//key后的数字都比key大。这样key在数组的位置就放好了。
//这里用三种方法实现上述思路

//方法一：hoare指针法,返回中间key的位置(左右指针法)
template<class T>
int _PartSort_Pointer(vector<T>&dev, int left, int right)
{
	int mid = GetMidIndex(dev, left, right);
	swap(dev[left], dev[mid]);
	int key = left;
	//右边先移动，再向后移动
	while (left < right)
	{
		while (dev[right] >= dev[key] && right > left)
		{
			--right;
		}
		while (dev[left] <= dev[key] && left < right)
		{
			++left;
		}
		swap(dev[left], dev[right]);
	}
	swap(dev[key], dev[left]);//之前交换了left与mid的位置，之后再交换回来
	return left;//跳出循环的时候left=right就在key的位置
}

//方法二：挖坑法
template<class T>
int _PartSort_Hode(vector<T>&dev, int left, int right)
{
	int mid = GetMidIndex(dev, left, right);
	swap(dev[left], dev[mid]);
	int key = dev[left];//与上面的思路类似
	while (left < right)
	{
		while (left < right && dev[right] >= key)
		{
			--right;
		}
		dev[left] = dev[right];//这里存在数据被覆盖，但是上面已经保留了原来的值了
		//最左边先为坑从右边开始找小，找到小的后放到左边的坑上
		//此后右边为坑从左边开始找大，找到后放到右边的坑上
		while (left < right && dev[left] <= key)
		{
			++left;
		}
		dev[right] = dev[left];
	}
//同理因为是先从右开始找，所以最后停下来时一定是左边找大找不到，最后
//left=right此时因为是右边停下来的位置所以数据一定被放到坑中
//这里放我们的key
	dev[left] = key;
	return left;
	//最后返回key所在的位置，方便下一次处理
}

//方法三：前后指针法
template<class T>
int _PartSort_PrevPoint(vector<T>&dev, int left, int right)
{
	int mid = GetMidIndex(dev, left, right);
	swap(dev[left], dev[mid]);
	int key = left;
	int prev = left;
	int cur = left + 1;
	while (left < right)
	{
		if (dev[cur] <= dev[key] && ++prev != cur)//不仅利用了且的短路，还防止了自己与自己交换
		{
			swap(dev[prev], dev[cur]);
		}
		++cur;
	}
	swap(&dev[key], &dev[prev]);//出来的位置就是数组中间数据的位置
	return prev;
}

template<class T>
void Sort<T>::Quick_Sort(vector<T>& dev,int left,int right)//递归写法
{
	if (left >= right)//递归出口
	{
		return;
	}
	int key = _PartSort_Pointer(dev, left, right);
	//_PartSort_Hode _PartSort_Pointer _PartSort_PrevPoint都可以，这三个函数相同功能
	//递归左区间
	Quick_Sort(dev, left, key - 1);
	//递归右区间
	Quick_Sort(dev, key + 1, right);
}

//快速排序非递归写法,利用栈模拟递归
template<class T>
void Sort<T>::Quick_Sort_stack(vector<T>& dev, int left, int right)
{
	stack<int>tmp;
	tmp.push(left); tmp.push(right);
	while (!tmp.empty())
	{
		int left = tmp.top();
		tmp.pop();
		int right = tmp.top();
		tmp.pop();
		int key = _PartSort_Pointer(dev, left, right);
		if (left < key - 1)//左区间
		{
			tmp.push(left);
			tmp.push(key - 1);
		}
		if (right > key + 1)//右区间
		{
			tmp.push(key + 1);
			tmp.push(right);
		}
	}
}

template<class T>
void Sort<T>::Count_Sort(vector<T>& dev)//不支持小数，只支持整形
{
	//找dev数组的最大值最小值
	int max = dev[0];
	int min = dev[0];
	for (int i = 0; i < dev.size(); i++)
	{
		if (dev[i] > max)
		{
			max = dev[i];
		}
		if (dev[i] < min)
		{
			min = dev[i];
		}
	}
	int arrSize = max - min + 1;//如果最大值=最小值，此时数组的大小为1
	int* Hash = new int[arrSize];
	//新数组必须初始化成0，因为这个数组起到计数的作用
	if (Hash == nullptr)
	{
		exit(-1);
	}
	memset(Hash, 0, sizeof(int) * arrSize);
	for (int i = 0; i < dev.size(); i++)
	{
		Hash[dev[i] - min]++;
	}
	int j = 0;
	for (int i = 0; i < arrSize; i++)
	{
		if (Hash[i] != 0)
		{
			while (Hash[i]--)
			{
				dev[j] = i + min;
				j++;
			}
		}
	}
}
