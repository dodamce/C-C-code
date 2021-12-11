#include<iostream>
#include<vector>

using namespace std;

template<class T>
void _Merge(vector<T>& dev, T* tmp, int begin1, int end1, int begin2, int end2)
{
	int i = begin1;
	int i2 = begin1;
	//将两个区间先排成有序
	while (begin1 <= end1 && begin2 <= end2)//这两个区间都有数据时
	{
		if (dev[begin1] < dev[begin2])
		{
			tmp[i++] = dev[begin1++];
		}
		else
		{
			tmp[i++] = dev[begin2++];
		}
	}
	while (begin1 <= end1)//当第一段还有剩余的时候把它全部拷贝到tmp数组中
	{
		tmp[i++] = dev[begin1++];
	}
	while (begin2 <= end2)//当第二段还有剩余的时候把它全部拷贝到tmp数组中
	{
		tmp[i++] = dev[begin2++];
	}
	//将tmp数组中排好序的元素放回dev数组中
	for (int i = i2; i <= end2; i++)
	{
		dev[i] = tmp[i];
	}
}

template<class T>
void _Merge_Sort(vector<T>& dev, T* tmp, int left, int right)
{
	if (left >= right)//递归结束的条件
	{
		return;
	}
	int mid = (left + right) / 2;
	_Merge_Sort(dev, tmp, left, mid);//递归左
	_Merge_Sort(dev, tmp, mid + 1, right); //递归右
	_Merge(dev, tmp, left, mid, mid + 1, right);//递归到最小单元后，将最小单元排成有序的
}

template<class T>
void Merge_Sort(vector<T>& dev)
{
	T* tmp = (T*)malloc(sizeof(int) * dev.size());
	if (tmp == nullptr)
	{
		return;
	}
	_Merge_Sort(dev, tmp, 0, dev.size() - 1);//递归子函数
	free(tmp);
}

template<class T>
void Print(const vector<T>& dev)
{
	for (int i = 0; i < dev.size(); i++)
	{
		cout << dev[i] << " ";
	}
	cout << endl;
}

int main()
{
	vector<int>ret = { 3,6,1,8,3,7,0 };
	Merge_Sort(ret);
	Print(ret);
	return 0;
}