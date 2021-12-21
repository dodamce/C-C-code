#include"WPS.h"

void Test1()
{
	WPS chect;
	chect.ReadFile("成绩.csv");
	chect.Print();
	int Pos=chect.FindCheet("学号", "20050443");//通过学号查找
	cout << "查找到的表格为" << endl;
	chect.PrintFindCheet(Pos);
	CHEET Arr = { "平均成绩", DtoStr(chect.GetSumNum("成绩")/chect.GetSize(), 2) };
	WPS_Date cheet(Arr);
	chect.InsertDate(cheet);
	chect.Print();
}

int main()
{
	Test1();
	return 0;
}