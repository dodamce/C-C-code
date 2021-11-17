#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<vector<string>>ret;//��Ž��������

bool isAvalid(const vector<string>& board, int row, int col)
{
	int n = board[row].size();
	//��������Ƿ��лʺ��ͻ
	for (int i = 0; i < row; i++)
	{
		if (board[i][col] == '*')
		{
			return false;
		}
	}
	//���Խ����Ƿ�Ϸ�
	for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
	{
		if (board[i][j] == '*')
		{
			return false;
		}
	}
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (board[i][j] == '*')
		{
			return false;
		}
	}
	return true;
}

//����<row������Ϊ·���������Ѿ�������ѡ��board����Ϊѡ���б����߽�������Ϊrow����board�����һ�У���������
void backtrack(vector<string>& board, int row)
{
	//��������
	if (row == board.size())
	{
		ret.push_back(board);
		return;
	}
	int size = board[row].size();//ѡ���б�Ĵ�С
	for (int col = 0; col < size; col++)//��ѡ���б�����ѡ��
	{
		if (!isAvalid(board, row, col))//�ų����Ϸ�ѡ��
		{
			continue;
		}
		//��ѡ��
		board[row][col] = '*';
		//������һ�о�����
		backtrack(board, row + 1);
		//����ѡ��
		board[row][col] = '_';
	}
}

void CoutNQueen(const int n)
{
	//��ʼ������'_'����� '*'����ʺ�
	vector<string>board(n, string(n, '_'));
	backtrack(board, 0);//�����㷨
}

int main()
{
	int n = 0;
	cout << "������ʺ�����,�ʺ����������̵�������ͬ" << endl;
	cin >> n;
	CoutNQueen(n);
	//��ӡ�������
	for (int i = 0; i < ret.size(); i++)
	{
		for (int j = 0; j < ret[i].size(); j++)
		{
			for (int k = 0; k < ret[i][j].size(); k++)
			{
				cout << ret[i][j][k] << "|";
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << "һ����" << ret.size() << "�����" << endl;
	return 0;
}