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
	MatrixDate(const MatrixDate<ElemType>& dev)//�������캯��
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

	//�������캯��
	Matrix(const Matrix<ElemType>& ret)
	{
		Row = ret.Row;
		Col = ret.Col;
		Table = ret.Table;
	}

	void Insert()
	{
		cout << "��������������ָ���" << endl;
		int Size = 0;
		cin >> Size;
		for (int i = 0; i < Size; i++)
		{
			cout << "�������" << i + 1 << "����������_����+��+��˳��:" << endl;
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
					cout << "λ�����Ѿ���Ԫ���ˣ���������" << endl;
					i--;
				}
			}
			else
			{
				cout << "���ݷ�Χ�������⣬��������" << endl;
				cout << "��<" << Row << "��<" << Col << endl;
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
				if (Pos == -1)//û�ҵ�
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

	Matrix<int> operator+(Matrix<int>&dev)//����ӷ�
	{
		vector<vector<ElemType>>_this = Reduction();
		vector<vector<ElemType>>_dev = dev.Reduction();
		if (Row == dev.Col &&Row == dev.Row)//������ͬ����+
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
			cout << "���в�ͬ�����������" << endl;
		}
		Matrix<int>ret(_this);
		return ret;
	}

	Matrix<int> operator-(Matrix<int>& dev)//�������
	{
		vector<vector<ElemType>>_this = Reduction();
		vector<vector<ElemType>>_dev = dev.Reduction();
		if (Row == dev.Col && Row == dev.Row)//������ͬ����-
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
			cout << "���в�ͬ�����������" << endl;
		}
		Matrix<int>ret(_this);
		return ret;
	}

	void PrintReduce()
	{
		for (int i = 0; i < Table.size(); i++)
		{
			cout << "Ԫ��ֵ:" << Table[i]._Date << " ��:" << Table[i]._row << " ��:" << Table[i]._col << endl;
		}
		cout << endl;
	}

	//����A��������col�����ھ���B��������row��ʱ��A��B������ˡ�
	Matrix<ElemType> operator*(Matrix<ElemType>& dev)//�����
	{
		if (Col != dev.Row)
		{
			cout << "����A��������col�����ھ���B��������row��ʱ��A��B�������" << endl;
			cout << "Error" << endl;
			return *this;
		}
		else
		{
			//�˻������A����B����
			vector<vector<ElemType>>retNR;
			//��ԭ����
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
	//ѹ������ԭ�㷨
	vector<vector<ElemType>> Reduction()//��ԭ����
	{
		vector<vector<ElemType>>ret;
		for (int row = 0; row < Row; row++)
		{
			vector<ElemType>cur;
			for (int col = 0; col < Col; col++)
			{
				int Pos = Find(row, col);
				if (Pos == -1)//û�ҵ�
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
	//��ά����ѹ��
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

	int Find(const int row, const int col)//�ҵ��˷����±꣬�Ҳ�������-1
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

//����
void Test1()//���Թ��캯��.���Ի�ԭ����
{
	Matrix<int>max(3, 4);
	max.Insert();
	max.Print();
}

//void Test2()//����ѹ����ԭ�㷨
//{
//	vector<vector<int>>ret = { {1,2,3},{0,0,0},{0,2,0} };
//	Matrix<int>Mt(3, 4);
//	Mt.Reduce(ret);
//}

//void test1()//���Ծ������
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
	cout << "���������" << endl;
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
		ret1.clear(); ret2.clear();//�������
		cout << "����ѹ������" << endl;
		int Row = 0; int Col = 0;
		cout << "�������1��������Ϊ" << endl;
		cin >> Row >> Col;
		InitVector(ret1, Row, Col);
		Matrix<int>Num1(ret1);
		cout << "���������2��������" << endl;
		cin >> Row >> Col;
		InitVector(ret2, Row, Col);
		Matrix<int>Num2(ret2);
		cout << "ѡ�� + - *���㡪��A��ӡ���������ѹ����ʽ" << endl;
		char input = 0;
		cin >> input;
		Matrix<int>ret(0,0);
		switch (input)
		{
		case  '+':
			ret = Num1 + Num2;
			ret.Print();
			cout << "retѹ����ʽ��" << endl;
			ret.PrintReduce();
			break;
		case '-':
			ret = Num1 - Num2;
			ret.Print();
			cout << "retѹ����ʽ��" << endl;
			ret.PrintReduce();
			break;
		case '*':
			ret = Num1 * Num2;
			ret.Print();
			cout << "retѹ����ʽ��" << endl;
			ret.PrintReduce();
			break;
		case 'A':
			cout << "����1ѹ����ʽ" << endl;
			Num1.PrintReduce();
			cout << "����2ѹ����ʽ" << endl;
			Num2.PrintReduce();
			break;
		default:
			break;
		}
	}
	return 0;
}