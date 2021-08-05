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
//初始化堆
void HeapInit(Heap* php, HeapDate* x, int n);
//销毁创建的堆
void HeapDestory(Heap* php);
//向堆中插入数据
void HeapPush(Heap* php, HeapDate x);
//删除堆顶数据（二叉树的祖先）
void HeapPop(Heap* php);
//获得堆顶的数据
HeapDate HeapTop(Heap* php);
//判断堆是否为空
bool HeapEmpty(Heap* php);
//以二叉树的形式打印堆
void HeapPrint(Heap* php);
//获得二叉树的深度
int maxdeap(Heap* php);
//获得堆的大小
int HeapSize(Heap* php);
