#include"WPS.h"

void Test1()
{
	WPS chect;
	chect.ReadFile("�ɼ�.csv");
	chect.Print();
	int Pos=chect.FindCheet("ѧ��", "20050443");//ͨ��ѧ�Ų���
	cout << "���ҵ��ı��Ϊ" << endl;
	chect.PrintFindCheet(Pos);
	CHEET Arr = { "ƽ���ɼ�", DtoStr(chect.GetSumNum("�ɼ�")/chect.GetSize(), 2) };
	WPS_Date cheet(Arr);
	chect.InsertDate(cheet);
	chect.Print();
}

int main()
{
	Test1();
	return 0;
}