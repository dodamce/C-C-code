#include<iostream>
#include<vector>

using namespace std;

template<class T>
void _Merge(vector<T>& dev, T* tmp, int begin1, int end1, int begin2, int end2)
{
	int i = begin1;
	int i2 = begin1;
	//�������������ų�����
	while (begin1 <= end1 && begin2 <= end2)//���������䶼������ʱ
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
	while (begin1 <= end1)//����һ�λ���ʣ���ʱ�����ȫ��������tmp������
	{
		tmp[i++] = dev[begin1++];
	}
	while (begin2 <= end2)//���ڶ��λ���ʣ���ʱ�����ȫ��������tmp������
	{
		tmp[i++] = dev[begin2++];
	}
	//��tmp�������ź����Ԫ�طŻ�dev������
	for (int i = i2; i <= end2; i++)
	{
		dev[i] = tmp[i];
	}
}

template<class T>
void _Merge_Sort(vector<T>& dev, T* tmp, int left, int right)
{
	if (left >= right)//�ݹ����������
	{
		return;
	}
	int mid = (left + right) / 2;
	_Merge_Sort(dev, tmp, left, mid);//�ݹ���
	_Merge_Sort(dev, tmp, mid + 1, right); //�ݹ���
	_Merge(dev, tmp, left, mid, mid + 1, right);//�ݹ鵽��С��Ԫ�󣬽���С��Ԫ�ų������
}

template<class T>
void Merge_Sort(vector<T>& dev)
{
	T* tmp = (T*)malloc(sizeof(int) * dev.size());
	if (tmp == nullptr)
	{
		return;
	}
	_Merge_Sort(dev, tmp, 0, dev.size() - 1);//�ݹ��Ӻ���
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