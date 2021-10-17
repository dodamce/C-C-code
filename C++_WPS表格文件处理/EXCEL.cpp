#include"EXCEL.h"

char filename[MAXNAME] = { 0 };

int CoutSizeLen(FILE*& fp)//�����ļ�����
{
	int cout = CoutOffSet(fp);
	if (fp == NULL)
	{
		printf("���ļ�ʧ��");
		return 0;
	}
	int Size = 1;
	char ch = '*';
	while (ch != '\n')
	{
		fscanf(fp, "%c", &ch);
		if (ch == ',')
		{
			Size++;
		}
	}
	fseek(fp, (long)cout, SEEK_SET);
	return Size;
}

FILE* InitFile()
{
	printf("��������ص��ļ���:");
	scanf("%s", filename);
	FILE* fp = fopen(filename, "r");
	return fp;
}

int CoutOffSet(FILE*& fp)
{
	int cout = 1;
	char ch = '*';
	while (ch != '\n')
	{
		fscanf(fp, "%c", &ch);
		cout++;
	}
	fseek(fp, (long)cout, SEEK_SET);
	return cout;
}

void PrintCSV(FILE*& fp)
{
	FILE* tmp = fp;
	char ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		putchar(ch);
	}
	putchar('\n');
	fp = tmp;
}

int CoutFirstStr(FILE*& fp)
{
	FILE* tmp = fp;
	int cout = 1;
	char ch = '*';
	while (ch != ',')
	{
	    fscanf(fp, "%c", &ch);
		cout++;
	}
	fp = tmp;
	return cout;
}

void PrintDateCVS(FILE*& fp)
{
	FILE* tmp = fp;
	int cout = CoutOffSet(fp);
	fseek(fp, (long)cout, SEEK_SET);//������һ��
	int cout2 = CoutOffSet(fp);
	for (int i = 0; i < cout2; i++)
	{
		char ch='*';
		int coutFirst = CoutFirstStr(fp);
		fseek(fp, (long)coutFirst, SEEK_CUR);
		while (ch != '\n')
		{
			ch = fgetc(fp);
			putchar(ch);
		}
	}
	fp = tmp;
}