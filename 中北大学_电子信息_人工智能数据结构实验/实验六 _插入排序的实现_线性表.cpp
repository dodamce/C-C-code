#include<iostream>
#include<algorithm>

using namespace std;

template<class Value>
class SeQuence//˳��
{
public:
	SeQuence(int cap = 1) :Capcity(cap),size(0)//Ĭ������
	{
		Table = new Value[Capcity];
	}
	~SeQuence()
	{
		Capcity = 0;
		delete[]Table;
	}

	//˳������
	void Insert(const Value& val)
	{
		_CheckSize();
		Table[size] = val;
		size++;
	}

	//˳���ɾ��
	void Deleat(const Value& val)
	{
		Value* ret = _FindNode(val);
		if (size == 0)
		{
			cout << "��Ϊ�գ�ɾ��ʧ��" << endl;
			return;
		}
		if (ret == nullptr)
		{
			cout << "�޴�Ԫ�أ�ɾ��ʧ��" << endl;
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

	//˳����ӡ
	void Print()
	{
		if (size == 0)
		{
			cout << "˳���Ϊ��" << endl;
			return;
		}
		for (int i = 0; i < size; i++)
		{
			cout << Table[i] << " ";
		}
		cout << endl;
	}

	int FindNode(const Value&val)//˳���Ĳ���,���ز���λ��
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
			cout << "û���ҵ�" << endl;
		}
		return ret;
	}

	//˳��������
	void Sort()
	{
		if (size == 1)//ֻ��һ��Ԫ��
		{
			return;
		}
		cout << "��С��������:" << endl;
		//����˳���Ĳ�������
		//_InsertSort(Table);
		//����˳���ѡ������
		//_SelectSort(Table);
		//����˳����������_�ݹ�
		_Quick_SortR(Table,0,size-1);
	}
private:

	int GetMidIndex(Value* dev, int left, int right)//Ҫ������Ϊleft��right,�����м�ֵ���±�
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
		int key = dev[left];//�������˼·����
		while (left < right)
		{
			while (left < right && dev[right] >= key)
			{
				--right;
			}
			dev[left] = dev[right];//����������ݱ����ǣ����������Ѿ�������ԭ����ֵ��
			//�������Ϊ�Ӵ��ұ߿�ʼ��С���ҵ�С�ĺ�ŵ���ߵĿ���
			//�˺��ұ�Ϊ�Ӵ���߿�ʼ�Ҵ��ҵ���ŵ��ұߵĿ���
			while (left < right && dev[left] <= key)
			{
				++left;
			}
			dev[right] = dev[left];
		}
		//ͬ����Ϊ���ȴ��ҿ�ʼ�ң��������ͣ����ʱһ��������Ҵ��Ҳ��������
		//left=right��ʱ��Ϊ���ұ�ͣ������λ����������һ�����ŵ�����
		//��������ǵ�key
		dev[left] = key;
		return left;
		//��󷵻�key���ڵ�λ�ã�������һ�δ���
	}

	void _Quick_SortR(Value* Table,const int left,const int right)
	{
		if (left >= right)//�ݹ����
		{
			return;
		}
		int key = _PartSort_Hode(Table, left, right);
		//�ݹ�������
		_Quick_SortR(Table, left, key - 1);
		//�ݹ�������
		_Quick_SortR(Table, key + 1, right);
	}

	void _SelectSort(Value* Table)//��ƻ���˳���ѡ������
	{
		int left = 0; int right = size - 1;
		while (left <= right)//���������ұ���������������
		{
			int max = left;
			int min = right;
			for (int i = left; i < right; i++)//һ����������ų���������
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
			//�����ʱleft������Ϊ���ֵ��������left����Ϊ��Сֵ����ʱ��Ҫ�������ֵ��λ��
			if (max == left)
			{
				max = min;
			}
			swap(Table[right], Table[max]);
			++left; --right;
		}
	}

	void _InsertSort(Value* Table)//����˳���Ĳ�������
	{
		for (int i = 0; i < size-1; i++)
		{
			int end = i;
			while (end>= 0)
			{
				if (Table[end + 1] < Table[end])//�Ӻ���ǰ��ʼɸѡ
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
			if (Table[i] == val)//�ҵ���
			{
				return Table + i;
			}
		}
		return nullptr;
	}

	void _CheckSize()//��������Ƿ���,����������
	{
		if (size == Capcity)//����
		{
			Value* NewTable = new Value[2 * Capcity];
			Capcity *= 2;
			memcpy(NewTable, Table, sizeof(Value) * size);
			swap(Table, NewTable);
			cout << "���ݳɹ�" << endl;
			delete[] NewTable;
		}
	}
	int Capcity;//����
	int size;//��С
	Value* Table;
};

//��Ԫ����,����
void Test1()
{
	SeQuence<int>val;
	val.Insert(1);
	val.Insert(2);
}

//����ɾ��,��ӡ
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

//��������
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
		cout << "1.���� 2.ɾ�� 3.���� 4.���� 5.��ӡ 6.�˳�" << endl;
		cin >> Sect;
		switch (Sect)
		{
		case 1:
			cout << "��������ֵ" << endl;
			cin >> Value;
			Table.Insert(Value);
			break;
		case 2:
			cout << "����ɾ����ֵ" << endl;
			cin >> Value;
			Table.Deleat(Value);
			break;
		case 3:
			cout << "����Ҫ���ҵ�ֵ" << endl;
			cin >> Value;
			Pos = Table.FindNode(Value);
			cout << "���ڱ�ĵ�" << Pos << "λ��" << endl;
			break;
		case 4:
			Table.Sort();
			cout << "����ɹ�" << endl;
			break;
		case 5:
			Table.Print();
			break;
		case 6:
			cout << "�˳��ɹ�" << endl;
			flag = 1;
			break;
		default:
			cout << "ѡ�����" << endl;
			break;
		}
	}
	return 0;
}