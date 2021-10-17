#define _CRT_SECURE_NO_WARNINGS 1

#define MAXNAME 30
#include<stdio.h>

FILE* InitFile();//加载文件

int CoutSizeLen(FILE*& fp);//计算文件列数

int CoutOffSet(FILE*& fp);//计算一行的偏移量

void PrintCSV(FILE*& fp);//打印表格

void PrintDateCVS(FILE*& fp);//打印表格的数据部分去掉第一行第一列

int CoutFirstStr(FILE*& fp);//计算这一行第一格偏移量