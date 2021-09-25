#pragma once

#include<iostream>

#include<vector>

#include<stack>

using namespace std;

//��ӡ����õ�����
template<class T>
void Print(const vector<T>& dev)
{
	for (int i = 0; i < dev.size(); i++)
	{
		cout << dev[i] << " ";
	}
	cout << endl;
}

//����������,��С����
template<class T>
class Sort
{
public:
	static void Bubble_Sort(vector<T>&);//1.ð������
	static void Insert_Sort(vector<T>&);//2.��������

	//ϣ��������ѡ�������˼������
	//ϣ������˼�����ȴ�������������ô�����־�������������ߣ�С�����־�����ǰ���ߡ�
	static void Shell_Sort(vector<T>&);//3.ϣ������

	static void Select_Sort(vector<T>&);//4.ѡ������

	//�������ڽ��ѵ�ʱ����Ҫ���µ����㷨,��С�������������
	static void AdujstDown(vector<T>& dev, int root,int end)//��root����ʼ���µ���
	{//end���ڼ�¼Ҫ�����������С����СΪend-root,һ��Ҫ�ǵô����������
		int parents = root;
		int child = 2 * parents + 1;
		while (child < end)
		{
			if (child + 1 < end && dev[child] < dev[child + 1])/*�����ҽڵ�*/
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
	static void Heap_Sort(vector<T>&);//����������ĵ����㷨��������໥ƥ�䣬���Խ�����ѻ���С�ѣ�
	//��Ѷ��ڴ�С����С�Ѷ���Ӵ�С

	//��������
	/*
	* ���������˼·�ǣ�
     1.ѡ��һ��key������������Ľ����keyǰ�����ֶ���keyС
     key������ֶ���key������key�������λ�þͷź��ˡ�
     2.Ȼ��ѡ��ݹ����ջ����key֮ǰ��key֮������顣
	*/
	static void Quick_Sort(vector<T>&, int left,int right);//��������ݹ�д��
	static void Quick_Sort_stack(vector<T>& dev, int left, int right);//��������ǵݹ�д��

	//��������
	//�ҵ����ֵ����Сֵ������һ�����飬��ԭ�����е�Ԫ�ذ��������ŵ��´�����������ȥ
	static void Count_Sort(vector<T>&);
};

template<class T>
void Sort<T>::Bubble_Sort(vector<T>& dev)//ð������
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
			if (dev[end + 1] < dev[end])//�Ӻ���ǰ��ʼɸѡ
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
		grep = grep / 3 + 1;//ʹgrepһ�����Ϊ1�������Ϊ1��ʱ��ϣ�������ɲ�������
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
void Sort<T>::Select_Sort(vector<T>& dev)//ѡ��������Ҫ��¼�������ֵ����Сֵ���±�
{
	int left = 0; int right = dev.size() - 1;
	while (left <= right)//���������ұ���������������
	{
		int max = left;
		int min = right;
		for (int i = left; i < right; i++)//һ����������ų���������
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
		//�����ʱleft������Ϊ���ֵ��������left����Ϊ��Сֵ����ʱ��Ҫ�������ֵ��λ��
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
	//����
	for (int i = (dev.size() - 1 - 1) / 2; i >= 0; i--)//��Ϊ���Ľڵ�ֻ��һ����û�б�Ҫ���µ���
	{
		AdujstDown(dev, i, dev.size());//��ÿ�����ݶ��������µ���
	}
	int end = dev.size() - 1;
	//�Ѷ������������������������������һ������
	while (end > 0)
	{
		swap(dev[0], dev[end]);
		//����������µ���
		AdujstDown(dev, 0, end);
		end--;
	}
}

//��������

/*
ע�⣺
1.key��ѡ���Ӱ����������Ч�ʣ����������鱾�ͽӽ�����keyѡȡ�Ĳ����ʿ��������˻���ð������

����������key��ѡ��������ȡ����ʵ��
*/

//����ȡ���Ż�
//����ѡ������Ŀ�ͷ������Ľ�β��������м����������ݽ��бȽ�
//ѡ�����������м��С������key.
template<class T>
int GetMidIndex(vector<T>& dev,int left,int right)//Ҫ������Ϊleft��right,�����м�ֵ���±�
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

//1.ѡ��һ��key������������Ľ����keyǰ�����ֶ���keyС
//key������ֶ���key������key�������λ�þͷź��ˡ�
//���������ַ���ʵ������˼·

//����һ��hoareָ�뷨,�����м�key��λ��(����ָ�뷨)
template<class T>
int _PartSort_Pointer(vector<T>&dev, int left, int right)
{
	int mid = GetMidIndex(dev, left, right);
	swap(dev[left], dev[mid]);
	int key = left;
	//�ұ����ƶ���������ƶ�
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
	swap(dev[key], dev[left]);//֮ǰ������left��mid��λ�ã�֮���ٽ�������
	return left;//����ѭ����ʱ��left=right����key��λ��
}

//���������ڿӷ�
template<class T>
int _PartSort_Hode(vector<T>&dev, int left, int right)
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

//��������ǰ��ָ�뷨
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
		if (dev[cur] <= dev[key] && ++prev != cur)//�����������ҵĶ�·������ֹ���Լ����Լ�����
		{
			swap(dev[prev], dev[cur]);
		}
		++cur;
	}
	swap(&dev[key], &dev[prev]);//������λ�þ��������м����ݵ�λ��
	return prev;
}

template<class T>
void Sort<T>::Quick_Sort(vector<T>& dev,int left,int right)//�ݹ�д��
{
	if (left >= right)//�ݹ����
	{
		return;
	}
	int key = _PartSort_Pointer(dev, left, right);
	//_PartSort_Hode _PartSort_Pointer _PartSort_PrevPoint�����ԣ�������������ͬ����
	//�ݹ�������
	Quick_Sort(dev, left, key - 1);
	//�ݹ�������
	Quick_Sort(dev, key + 1, right);
}

//��������ǵݹ�д��,����ջģ��ݹ�
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
		if (left < key - 1)//������
		{
			tmp.push(left);
			tmp.push(key - 1);
		}
		if (right > key + 1)//������
		{
			tmp.push(key + 1);
			tmp.push(right);
		}
	}
}

template<class T>
void Sort<T>::Count_Sort(vector<T>& dev)//��֧��С����ֻ֧������
{
	//��dev��������ֵ��Сֵ
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
	int arrSize = max - min + 1;//������ֵ=��Сֵ����ʱ����Ĵ�СΪ1
	int* Hash = new int[arrSize];
	//����������ʼ����0����Ϊ��������𵽼���������
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
