#include<iostream>
#include<vector>
using namespace std;
//˼·���ȶ���grap=1��ֱ�Ӵ���С��һ������ʼ�鲢���鲢һ�˺��¼��ȵ�grap*2
//����forѭ�������ƹ鲢��������grap�Ŀ��>=size-1�������һ�ι鲢���

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
void Merge_Sort_NotR(vector<T>& dev)
{
	T* tmp = (T*)malloc(sizeof(int) * dev.size());
	if (tmp == nullptr)
	{
		return;
	}
	int grap = 1;//��ʼ������Ϊ1
	while (grap < dev.size())//��grapС��sizeʱ˵����û�н������һ�ι鲢
	{
		for (int i = 0; i < dev.size(); i += 2 * grap)
		{
			int begin1 = i;
			int end1 = i + grap - 1;
			int begin2 = i + grap;
			int end2 = i + 2 * grap - 1;
			//ע���������������
			if (begin2 >= dev.size())//˵��right���鲻���ڲ����й鲢right
			{
				break;
			}
			if (end2 >= dev.size())//˵��right���鲿��Խ�磬ֻ�ù鲢û��Խ�粿�ֵ�����
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