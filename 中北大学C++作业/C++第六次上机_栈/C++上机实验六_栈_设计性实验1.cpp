//�ַ�����ת

#include<iostream>

#include<stack>//C++STL

using namespace std;

//��ӡ��ջԪ�غ���
void PrintStack(stack<char>& Str)
{
	if (Str.empty())//ջΪ�գ�����
	{
		cout << "error" << endl;
	}
	while (!Str.empty())
	{
		cout << Str.top();
		Str.pop();
	}
	cout << endl;
}

int main()
{
	stack<char>Str;//ջ
	while (1)//�������
	{
		//���������ַ������ԡ�#�������ַ��������ı�־
		char ch;
		cout << "ÿ���ַ�����#��β������" << endl;
		while (1)
		{
			cin >> ch;
			if (ch == '#')
				break;//����ѭ����ʼ�����ַ���
			Str.push(ch);
		}
		PrintStack(Str);
	}
	return 0;
}