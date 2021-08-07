#pragma once

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS 1

struct BinaryTreeNode;//Ç°ÖÃÉùÃ÷
typedef struct BinaryTreeNode* Qlistdate;

//typedef char BTDataType;
//
//typedef struct BinaryTreeNode
//{
//	BTDataType _data;
//	struct BinaryTreeNode* _left;
//	struct BinaryTreeNode* _right;
//}BTNode;
//
//typedef struct BTNode* Qlistdate;

typedef struct Qlistnood
{
	struct Qlistnood* next;
	Qlistdate val;
}Qlistnood;

typedef struct Qlist
{
	Qlistnood* head;
	Qlistnood* tail;
}Qlist;



void QlistInit(Qlist*p);
void QlistDestory(Qlist* p);

void QlistPush(Qlist* p, Qlistdate x);
void QlistPup(Qlist*p);
Qlistdate QlistFront(Qlist*p);
Qlistdate QlistBack(Qlist*p);
int QlistEmpty(Qlist* p);
int QlistSize(Qlist*p);

