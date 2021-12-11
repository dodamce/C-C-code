#include<iostream>
#include<vector>

using namespace std;

template<class ElemType>
struct MatrixDate
{
	int _row; int _col;
	ElemType _Date;
	MatrixDate(const int row,const int col, ElemType date)
		:_row(row),_col(col),_Date(date)
	{}
	MatrixDate(const MatrixDate<ElemType>& dev)//拷贝构造函数
	{
		_row = dev._row; _col = dev._col; _Date = dev._Date;
	}
};

template<class ElemType>
class Matrix
{
	typedef MatrixDate<ElemType> Date;
public:
	Matrix(const int row, const int col)
		:Row(row),Col(col)
	{}

	Matrix(const int row, const int col, vector<Date>ret)
		:Row(row), Col(col), Table(ret)
	{}

	Matrix(const vector<vector<ElemType>>& dev)
	{
		Row = dev.size();
		Col = dev[0].size();
		Table = Reduce(dev);
	}

	//拷贝构造函数
	Matrix(const Matrix<ElemType>& ret)
	{
		Row = ret.Row;
		Col = ret.Col;
		Table = ret.Table;
	}

	void Insert()
	{
		cout << "输入数组非零数字个数" << endl;
		int Size = 0;
		cin >> Size;
		for (int i = 0; i < Size; i++)
		{
			cout << "请输入第" << i + 1 << "个非零数字_数字+行+列顺序:" << endl;
			int row = 0; int col = 0; ElemType val;
			cin >> val >> row >> col;
			if (IsRightNum(row, col))
			{
				if (Find(row, col) == -1)
				{
					Table.push_back(Date(row - 1, col - 1, val));
				}
				else
				{
					cout << "位置上已经有元素了，重新输入" << endl;
					i--;
				}
			}
			else
			{
				cout << "数据范围存在问题，重新输入" << endl;
				cout << "行<" << Row << "列<" << Col << endl;
				i--;
			}
		}
	}

	void Print()
	{
		for (int row = 0; row < Row; row++)
		{
			for (int col = 0; col < Col; col++)
			{
				int Pos = Find(row, col);
				if (Pos == -1)//没找到
				{
					cout << "0 ";
				}
				else
				{
					cout << Table[Pos]._Date << " ";
				}
			}
			cout << endl;
		}
	}

	Matrix<int> operator+(Matrix<int>&dev)//矩阵加法
	{
		vector<vector<ElemType>>_this = Reduction();
		vector<vector<ElemType>>_dev = dev.Reduction();
		if (Row == dev.Col &&Row == dev.Row)//行列相同可以+
		{
			for (int row = 0; row < dev.Row; row++)
			{
				for (int col = 0; col < dev.Col; col++)
				{
					_this[row][col] += _dev[row][col];
				}
			}
		}
		else
		{
			cout << "行列不同，矩阵不能相加" << endl;
		}
		Matrix<int>ret(_this);
		return ret;
	}

	Matrix<int> operator-(Matrix<int>& dev)//矩阵减法
	{
		vector<vector<ElemType>>_this = Reduction();
		vector<vector<ElemType>>_dev = dev.Reduction();
		if (Row == dev.Col && Row == dev.Row)//行列相同可以-
		{
			for (int row = 0; row < dev.Row; row++)
			{
				for (int col = 0; col < dev.Col; col++)
				{
					_this[row][col] -= _dev[row][col];
				}
			}
		}
		else
		{
			cout << "行列不同，矩阵不能相减" << endl;
		}
		Matrix<int>ret(_this);
		return ret;
	}

	void PrintReduce()
	{
		for (int i = 0; i < Table.size(); i++)
		{
			cout << "元素值:" << Table[i]._Date << " 行:" << Table[i]._row << " 列:" << Table[i]._col << endl;
		}
		cout << endl;
	}

