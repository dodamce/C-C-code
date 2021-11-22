#define _CRT_SECURE_NO_WARNINGS 1

#include"save_contect.h"

void menu()
{
	printf("|-----------------------|\n");
	printf("|        contact        |\n");
	printf("|   1.Add     2.Delete  |\n");
	printf("|   3.Search  4.Modify  |\n");
	printf("|   5.Show    6.Sort    |\n");
	printf("|   0.Exit    7.Save    |\n");
	printf("|-----------------------|\n");
}

void menu_deleat()
{
	printf("****1.通过名字删除****\n");
	printf("****2.通过电话删除****\n");
	printf("*****  3.全部删除*****\n");
	printf("*****0.返回上一步*****\n");
}

void menu_search()
{
	printf("****1.通过名字查找****\n");
	printf("****2.通过电话查找****\n");
	printf("*****0.返回上一步*****\n");
}

void menu_modify()
{
	printf("****1.通过名字查找****\n");
	printf("****2.通过电话查找****\n");
	printf("*****0.返回上一步*****\n");
}

void menu_modify_option()
{
	printf("****1.修改姓名****\n");
	printf("****2.修改年龄****\n");
	printf("****3.修改性别****\n");
	printf("****4.修改电话****\n");
	printf("****5.修改地址****\n");
	printf("***0.返回上一步***\n");
}

void initcontect(contect* p)
{
	p->sz = 0;
	p->capacity = MAX_CAP;
	p->data = (people*)malloc(3*sizeof(people));
	if (p->data == NULL)
	{
		printf("通讯录初始化失败，请退出程序重试\n");
		exit(1);
	}
	LodeContact(p);
	printf("初始化通讯录成功！\n");
}

void CheckCapacity(contect* p)
{
	if (p->sz == p->capacity)
	{
		people* ptr = (people*)realloc(p->data, (p->capacity + 2) * sizeof(people));
		if (ptr == NULL)
		{
			printf("内存不足，增容失败\n");
		}
		else
		{
			p->data = ptr;
			p->capacity += 2;
			printf("提示：通讯录增容成功\n");

		}
	}
}

void Addcontect(contect* p)
{
	int pos = -1;
	CheckCapacity(p);
		printf("请输入姓名:>\n");
		scanf("%s",p->data[p->sz].name);
		printf("请输入年龄:>\n");
		scanf("%d",&p->data[p->sz].age);
		printf("请输入性别:>\n");
		scanf("%s",p->data[p->sz].sex);
		printf("请输入电话:>\n");
		scanf("%s",p->data[p->sz].tele);
		printf("请输入地址:>\n");
		scanf("%s",p->data[p->sz].address);
		p->sz++;
		system("cls");
		pos = search_name2(p->data[p->sz-1].name, p);
		if (pos == -1)
		{
			printf("添加成功\n");
		}
		else
		{
			printf("通讯录中已经有此人\n");
			dele_name2(p->sz,p);
			p->sz--;
			 
		}
}

void Showcontect(contect* p)
{
	if (p->sz == 0)
	{
		system("cls");
		printf("通讯录为空\n");
	} 
	else
	{
		system("cls");
		printf("%-15s\t %-5s\t %-5s\t %-12s\t %-20s\t\n", "姓名","年龄","性别","电话","地址");
		for (int i = 0; i < p->sz; i++)
		{
			printf("%-15s\t %-5d\t %-5s\t %-12s\t %-20s\t\n",p->data[i].name,
			p->data[i].age,p->data[i].sex,p->data[i].tele,p->data[i].address);
		}

	}
}

