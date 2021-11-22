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
	void PushLineNode()//入队列
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
			cout << "队列为空" << endl;
			return;
		}
		ListNode tmp = _Head.front();
		_Head.pop();
		_CopHead.pop();
		cout << tmp.Key << "->" << tmp._name << "出队" << endl;
		cout << "队列剩余人" << endl;
		for (int i = 0; i < _CopHead.size(); i++)
		{
			ListNode s = _CopHead.front();
			cout << s.Key << "->" << s._name << endl;
			_CopHead.pop();
		}
		_CopHead = _Head;//拷贝构造函数
	}
private:
	queue<ListNode>_Head;
	queue<ListNode>_CopHead;
};

int main()
{
	Line line;
	int flag = 1;//退出标准
	while (flag)
	{
		cout << "选择 1.入队 2.出队 3.退出" << endl;
		int Input = 0;
		cin >> Input;
		switch (Input)
		{
		case 1:
		{
			cout << "输入入队人的名称" << endl;
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
			cout << "退出成功" << endl;
			flag = 0;
			break;
		}
		default:
			cout << "错误退出" << endl;
			flag = 0;
			break;
		}
	}
	return 0;
}