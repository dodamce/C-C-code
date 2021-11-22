#include<iostream>
#include<string>
#include<queue>

using namespace std;

struct ListNode
{
	string _name;
	int Key = 0;
};

class Line
{
public:
	void PushLineNode()//�����
	{
		ListNode _Name;
		cin >> _Name._name;
		_Name.Key = _Head.size();
		_Head.push(_Name);
		_CopHead.push(_Name);
	}

	void PopLineNode()
	{
		if (_Head.empty())
		{
			cout << "����Ϊ��" << endl;
			return;
		}
		ListNode tmp = _Head.front();
		_Head.pop();
		_CopHead.pop();
		cout << tmp.Key << "->" << tmp._name << "����" << endl;
		cout << "����ʣ����" << endl;
		for (int i = 0; i < _CopHead.size(); i++)
		{
			ListNode s = _CopHead.front();
			cout << s.Key << "->" << s._name << endl;
			_CopHead.pop();
		}
		_CopHead = _Head;//�������캯��
	}
private:
	queue<ListNode>_Head;
	queue<ListNode>_CopHead;
};

int main()
{
	Line line;
	int flag = 1;//�˳���׼
	while (flag)
	{
		cout << "ѡ�� 1.��� 2.���� 3.�˳�" << endl;
		int Input = 0;
		cin >> Input;
		switch (Input)
		{
		case 1:
		{
			cout << "��������˵�����" << endl;
			line.PushLineNode();
			break;
		}
		case 2:
		{
			line.PopLineNode();
			break;
		}
		case 3:
		{
			cout << "�˳��ɹ�" << endl;
			flag = 0;
			break;
		}
		default:
			cout << "�����˳�" << endl;
			flag = 0;
			break;
		}
	}
	return 0;
}