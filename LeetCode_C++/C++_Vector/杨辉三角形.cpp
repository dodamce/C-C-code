����һ���Ǹ����� numRows�����ɡ�������ǡ���ǰ numRows �С�

�ڡ�������ǡ��У�ÿ�����������Ϸ������Ϸ������ĺ͡�

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