int search_name2(char name[], contect* ps)
{
	for (int i = 0; i < ps->sz-1; i++)
	{
		if (strcmp(name, ps->data[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
}

int search_name(char name[], contect* ps)
{
	for (int i = 0; i < ps->sz; i++)
	{
		if (strcmp(name, ps->data[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
}

int search_tele(char tele[], contect* ps)
{
	for (int i = 0; i < ps->sz; i++)
	{
		if (strcmp(tele, ps->data[i].tele) == 0)
		{
			return i;
		}
	}
	return -1;
}

void dele_name2(int p,contect* ps)
{
	ps->data[p - 1] = ps->data[p];
}

void Deletecontect(contect* p)
{
	int input = 0;
	int input2 = 0;
	int pos = 0;
	char  name[10] = { 0 };
	char tele[20] = { 0 };
	system("cls");
	do
	{
		menu_deleat();
		scanf("%d",&input);
		switch (input)
		{
		case 1:
			printf("请输入你要删除的人名字\n");
			scanf("%s",name);
			pos= search_name2(name,p);
			if (pos == -1)
			{
				printf("要删除的名字不存在\n");
				printf("\n");
			}
			else
			{
				printf("删除成功\n");
				int j = 0;
				for (j = pos; j < p->sz - 1; j++)
				{
					p->data[pos] = p->data[pos + 1];
				}
				p->sz--;
			}

			break;
		case 2:
			printf("请输入你要删除的人的电话号码\n");
			scanf("%s", tele);
			pos = search_tele(tele, p);
			if (pos == -1)
			{
				printf("要删除的电话号码不存在\n");
				printf("\n");
			}
			else
			{
				printf("删除成功\n");
				int j = 0;
				for(j = pos; j < p->sz - 1; j++)
				{
					p->data[pos] = p->data[pos + 1];
				}
				p->sz--;
			}
			break;
		case 3:
			printf("你确定要全部删除通讯录吗？ 1.确定 2.回到上一步\n");
			scanf("%d",&input2);
			if (input2 == 2);
			else
			{
				FILE* pf = fopen("contect.data", "wb");
				Deletinformation(p);
				system("cls");
				return;
			}
			break;
		case 0:
			system("cls");
			printf("返回成功\n");
			return;
			break;
		default:
			printf("选择错误，请重新选择\n");
			break;
		}
	} while (input);

}

void Searchcontect(contect*ps)
{
	char name[20] = { 0 };
	char tele[20] = { 0 };
	int input = 0;
	int pos = 0;
	system("cls");
	do
	{
		menu_search();
		scanf("%d",&input);
		switch (input)
		{
		case 1:
			system("cls");
			printf("请输入你要查找人的名字\n");
			scanf("%s",name);
			 pos = search_name(name, ps);
			if (pos == -1)
			{
				printf("你要找的名字不存在\n");
			}
			else
			{
				printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "姓名", "年龄", "性别", "电话", "住址");
				printf("%-15s\t%-4d\t%-5s\t%-12s\t%-20s\n",
					ps->data[pos].name,
					ps->data[pos].age,
					ps->data[pos].sex,
					ps->data[pos].tele,
					ps->data[pos].address);
			}
			printf("\n");
			printf("\n");
			break;
		case 2:
			system("cls");
			printf("请输入你要查找人的电话号码\n");
			scanf("%s",tele);
			 pos = search_tele(tele, ps);
			if (pos == -1)
			{
				printf("你要查找的电话号码不存在\n");
			}
			else
			{
				printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "姓名", "年龄", "性别", "电话", "住址");
				printf("%-15s\t%-4d\t%-5s\t%-12s\t%-20s\n",
					ps->data[pos].name,
					ps->data[pos].age,
					ps->data[pos].sex,
					ps->data[pos].tele,
					ps->data[pos].address);
			}
			printf("\n");
			printf("\n");
			break;
		case 0:
			system("cls");
			printf("返回成功\n");
			break;
		default:
			system("cls");
			printf("选择错误，请重新选择\n");
			break;
		}
	} while (input);
}

void Modifycontect(contect* ps)
{
	char name[MAX_NAME] = { 0 };
	char tele[MAX_TELE] = { 0 };
	int pos = 0;
	int input = 0;
	do
	{
		menu_modify();
		scanf("%d",&input);
		switch (input)
		{
		case 1:
			system("cls");
			printf("请输入你要修改人的名字\n");
			scanf("%s", name);
			pos = search_name(name, ps);
			if (pos == -1)
			{
				printf("要修改的人不存在，请确定通讯录信息\n");
				int i = 0;
				printf("\n");
				printf("是否需要返回菜单确认信息 1.返回 2.重新寻找\n");
				scanf("%d",&i);
				if(i == 1)
				{
					return;
				}
			}
			else
			{
				int input2 = 0;
				do
				{
					menu_modify_option();
					scanf("%d",&input2);
					switch (input2)
					{
					case 1:
						printf("你要将原来的名字修改为\n");
						scanf("%s",ps->data[pos].name);
						system("cls");
						break;
					case 2:
						printf("你要将原来的年龄改为\n");
						scanf("%d",&ps->data[pos].age);
						system("cls");
						break;
					case 3:
						printf("你要将原来的性别改为\n");
						scanf("%s",ps->data[pos].sex);
						system("cls");
						break;
					case 4:
						printf("你要将原来的电话改为\n");
						scanf("%s",ps->data[pos].tele);
						system("cls");
						break;
					case 5:
						printf("你要将原来的地址改为\n");
						scanf("%s",ps->data[pos].address);
						system("cls");
						break;
					case 0:
						system("cls");
						printf("返回成功\n");
						break;
					default:
						system("cls");
						printf("输入错误，请重新输入\n");
						break;
					}
				} while (input2);
			}
			break;
		case 2:
			system("cls");
			printf("请输入你要修改人的电话号码\n");
			scanf("%s", tele);
			pos = search_tele(tele, ps);
			if (pos == -1)
			{
				printf("要修改的人不存在，请确定通讯录信息\n");
				int i = 0;
				printf("\n");
				printf("是否需要返回菜单确认信息 1.返回 2.重新寻找\n");
				scanf("%d", &i);
				if (i == 1)
				{
					return;
				}
			}
			else
			{
				int input2 = 0;
				do
				{
					menu_modify_option();
					scanf("%d", &input2);
					switch (input2)
					{
					case 1:
						printf("你要将原来的名字修改为\n");
						scanf("%s", ps->data[pos].name);
						system("cls");
						break;
					case 2:
						printf("你要将原来的年龄改为\n");
						scanf("%d", &ps->data[pos].age);
						system("cls");
						break;
					case 3:
						printf("你要将原来的性别改为\n");
						scanf("%s", ps->data[pos].sex);
						system("cls");
						break;
					case 4:
						printf("你要将原来的电话改为\n");
						scanf("%s", ps->data[pos].tele);
						system("cls");
						break;
					case 5:
						printf("你要将原来的地址改为\n");
						scanf("%s", ps->data[pos].address);
						system("cls");
						break;
					case 0:
						system("cls");
						printf("返回成功\n");
						break;
					default:
						system("cls");
						printf("输入错误，请重新输入\n");
						break;
					}
				} while (input2);
			}
			break;
		case 0:
			system("cls");
			printf("返回成功\n");
			break;
		default:
			system("cls");
			printf("选择错误，请重新选择\n");
			break;
		}

	} while (input);
}

int CmpByName(const void* e1, const void* e2)
{
	return strcmp((const char*)e1, (const char*)e2);
}

void Sortcontect(contect* ps)
{
	qsort(ps->data,ps->sz,sizeof(people), CmpByName);
	system("cls");
	printf("排序成功\n");
}

void Deletinformation(contect* p)
{
	free(p->data);
	p->data= NULL;
	p->sz = 0;
}

void Savecontect(contect*ps)
{
	FILE* pf = fopen("contect.data", "wb");
	if (pf == NULL)
	{
		printf("内存不足，保存失败\n");
		return;
	}
	for (int i = 0; i < ps->sz; i++)
	{
		fwrite(&(ps->data[i]),sizeof(people),1,pf);
	}
	fclose(pf);
	pf = NULL;
	printf("保存成功\n");
}

void LodeContact(contect* p)
{
	FILE* pf = fopen("contect.data", "rb");
	if (pf == NULL)
	{
		printf("加载通讯录失败\n");
		return;
	}
	people tmp = {0};
	while (fread(&tmp, sizeof(people), 1, pf))
	{
		CheckCapacity(p);
		p->data[p->sz] = tmp;
		p->sz++;
	}
	fclose(pf);
	pf = NULL;
}