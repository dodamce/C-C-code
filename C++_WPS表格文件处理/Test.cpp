#include"EXCEL.h"

void Test1()//��Ԫ����
{
	FILE* fp = InitFile();
	printf("%d",CoutSizeLen(fp));
}

void Test2()
{
	FILE* fp = InitFile();
	int cout = CoutOffSet(fp);
	printf("%d", CoutSizeLen(fp));
}

void Test3()
{
	FILE* fp = InitFile();
	//PrintCSV(fp);
	printf("\n");
	PrintDateCVS(fp);
}

void Test4()
{
	FILE* fp = InitFile();
}

int main()
{
	Test3();
}