#include"slist.h"


slist* buylist(slistdate x)
{
	slist* nood = (slist*)malloc(sizeof(slist));
	nood->date = x;
	nood->p = NULL;
	return nood;
}

void slistpushback(struct slist** pplist, slistdate x)
{
	slist* newnood = buylist(x);
	if (*pplist == NULL)
	{
		*pplist = newnood;
	}
	else
	{
		slist* tail = *pplist;
		while (tail->p != NULL)
		{
			tail = tail->p;
		}
		tail->p = newnood;
	}
}

void printslist(slist* plist)
{
	slist* cur = plist;
	while (cur!=NULL)
	{
		printf("%d->",cur->date);
		cur = cur->p;
	}
	printf("\n");
}

void slistpushfrount(struct slist** pplist, slistdate x)
{
	slist* newnood = buylist(x);
	newnood->p = *pplist;
	*pplist = newnood;
}

void slistpopback(slist** pplist)//尾删除
{
	if (*pplist == NULL)
	{
		printf("链表为空，无法删除\n");
		return ;
	}
	else if ((*pplist)->p == NULL)
	{
		free(*pplist);
		*pplist = NULL;
		printf("链表被删空\n");
	}
	else
	{
		slist* tail = *pplist;
		slist* prev = NULL;
		while (tail->p != NULL)
		{
			prev = tail;
			tail = tail->p;
		}
		free(tail);
		tail = NULL;
		prev->p = NULL;
	}
}

void slistfrontback(slist** pplist)
{
	if (*pplist == NULL)
	{
		printf("链表为空无法删除\n");
	}
	else if ((*pplist)->p==NULL)
	{
		printf("链表被删空\n");
		free(*pplist);
		*pplist = NULL;
	}
	else
	{
		slist* ret = *pplist;
		*pplist = (*pplist)->p;
		free(ret);
	}
}

//中间添加

void slistmiddleadd(slist** pplist,int x,slistdate y)
{
	int ret = 0;
	slist* tail = *pplist;
	while (tail != NULL)
	{
		ret++;
		tail = tail->p;
	}
	if (x>ret)
	{
		printf("没有这么多数据，已经帮你尾插\n");
		slistpushback(pplist,y);
	}
	if (x == 0)
	{
		printf("相当于首插\n");
		slistpushfrount(pplist, y);
	}
	else
	{
		slist* tail = *pplist;
		for (int i = 0; i <= x; i++)
		{
			tail = tail->p;
		}
		slist* ret = tail;
		slist* newnood = buylist(y);
		tail = newnood;
		newnood->p = ret;
	}
	
}