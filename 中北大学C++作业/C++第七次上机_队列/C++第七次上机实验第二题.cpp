//ģ���βεõ�ʵ�εĹ���

//��ֵʱ�ȶ�����ȸ�ֵ

#include<iostream>
#include<queue>
#include<string>
#include<vector>

using namespace std;


int main()
{
	vector<string>Arr;
	queue<string>Num;
	while (1)
	{
		Arr.clear();
		cout << "�붨�������,��' '�ַ��ָ�ÿ������������������Ϻ���'#'����" << endl;
		/* a b c #   ������������*/
		string Str;
		while (cin >> Str && Str != "#")
		{
			Arr.push_back(Str);
		}
		string _Num;
		cout << "�붨�������С,��' '�ַ��ָ�ÿ��������С������������Ϻ���'#'����" << endl;
		while (cin >> _Num && _Num != "#")
		{
			Num.push(_Num);
		}
		for (int i = 0; i < Arr.size(); i++)
		{
			cout << Arr[i] << "=" << Num.front() << endl;
			Num.pop();
		}
	}
	return 0;
}