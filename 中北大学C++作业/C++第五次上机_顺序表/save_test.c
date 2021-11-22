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
			printf("保存成功\n");
			break;
		case Exit:
			system("cls");
			printf("退出通讯录后，如不保存数据会丢失，请先保存再退出\n");
			printf("1.退出     0.取消退出\n");
			scanf("%d",&input2);
			if (input2 == 0)
			{
				system("cls");
				input = 1;
				printf("取消退出成功\n");
			}
			else
			{
				Deletinformation(&con);
				system("cls");
				printf("退出通讯录成功\n");
			}
			break;
		default:
			system("cls");
			printf("选择错误，请重新选择\n");
			break;
		}
	} while (input);
	return 0;
}