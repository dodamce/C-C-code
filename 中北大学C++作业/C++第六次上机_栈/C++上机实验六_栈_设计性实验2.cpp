//��̬����ƥ��

#include<iostream>

#include<stack>//C++STL

#include<string>

using namespace std;

class Match
{
public:
	void InSert(char ch)//����ջ��
	{
		Str.push_back(ch);//��¼��ʱ�ַ���
		if (ch == ')' || ch == ']' || ch == '}')//���������Ž�ռ�����������ų�ջ�Ա�
		{
			//��ջ�Ա�
			FindMatch(ch);
		}
		else if (ch == '(' || ch == '[' || ch == '{')//ֻ��������ջ�������ַ�����ջ
		{
			Stk.push(ch);
		}
		if (Stk.empty())
		{
			cout << "����ƥ��" << endl;
		}
		else
		{
			cout << "���Ų�ƥ��" << endl;
		}
	}

	//��ӡ�ִ�
	void PrintStr()
	{
		cout << "��ǰ�ַ���Ϊ" << Str << endl;
		cout << endl << Str;
	}
private:
	void FindMatch(const char ch)
	{
		if ((Stk.top()=='{'&&ch=='}')||(Stk.top()=='('&&ch==')')||(Stk.top()=='['&&ch==']'))
		{
			Stk.pop();//ɾ�����ţ�ƥ���������
		}
	}
	stack<char>Stk;
	string Str;

};

int main()
{
	Match Mh;
	char ch = 0;
	while (cin >> ch)
	{
		Mh.InSert(ch);
		Mh.PrintStr();
	}
	return 0;
}