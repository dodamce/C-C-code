#include<iostream>
#include<algorithm>

using namespace std;

template<class Value>
class SeQuence//顺序
{
public:
	SeQuence(int cap = 1) :Capcity(cap),size(0)//默认容量
	{
		Table = new Value[Capcity];
	}
	~SeQuence()
	{
		Capcity = 0;
		delete[]Table;
	}

	//顺序表插入
	void Insert(const Value& val)
	{
		_CheckSize();
		Table[size] = val;
		size++;
	}

	//顺序表删除
	void Deleat(const Value& val)
	{
		Value* ret = _FindNode(val);
		if (size == 0)
		{
			cout << "表为空，删除失败" << endl;
			return;
		}
		if (ret == nullptr)
		{
			cout << "无此元素，删除失败" << endl;
			return;
		}
		Value* tmp = Table;
		while (ret != tmp + size)
		{
			*ret = *(ret + 1);
			ret++;
		}
		size--;
	}

	//顺序表打印
	void Print()
	{
		if (size == 0)
		{
			cout << "顺序表为空" << endl;
			return;
		}
		for (int i = 0; i < size; i++)
		{
			cout << Table[i] << " ";
		}
		cout << endl;
	}

	int FindNode(const Value&val)//顺序表的查找,返回查找位置
	{
		int ret = 0;
		bool IsFind = false;
		for (int i = 0; i < size; i++)
		{
			if (Table[i] == val)
			{
				ret = i;
				IsFind = true;
				break;
			}
		}
		if (IsFind == false)
		{
			cout << "没有找到" << endl;
		}
		return ret;
	}

	//顺序表的排序
	void Sort()
	{
		if (size == 1)//只有一个元素
		{
			return;
		}
		cout << "从小到大排序:" << endl;
		//基于顺序表的插入排序
		//_InsertSort(Table);
		//基于顺序表选择排序
		//_SelectSort(Table);
		//基于顺序表快速排序_递归
		_Quick_SortR(Table,0,size-1);
	}
private:

	int GetMidIndex(Value* dev, int left, int right)//要求区间为left到right,返回中间值的下标
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

	int _PartSort_Hode(Value* dev, int left, int right)
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

	void _Quick_SortR(Value* Table,const int left,const int right)
	{
		if (left >= right)//递归出口
		{
			return;
		}
		int key = _PartSort_Hode(Table, left, right);
		//递归左区间
		_Quick_SortR(Table, left, key - 1);
		//递归右区间
		_Quick_SortR(Table, key + 1, right);
	}

	void _SelectSort(Value* Table)//设计基于顺序表选择排序
	{
		int left = 0; int right = size - 1;
		while (left <= right)//当左标记与右标记相遇，排序结束
		{
			int max = left;
			int min = right;
			for (int i = left; i < right; i++)//一次排序可以排出两个数据
			{
				if (Table[max] < Table[i])
				{
					max = i;
				}
				if (Table[min] > Table[i])
				{
					min = i;
				}
			}
			swap(Table[left], Table[min]);
			//如果此时left处正好为最大值，交换后left处变为最小值，此时需要更新最大值的位置
			if (max == left)
			{
				max = min;
			}
			swap(Table[right], Table[max]);
			++left; --right;
		}
	}

	void _InsertSort(Value* Table)//基于顺序表的插入排序
	{
		for (int i = 0; i < size-1; i++)
		{
			int end = i;
			while (end>= 0)
			{
				if (Table[end + 1] < Table[end])//从后向前开始筛选
				{
					swap(Table[end], Table[end + 1]);
					--end;
				}
				else
				{
					break;
				}
			}
		}
	}

	Value* _FindNode(const Value& val)
	{
		for (int i = 0; i < size; i++)
		{
			if (Table[i] == val)//找到了
			{
				return Table + i;
			}
		}
		return nullptr;
	}

	void _CheckSize()//检测容量是否够用,不够用增容
	{
		if (size == Capcity)//增容
		{
			Value* NewTable = new Value[2 * Capcity];
			Capcity *= 2;
			memcpy(NewTable, Table, sizeof(Value) * size);
			swap(Table, NewTable);
			cout << "增容成功" << endl;
			delete[] NewTable;
		}
	}
	int Capcity;//容量
	int size;//大小
	Value* Table;
};

//单元测试,插入
void Test1()
{
	SeQuence<int>val;
	val.Insert(1);
	val.Insert(2);
}

//测试删除,打印
void Test2()
{
	SeQuence<int>val;
	for (int i = 0; i < 10; i++)
	{
		val.Insert(i);
		val.Print();
	}
	for (int i = 0; i < 10; i++)
	{
		val.Deleat(i);
		val.Print();
	}
}

//测试排序
void Test3()
{
	SeQuence<int>val;
	for (int i = 10; i>=0; i--)
	{
		val.Insert(i);
		val.Print();
	}
	val.Sort();
	val.Print();
}

int main()
{
	SeQuence<int>Table;
	int flag = 0;
	int Sect = 0;
	int Value = 0;
	int Pos = 0;
	while (1)
	{
		if (flag == 1)
		{
			break;
		}
		cout << "1.插入 2.删除 3.查找 4.排序 5.打印 6.退出" << endl;
		cin >> Sect;
		switch (Sect)
		{
		case 1:
			cout << "输入插入的值" << endl;
			cin >> Value;
			Table.Insert(Value);
			break;
		case 2:
			cout << "输入删除的值" << endl;
			cin >> Value;
			Table.Deleat(Value);
			break;
		case 3:
			cout << "输入要查找的值" << endl;
			cin >> Value;
			Pos = Table.FindNode(Value);
			cout << "它在表的第" << Pos << "位置" << endl;
			break;
		case 4:
			Table.Sort();
			cout << "排序成功" << endl;
			break;
		case 5:
			Table.Print();
			break;
		case 6:
			cout << "退出成功" << endl;
			flag = 1;
			break;
		default:
			cout << "选择错误" << endl;
			break;
		}
	}
	return 0;
}