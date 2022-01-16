#include"BloomFilter.h"

#include<iostream>
using namespace std;

void Test()
{
	BloomFilter<200>bits;
	bits.Set("小红");
	bits.Set("小刚");
	bits.Set("小明");
	if (bits.Find("小明"))
	{
		cout << "Yes" << endl;
	}
}

void Test2()
{
	BloomFilter<400>bits;
	vector<string>Vet;
	int Size = 100;
	for (int i = 0; i < Size; i++)
	{
		string Str = "NUC";
		Str += to_string(2022 + i);
		Vet.push_back(Str);
	}
	for (int i = 0; i < Vet.size(); i++)
	{
		bits.Set(Vet[i]);
	}
	bool IsError = false;
	for (int i = 0; i < Vet.size(); i++)
	{
		if (bits.Find(Vet[i]) == false)
		{
			IsError = true;
			break;
		}
	}
	if (IsError == false)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "Error" << endl;
	}

	cout << "-----------------" << endl;
	vector<string>Vet2;
	for (int i = 0; i < Size; i++)
	{
		string Str = "Dod";
		Str += to_string(2022 + i);
		Vet2.push_back(Str);
	}
	
	for (int i = 0; i < Vet.size(); i++)
	{
		if (bits.Find(Vet2[i]) == true)
		{
			cout << "误判错误" << endl;
		}
	}
}

int main()
{
	//Test();
	Test2();
	return 0;
}