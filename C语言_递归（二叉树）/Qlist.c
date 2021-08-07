#include"Qlist.h"

void QlistInit(Qlist* p)
{
	assert(p);
	p->head = p->tail = NULL;
}

void QlistDestory(Qlist* p)
{
	assert(p);
	Qlistnood* cur = p->head;
	while (cur)
	{
		Qlistnood* next = cur->next;
		free(cur);
		cur = next;
	}
	p->head = p->tail = NULL;
}

void QlistPush(Qlist* p, Qlistdate x)
{
	assert(p);
	Qlistnood* newnood = (Qlistnood*)malloc(sizeof(Qlistnood));
	if (newnood == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	newnood->next = NULL;
	newnood->val = x;
	if (p->head == NULL)
	{
		p->head = p->tail = newnood;
	}
	else
	{
		p->tail->next = newnood;
		p->tail = newnood;
	}
}

void QlistPup(Qlist* p)
{
	assert(p);
	assert(!QlistEmpty(p));
	if (p->head->next == NULL)
	{
		free(p->head);
		p->head = p->tail = NULL;
	}
	else
	{
		Qlistnood* next = p->head->next;
		free(p->head);
		p->head = next;
	}
}

Qlistdate QlistFront(Qlist* p)
{
	assert(p);
	assert(!QlistEmpty(p));
	return p->head->val;
}

Qlistdate QlistBack(Qlist* p)
{
	assert(p);
	assert(!QlistEmpty(p));
	return p->tail->val;
}

int QlistEmpty(Qlist* p)
{
	if (p->head == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int QlistSize(Qlist* p)
{
	int size = 0;
	Qlistnood* cur = p->head;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return size;
}

