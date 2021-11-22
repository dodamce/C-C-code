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
	printf("****1.ͨ������ɾ��****\n");
	printf("****2.ͨ���绰ɾ��****\n");
	printf("*****  3.ȫ��ɾ��*****\n");
	printf("*****0.������һ��*****\n");
}

void menu_search()
{
	printf("****1.ͨ�����ֲ���****\n");
	printf("****2.ͨ���绰����****\n");
	printf("*****0.������һ��*****\n");
}

void menu_modify()
{
	printf("****1.ͨ�����ֲ���****\n");
	printf("****2.ͨ���绰����****\n");
	printf("*****0.������һ��*****\n");
}

void menu_modify_option()
{
	printf("****1.�޸�����****\n");
	printf("****2.�޸�����****\n");
	printf("****3.�޸��Ա�****\n");
	printf("****4.�޸ĵ绰****\n");
	printf("****5.�޸ĵ�ַ****\n");
	printf("***0.������һ��***\n");
}

void initcontect(contect* p)
{
	p->sz = 0;
	p->capacity = MAX_CAP;
	p->data = (people*)malloc(3*sizeof(people));
	if (p->data == NULL)
	{
		printf("ͨѶ¼��ʼ��ʧ�ܣ����˳���������\n");
		exit(1);
	}
	LodeContact(p);
	printf("��ʼ��ͨѶ¼�ɹ���\n");
}

void CheckCapacity(contect* p)
{
	if (p->sz == p->capacity)
	{
		people* ptr = (people*)realloc(p->data, (p->capacity + 2) * sizeof(people));
		if (ptr == NULL)
		{
			printf("�ڴ治�㣬����ʧ��\n");
		}
		else
		{
			p->data = ptr;
			p->capacity += 2;
			printf("��ʾ��ͨѶ¼���ݳɹ�\n");

		}
	}
}

void Addcontect(contect* p)
{
	int pos = -1;
	CheckCapacity(p);
		printf("����������:>\n");
		scanf("%s",p->data[p->sz].name);
		printf("����������:>\n");
		scanf("%d",&p->data[p->sz].age);
		printf("�������Ա�:>\n");
		scanf("%s",p->data[p->sz].sex);
		printf("������绰:>\n");
		scanf("%s",p->data[p->sz].tele);
		printf("�������ַ:>\n");
		scanf("%s",p->data[p->sz].address);
		p->sz++;
		system("cls");
		pos = search_name2(p->data[p->sz-1].name, p);
		if (pos == -1)
		{
			printf("��ӳɹ�\n");
		}
		else
		{
			printf("ͨѶ¼���Ѿ��д���\n");
			dele_name2(p->sz,p);
			p->sz--;
			 
		}
}

