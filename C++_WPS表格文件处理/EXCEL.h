#define _CRT_SECURE_NO_WARNINGS 1

#define MAXNAME 30
#include<stdio.h>

FILE* InitFile();//�����ļ�

int CoutSizeLen(FILE*& fp);//�����ļ�����

int CoutOffSet(FILE*& fp);//����һ�е�ƫ����

void PrintCSV(FILE*& fp);//��ӡ���

void PrintDateCVS(FILE*& fp);//��ӡ�������ݲ���ȥ����һ�е�һ��

int CoutFirstStr(FILE*& fp);//������һ�е�һ��ƫ����