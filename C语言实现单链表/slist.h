#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

typedef int slistdate;

typedef struct slist
{
	slistdate date;
	struct slist* p;
}slist;

void slistpushback(struct slist** pplist,slistdate x);

void printslist(slist* plist);

void slistpushfrount(struct slist** pplist, slistdate x);

void slistpopback(struct slist** pplist);

void slistfrontback(slist** pplist);

void slistmiddleadd(slist** pplist,int x,slistdate y);
