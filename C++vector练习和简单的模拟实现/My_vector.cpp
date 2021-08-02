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

void TestVector5()//≤‚ ‘øΩ±¥ππ‘Ï∫Ø ˝ ,=÷ÿ‘ÿ
{
	My::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	My::PrintVector(v);
	My::vector<int> v2(v);
	My::PrintVector(v2);
	My::vector<int> v3;
	v3 = v2;
	My::PrintVector(v3);
}

void TestVector6()//≤‚ ‘◊÷∑˚¥Æ
{
	My::vector<string>v;
	v.push_back("11111111111111");
	v.push_back("2222");
	v.push_back("3333");
	v.push_back("4444");
	v.push_back("5555");
	v.push_back("6666");
	v.push_back("6666");
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << "  ";
	}
}

void TestVector7()//≤‚ ‘∏˜÷÷øΩ±¥ππ‘Ï
{
	My::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	My::vector<int>v2(v.begin(), v.end());
	My::PrintVector(v2);
	My::vector<int>v3(10, 2);
	My::PrintVector(v3);
}

int main()
{
	//TestVector1();
	//TestVector2();
	//TestVector3();
	//TestVector4();
	//TestVector5();
	//TestVector6();
	TestVector7();
	return 0;
}