void Showcontect(contect* p)
{
	if (p->sz == 0)
	{
		system("cls");
		printf("ͨѶ¼Ϊ��\n");
	} 
	else
	{
		system("cls");
		printf("%-15s\t %-5s\t %-5s\t %-12s\t %-20s\t\n", "����","����","�Ա�","�绰","��ַ");
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
			printf("��������Ҫɾ����������\n");
			scanf("%s",name);
			pos= search_name2(name,p);
			if (pos == -1)
			{
				printf("Ҫɾ�������ֲ�����\n");
				printf("\n");
			}
			else
			{
				printf("ɾ���ɹ�\n");
				int j = 0;
				for (j = pos; j < p->sz - 1; j++)
				{
					p->data[pos] = p->data[pos + 1];
				}
				p->sz--;
			}

			break;
		case 2:
			printf("��������Ҫɾ�����˵ĵ绰����\n");
			scanf("%s", tele);
			pos = search_tele(tele, p);
			if (pos == -1)
			{
				printf("Ҫɾ���ĵ绰���벻����\n");
				printf("\n");
			}
			else
			{
				printf("ɾ���ɹ�\n");
				int j = 0;
				for(j = pos; j < p->sz - 1; j++)
				{
					p->data[pos] = p->data[pos + 1];
				}
				p->sz--;
			}
			break;
		case 3:
			printf("��ȷ��Ҫȫ��ɾ��ͨѶ¼�� 1.ȷ�� 2.�ص���һ��\n");
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
			printf("���سɹ�\n");
			return;
			break;
		default:
			printf("ѡ�����������ѡ��\n");
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
			printf("��������Ҫ�����˵�����\n");
			scanf("%s",name);
			 pos = search_name(name, ps);
			if (pos == -1)
			{
				printf("��Ҫ�ҵ����ֲ�����\n");
			}
			else
			{
				printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "סַ");
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
			printf("��������Ҫ�����˵ĵ绰����\n");
			scanf("%s",tele);
			 pos = search_tele(tele, ps);
			if (pos == -1)
			{
				printf("��Ҫ���ҵĵ绰���벻����\n");
			}
			else
			{
				printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "סַ");
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
			printf("���سɹ�\n");
			break;
		default:
			system("cls");
			printf("ѡ�����������ѡ��\n");
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
			printf("��������Ҫ�޸��˵�����\n");
			scanf("%s", name);
			pos = search_name(name, ps);
			if (pos == -1)
			{
				printf("Ҫ�޸ĵ��˲����ڣ���ȷ��ͨѶ¼��Ϣ\n");
				int i = 0;
				printf("\n");
				printf("�Ƿ���Ҫ���ز˵�ȷ����Ϣ 1.���� 2.����Ѱ��\n");
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
						printf("��Ҫ��ԭ���������޸�Ϊ\n");
						scanf("%s",ps->data[pos].name);
						system("cls");
						break;
					case 2:
						printf("��Ҫ��ԭ���������Ϊ\n");
						scanf("%d",&ps->data[pos].age);
						system("cls");
						break;
					case 3:
						printf("��Ҫ��ԭ�����Ա��Ϊ\n");
						scanf("%s",ps->data[pos].sex);
						system("cls");
						break;
					case 4:
						printf("��Ҫ��ԭ���ĵ绰��Ϊ\n");
						scanf("%s",ps->data[pos].tele);
						system("cls");
						break;
					case 5:
						printf("��Ҫ��ԭ���ĵ�ַ��Ϊ\n");
						scanf("%s",ps->data[pos].address);
						system("cls");
						break;
					case 0:
						system("cls");
						printf("���سɹ�\n");
						break;
					default:
						system("cls");
						printf("�����������������\n");
						break;
					}
				} while (input2);
			}
			break;
		case 2:
			system("cls");
			printf("��������Ҫ�޸��˵ĵ绰����\n");
			scanf("%s", tele);
			pos = search_tele(tele, ps);
			if (pos == -1)
			{
				printf("Ҫ�޸ĵ��˲����ڣ���ȷ��ͨѶ¼��Ϣ\n");
				int i = 0;
				printf("\n");
				printf("�Ƿ���Ҫ���ز˵�ȷ����Ϣ 1.���� 2.����Ѱ��\n");
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
						printf("��Ҫ��ԭ���������޸�Ϊ\n");
						scanf("%s", ps->data[pos].name);
						system("cls");
						break;
					case 2:
						printf("��Ҫ��ԭ���������Ϊ\n");
						scanf("%d", &ps->data[pos].age);
						system("cls");
						break;
					case 3:
						printf("��Ҫ��ԭ�����Ա��Ϊ\n");
						scanf("%s", ps->data[pos].sex);
						system("cls");
						break;
					case 4:
						printf("��Ҫ��ԭ���ĵ绰��Ϊ\n");
						scanf("%s", ps->data[pos].tele);
						system("cls");
						break;
					case 5:
						printf("��Ҫ��ԭ���ĵ�ַ��Ϊ\n");
						scanf("%s", ps->data[pos].address);
						system("cls");
						break;
					case 0:
						system("cls");
						printf("���سɹ�\n");
						break;
					default:
						system("cls");
						printf("�����������������\n");
						break;
					}
				} while (input2);
			}
			break;
		case 0:
			system("cls");
			printf("���سɹ�\n");
			break;
		default:
			system("cls");
			printf("ѡ�����������ѡ��\n");
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
	printf("����ɹ�\n");
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
		printf("�ڴ治�㣬����ʧ��\n");
		return;
	}
	for (int i = 0; i < ps->sz; i++)
	{
		fwrite(&(ps->data[i]),sizeof(people),1,pf);
	}
	fclose(pf);
	pf = NULL;
	printf("����ɹ�\n");
}

void LodeContact(contect* p)
{
	FILE* pf = fopen("contect.data", "rb");
	if (pf == NULL)
	{
		printf("����ͨѶ¼ʧ��\n");
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