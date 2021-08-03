#include"Slist2.h"

void testslist()
{
	slist* p = NULL;
	slistpushback(&p, 0);
	slistpushback(&p, 1);
	slistpushback(&p, 2);
	slistpushback(&p, 3);
	slistpushback(&p, 4);
	printslist(p);
}

int main()
{
	testslist();
	return 0;
}