	//矩阵A的列数（col）等于矩阵B的行数（row）时，A与B可以相乘。
	Matrix<ElemType> operator*(Matrix<ElemType>& dev)//矩阵乘
	{
		if (Col != dev.Row)
		{
			cout << "矩阵A的列数（col）等于矩阵B的行数（row）时，A与B可以相乘" << endl;
			cout << "Error" << endl;
			return *this;
		}
		else
		{
			//乘积结果是A的行B的列
			vector<vector<ElemType>>retNR;
			//还原矩阵
			vector<vector<ElemType>>_this = Reduction();
			vector<vector<ElemType>>_dev = dev.Reduction();
			for (int Trow = 0; Trow < Row; Trow++)
			{
				vector<ElemType>tmp;
				for (int Dcol = 0; Dcol < dev.Col; Dcol++)
				{
					int sum = 0;
					for (int Tcol = 0; Tcol < Col; Tcol++)
					{
						sum += _this[Trow][Tcol] * _dev[Tcol][Dcol];
					}
					tmp.push_back(sum);
				}
				retNR.push_back(tmp);
			}
			Matrix<ElemType>ret(Row, dev.Col,Reduce(retNR));
			return ret;
		}
	}

private:
	//压缩矩阵还原算法
	vector<vector<ElemType>> Reduction()//还原矩阵
	{
		vector<vector<ElemType>>ret;
		for (int row = 0; row < Row; row++)
		{
			vector<ElemType>cur;
			for (int col = 0; col < Col; col++)
			{
				int Pos = Find(row, col);
				if (Pos == -1)//没找到
				{
					cur.push_back(0);
				}
				else
				{
					cur.push_back(Table[Pos]._Date);
				}
			}
			ret.push_back(cur);
		}
		return ret;
	}
	//二维数组压缩
	vector<Date>Reduce(const vector<vector<ElemType>>& ret)
	{
		vector<Date>dev;
		if (ret.empty())
		{
			return dev;
		}
		for (int i = 0; i < ret.size(); i++)
		{
			for (int j = 0; j < ret[0].size(); j++)
			{
				if (ret[i][j] != 0)
				{
					dev.push_back(Date(i, j, ret[i][j]));
				}
			}
		}
		return dev;
	}

	int Find(const int row, const int col)//找到了返回下标，找不到返回-1
	{
		for (int i = 0; i < Table.size(); i++)
		{
			if (Table[i]._row == row && Table[i]._col == col)
			{
				return i;
			}
		}
		return -1;
	}

	bool IsRightNum(const int row, const int col)
	{
		if (row >= 0 && row < Row && col >= 0 && col < Col)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	vector<Date>Table;
	int Row;
	int Col;
};

//测试
void Test1()//测试构造函数.测试还原矩阵
{
	Matrix<int>max(3, 4);
	max.Insert();
	max.Print();
}

//void Test2()//测试压缩还原算法
//{
//	vector<vector<int>>ret = { {1,2,3},{0,0,0},{0,2,0} };
//	Matrix<int>Mt(3, 4);
//	Mt.Reduce(ret);
//}

//void test1()//测试矩阵相乘
//{
//	Matrix<int>max(2, 2);
//	max.Insert();
//	Matrix<int>min(2, 3);
//	min.Insert();
//	Matrix<int>ret = max * min;
//	ret.Print();
//}

//void Test3()
//{
//	vector<vector<int>>ret = { {1,2},{1,-1} };
//	Matrix<int>tmp(ret);
//	vector<vector<int>>ret2 = { {1,2,-3,},{-1,1,2} };
//	Matrix<int>tmp2(ret2);
//	Matrix<int>retu = tmp * tmp2;
//	retu.Print();
//}

void InitVector(vector<vector<int>>&ret,int row,int col)
{
	cout << "请输入矩阵" << endl;
	ret.resize(row);
	int Num = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> Num;
			ret[i].push_back(Num);
		}
	}
}

int main()
{
	vector<vector<int>>ret1;
	vector<vector<int>>ret2;
	while (1)
	{
		ret1.clear(); ret2.clear();//清空数组
		cout << "矩阵压缩计算" << endl;
		int Row = 0; int Col = 0;
		cout << "输入矩阵1的行列数为" << endl;
		cin >> Row >> Col;
		InitVector(ret1, Row, Col);
		Matrix<int>Num1(ret1);
		cout << "请输入矩阵2的行列数" << endl;
		cin >> Row >> Col;
		InitVector(ret2, Row, Col);
		Matrix<int>Num2(ret2);
		cout << "选择 + - *运算——A打印两个矩阵的压缩形式" << endl;
		char input = 0;
		cin >> input;
		Matrix<int>ret(0,0);
		switch (input)
		{
		case  '+':
			ret = Num1 + Num2;
			ret.Print();
			cout << "ret压缩形式：" << endl;
			ret.PrintReduce();
			break;
		case '-':
			ret = Num1 - Num2;
			ret.Print();
			cout << "ret压缩形式：" << endl;
			ret.PrintReduce();
			break;
		case '*':
			ret = Num1 * Num2;
			ret.Print();
			cout << "ret压缩形式：" << endl;
			ret.PrintReduce();
			break;
		case 'A':
			cout << "矩阵1压缩形式" << endl;
			Num1.PrintReduce();
			cout << "矩阵2压缩形式" << endl;
			Num2.PrintReduce();
			break;
		default:
			break;
		}
	}
	return 0;
}