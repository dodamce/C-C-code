#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdio.h>

using namespace std;

typedef vector<string> CHEET;

const string DtoStr(double val, int fixed) //小数转字符串+保留几位
{
	string str = std::to_string(val);
	return str.substr(0, str.find(".") + fixed + 1);
}

struct WPS_Date
{
	WPS_Date() = default;//指定生成默认构造函数
	WPS_Date(const vector<string>& cheet) :Table(cheet) {}
	vector<string>Table;
};

class WPS
{
	typedef WPS_Date Date;
public:
	//导入文件
	void ReadFile(const string& FileName)
	{
		ifstream ifs(FileName);
		Date Val;
		char ch;
		string buff;
		while ((ch = ifs.get()) != EOF)
		{
			if (ch == '\n')//一行结束
			{
				int Pos = 0;
				int RPos = 0;
				Date Arr;
				while ((Pos = buff.find(",", Pos)) != string::npos)
				{
					Arr.Table.push_back(buff.substr(RPos, Pos-RPos));
					Pos++;
					RPos = Pos;
				}
				Arr.Table.push_back(buff.substr(RPos));
				WPSTable.push_back(Arr);
				buff.clear();
			}
			else
			{
				buff += ch;
			}
		}
	}

	void Print()//打印表格
	{
		for (int i = 0; i < WPSTable.size(); i++)
		{
			for (int j = 0; j < WPSTable[i].Table.size(); j++)
			{
				printf("%-10s\t", WPSTable[i].Table[j].c_str());
			}
			printf("\n");
		}
	}

	void FushTabel()//刷新文件
	{
		ofstream ofs("成绩.csv");
		for (int i = 0; i < WPSTable.size(); i++)
		{
			for (int j = 0; j < WPSTable[i].Table.size(); j++)
			{
				ofs.write(WPSTable[i].Table[j].c_str(), (WPSTable[i].Table[j].size()));
				if (j != WPSTable[i].Table.size() - 1)
				{
					ofs.write(",", 1);
				}
				else
				{
					ofs.write("\n", 1);
				}
			}
		}
	}

	void InsertDate(const Date& val)
	{
		WPSTable.push_back(val);
		//刷新到文件中
		FushTabel();
	}

	int FindCheet(const string& T,const string& dev)//查找T方式查找为val的表格
	{
		int Pos = _FindCol(T);
		return _FindRow(Pos, dev);
	}

	double GetSumNum(const int Pos)//求第几行的数据和
	{
		double Sum = 0.0;
		for (int i = 1; i < WPSTable.size(); i++)
		{
			Sum += stoi(WPSTable[i].Table[Pos]);
		}
		return Sum;
	}

	double GetSumNum(const string& Name)//重载求和方法
	{
		int Pos = _FindCol(Name);
		if (Pos == string::npos)
		{
			cout << "查找不到对应列" << endl;
			return 0.0;
		}
		return GetSumNum(Pos);
	}

	void PrintFindCheet(const int Pos)//打印找到的位置
	{
		for (int j = 0; j < WPSTable[Pos].Table.size(); j++)
		{
			printf("%-10s\t", WPSTable[Pos].Table[j].c_str());
		}
		printf("\n");
	}

	int GetSize() { return WPSTable.size() - 1; }//去除表头的值

private:

	int _FindRow(int Col,const string& dev)
	{
		int Pos = 0;
		bool IsFind = false;
		for (int i = 0; i < WPSTable.size(); i++)
		{
			if (WPSTable[i].Table[Col] == dev)
			{
				IsFind = true;
				break;
			}
			Pos++;
		}
		if (IsFind == true)
		{
			return Pos;
		}
		else
		{
			return string::npos;
		}
	}

	int _FindCol(const string& T)//查找第几列
	{
		int Pos = 0;
		bool IsFind = false;
		for (int j = 0; j < WPSTable[0].Table.size(); j++)
		{
			if (WPSTable[0].Table[j] == T)
			{
				IsFind = true;
				break;
			}
			Pos++;
		}
		if (IsFind == true)
		{
			return Pos;
		}
		else
		{
			return string::npos;
		}
	}

	vector<Date>WPSTable;
};
