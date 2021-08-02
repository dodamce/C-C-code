#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std; 


/*
void PrintVector(const vector<int>&v)
{

	vector<int>::const_iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
*/

template <class T>
void PrintVector(const vector<T>&v)
{
	vector<T>::const_iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

void TestVector1()
{
  vector<int>v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  for(size_t i=0;i<v.size();i++)
  {
    cout<<v[i]<<" ";
  }
  cout <<endl;
  vector<int>::iterator it=v.begin();
  while(it!=v.end())
  {
    cout<<*it<<" ";
    it++;
  }
  cout<<endl;
  for(auto e:v)
  {
    cout<<e<< " ";
  }
}


void TestVector2()//��ϰvector����
{
	vector<int> v1;
	vector<int> v2(10, 2);
	vector<int> v3(v2.begin(), v2.end());
	string s1("hello word");
	vector<char> v4(s1.begin(), s1.end());
	vector<string>v5;
	v5.push_back("hello ");
	v5.push_back("word");
	PrintVector(v1);
	PrintVector(v2);
	PrintVector(v3);
	PrintVector(v4);
	PrintVector(v5);
}

void TestVector3()//vector���ݷ�ʽ
{
	vector<int> v1;
	//v1.reserve(99);
	int sz = v1.capacity();
	cout << "sz=" << sz << endl;
	for (int i = 0; i < 100; i++)
	{
		v1.push_back(i);
		if (sz != v1.capacity())
		{
			sz = v1.capacity();
			cout << "sz=" << sz << endl;
		}
	}
}

void TestVector4()//vector�Ĳ�����ɾ��
{
	vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.insert(v.begin()+2, 0);
	PrintVector(v);
	v.erase(v.end()-1);//ɾ�����һ��Ԫ�أ���Ϊ������ҿ���
	PrintVector(v);
	v.erase(v.begin());
	PrintVector(v);
	//v.insert(v.begin())
}

void TestVector5()//������ʧЧ����
{
	vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	vector<int>::iterator pos = find(v.begin(), v.end(),3);
	if (pos != v.end())
	{
		v.insert(pos, 30);//��ʱpos��ָ�����ı�
	}
	PrintVector(v);
	//v.erase(pos);//��v���ݵ�ʱ������
}

void TestVector6()//ɾ��v�е�ż��
{
	vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(4);
	v.push_back(5);
	vector<int>v1(v);
	vector<int>::iterator pos = v.begin();
	while (pos != v.end())
	{
		if (*pos % 2 == 0)
		{
			pos=v.erase(pos);//��vs��Ҫ����pos��ֵ�������������ʧЧ
		}
		else
		{
			pos++;
		}
	}
	PrintVector(v);
	v1.swap(v);//������ַ
	PrintVector(v1);
	PrintVector(v);
}

int main()
{
    //TestVector1();
    //TestVector2();
	//TestVector3();
	//TestVector4();
	//TestVector5();
	TestVector6();
  return 0;
}
