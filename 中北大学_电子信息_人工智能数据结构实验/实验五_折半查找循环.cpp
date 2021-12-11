#include<iostream>
#include<vector>
using namespace std;
//思路：先定义grap=1，直接从最小的一个数开始归并，归并一趟后记录宽度的grap*2
//利用for循环来控制归并次数。当grap的宽度>=size-1表明最后一次归并完成

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
void Merge_Sort_NotR(vector<T>& dev)
{
	T* tmp = (T*)malloc(sizeof(int) * dev.size());
	if (tmp == nullptr)
	{
		return;
	}
	int grap = 1;//开始处理宽度为1
	while (grap < dev.size())//当grap小于size时说明还没有进行最后一次归并
	{
		for (int i = 0; i < dev.size(); i += 2 * grap)
		{
			int begin1 = i;
			int end1 = i + grap - 1;
			int begin2 = i + grap;
			int end2 = i + 2 * grap - 1;
			//注意两种特殊情况：
			if (begin2 >= dev.size())//说明right数组不存在不进行归并right
			{
				break;
			}
			if (end2 >= dev.size())//说明right数组部分越界，只用归并没有越界部分的数据
			{
				end2 = dev.size() - 1;
			}
			_Merge(dev, tmp, begin1, end1, begin2, end2);
		}
		grap = grap * 2;
	}
	free(tmp);
}

template<class T>
void Print(const vector<T>&dev)
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
	Merge_Sort_NotR(ret);
	Print(ret);
	return 0;
}