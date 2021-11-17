#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<vector<string>>ret;//存放结果的数组

bool isAvalid(const vector<string>& board, int row, int col)
{
	int n = board[row].size();
	//检测列中是否有皇后冲突
	for (int i = 0; i < row; i++)
	{
		if (board[i][col] == '*')
		{
			return false;
		}
	}
	//检测对角线是否合法
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

//行数<row的数字为路径，代表已经做过的选择，board列数为选择列表，决策结束条件为row超过board的最后一行，棋盘满了
void backtrack(vector<string>& board, int row)
{
	//结束条件
	if (row == board.size())
	{
		ret.push_back(board);
		return;
	}
	int size = board[row].size();//选择列表的大小
	for (int col = 0; col < size; col++)//在选择列表中做选择
	{
		if (!isAvalid(board, row, col))//排除不合法选择
		{
			continue;
		}
		//做选择
		board[row][col] = '*';
		//进入下一行决策树
		backtrack(board, row + 1);
		//撤销选择
		board[row][col] = '_';
	}
}

void CoutNQueen(const int n)
{
	//初始化棋盘'_'代表空 '*'代表皇后
	vector<string>board(n, string(n, '_'));
	backtrack(board, 0);//回溯算法
}

int main()
{
	int n = 0;
	cout << "请输入皇后数量,皇后数量和棋盘的行列相同" << endl;
	cin >> n;
	CoutNQueen(n);
	//打印所有情况
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
	cout << "一共有" << ret.size() << "种情况" << endl;
	return 0;
}