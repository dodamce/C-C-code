#define _CRT_SECURE_NO_WARNINGS 1

#include"save_contect.h"

int main()
{
	int input = 0;
	int input2 = 0;
	contect con;
	initcontect(&con);
	do
	{
		menu();
		scanf("%d",&input);
		switch (input)
		{
		case Add:
			Addcontect(&con);
			break;
		case Delete:
			Deletecontect(&con);
			break;
		case Search:
			Searchcontect(&con);
			break;
		case Modify:
			Modifycontect(&con);
			break;
		case Show:
			Showcontect(&con);
			break;
		case Sort:
			Sortcontect(&con);
			break;
		case Save:
			Savecontect(&con);
			system("cls");
			printf("����ɹ�\n");
			break;
		case Exit:
			system("cls");
			printf("�˳�ͨѶ¼���粻�������ݻᶪʧ�����ȱ������˳�\n");
			printf("1.�˳�     0.ȡ���˳�\n");
			scanf("%d",&input2);
			if (input2 == 0)
			{
				system("cls");
				input = 1;
				printf("ȡ���˳��ɹ�\n");
			}
			else
			{
				Deletinformation(&con);
				system("cls");
				printf("�˳�ͨѶ¼�ɹ�\n");
			}
			break;
		default:
			system("cls");
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);
	return 0;
}