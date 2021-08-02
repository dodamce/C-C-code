#include"My_vector.h"


void TestVector1()//ºÏ≤‚Œ≤≤Â£¨Œ≤…æ£¨µ¸¥˙∆˜£¨[]÷ÿ‘ÿ,vectorµƒ¥Ú”°
{
	My::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	My::vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i]<<" ";
	}
	cout << endl;
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	My::PrintVector(v);
	v.pop_back();
	v.pop_back();
	My::PrintVector(v);
	v.pop_back();
	My::PrintVector(v);
	v.pop_back();
	My::PrintVector(v);
	//v.pop_back();
}

void TestVector2()//≤‚ ‘resize
{
	My::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.resize(10, 5);
	My::PrintVector(v);
	v.resize(2);
	My::PrintVector(v);
	v.resize(5);
	My::PrintVector(v);
}

void TestVector3()//≤Â»Î≤‚ ‘
{
	My::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	My::vector<int>::iterator pos = find(v.begin(), v.end(), 5);
	v.insert(pos, 30);//posŒª÷√ ß–ß
	My::PrintVector(v);
}

void TestVector4()//…æ≥˝≤‚ ‘
{
	My::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	My::vector<int>::iterator pos = find(v.begin(), v.end(), 4);
	My::vector<int>::iterator tmp = v.erase(pos);
	My::PrintVector(v);
	My::vector<int>::iterator pos2 = find(v.begin(), v.end(), 1);
	v.erase(pos2);
	My::PrintVector(v);
}

int main()
{
	//TestVector1();
	//TestVector2();
	//TestVector3();
	TestVector4();
	return 0;
}