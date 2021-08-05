#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

typedef int HeapDate;

typedef struct Heap
{
	HeapDate* a;
	int size;
	int capicity;
}Heap;

void AdjustDown(HeapDate* a, int n, int parent);
//��ʼ����
void HeapInit(Heap* php, HeapDate* x, int n);
//���ٴ����Ķ�
void HeapDestory(Heap* php);
//����в�������
void HeapPush(Heap* php, HeapDate x);
//ɾ���Ѷ����ݣ������������ȣ�
void HeapPop(Heap* php);
//��öѶ�������
HeapDate HeapTop(Heap* php);
//�ж϶��Ƿ�Ϊ��
bool HeapEmpty(Heap* php);
//�Զ���������ʽ��ӡ��
void HeapPrint(Heap* php);
//��ö����������
int maxdeap(Heap* php);
//��öѵĴ�С
int HeapSize(Heap* php);
