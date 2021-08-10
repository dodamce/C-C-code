给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。

vector<vector<int>> generate(int numRows) 
{
	vector<vector<int>> ret;
	for (int i = 1; i <= numRows; i++)
	{
		ret.push_back(vector<int>(i, 1));
	}
	if (numRows<= 2)
	{
		return ret;
	}
	else
	{
		for (int i = 2; i < numRows; i++)
		{
			for (int j = 1; j < ret[i].size() - 1; j++)
			{
				ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
			}
		}
	}
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j <=i; j++)
		{
			cout << ret[i][j] << " ";
		}
		cout << endl;
	}
	return ret;
}
