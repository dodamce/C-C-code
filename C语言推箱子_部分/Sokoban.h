#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

#include<Windows.h>

#include<stdlib.h>

#include<conio.h>



typedef struct GamePos//��ȡ�������
{
	int x;
	int y;
}GamePos;


//�����Ż�

void SetColor(int color)
{
	HANDLE hconst = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨����
	SetConsoleTextAttribute(hconst, color);
}

void InitGrap()//���Ŀ���̨���ƣ���С
{
	SetConsoleTitle("Sokoban");
	system("mode con cols=26 lines=12");
}

void DrawMap(int arr[10][12])//��ӡ��ͼ  0->�յ� 1->ǽ�� 3->����Ŀ�ĵ� 4->���� 6->�� 7->���Ӻ�Ŀ�ĵ��غ� 9->��վ��Ŀ�ĵ���
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (arr[i][j] == 0)
				printf("  ");
			if (arr[i][j] == 1)
			{
				SetColor(FOREGROUND_RED);
				printf("��");
			}
			if (arr[i][j] == 3)
			{
				SetColor(FOREGROUND_BLUE);
				printf("��");
			}
		    if (arr[i][j] == 4)
				printf("��");
			if (arr[i][j] == 6)
				printf("��");
			if (arr[i][j] == 7)
				printf("��");
			if (arr[i][j]==9)
				printf("��");
		}
		printf("\n");
	}
}

GamePos GetPlayerPos(int arr[10][12])//��ȡ��ҵ�����
{
	GamePos pos={ -1, -1 };//Ĭ��û���ҵ�
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (arr[i][j] == 6 || arr[i][j] == 9)
			{
				pos.x = i;
				pos.y = j;
				return pos;
			}
		}
	}
	return pos;
}

//�����ƶ�

//��������
void swap(int* a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void Up(int arr[10][12])
{
	GamePos pos = GetPlayerPos(arr);
	//��ǰ���ǿյؿ����ƶ�
	if (arr[pos.x - 1][pos.y] == 0)
	{
		arr[pos.x - 1][pos.y] = 6;
		if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}
	//�˵�ǰ����Ŀ�ĵ�
	if (arr[pos.x - 1][pos.y] == 3)
	{
		arr[pos.x - 1][pos.y] = 9;
		if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}

	//�˵�ǰ��������
	if (arr[pos.x - 1][pos.y] == 4)
	{
		if (arr[pos.x - 1 - 1][pos.y] == 0)//����ǰ���ǿյ�
		{
			arr[pos.x - 1 - 1][pos.y] = 4;
			arr[pos.x - 1][pos.y] = 6;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}

		if (arr[pos.x - 1 - 1][pos.y] == 3)//����ǰ����Ŀ�ĵ�
		{
			arr[pos.x - 1 - 1][pos.y] = 7;
			arr[pos.x - 1][pos.y] = 6;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}
	}

	//�˵�ǰ�������ӡ�������Ŀ�ĵ���
	if (arr[pos.x - 1][pos.y] == 7)
	{
		if (arr[pos.x - 1 - 1][pos.y] == 0)//����ǰ���ǿյ�
		{
			arr[pos.x - 1 - 1][pos.y] = 4;
			arr[pos.x - 1][pos.y] = 9;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}

		if (arr[pos.x - 1 - 1][pos.y] == 3)//����ǰ����Ŀ�ĵ�
		{
			arr[pos.x - 1 - 1][pos.y] = 7;
			arr[pos.x - 1][pos.y] = 9;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}
	}
}

void Down(int arr[10][12])
{
	GamePos pos = GetPlayerPos(arr);
	//��ǰ���ǿյؿ����ƶ�
	if (arr[pos.x + 1][pos.y] == 0)
	{
		arr[pos.x + 1][pos.y] = 6;
		if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}
	//�˵�ǰ����Ŀ�ĵ�
	if (arr[pos.x + 1][pos.y] == 3)
	{
		arr[pos.x + 1][pos.y] = 9;
		if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}

	//�˵�ǰ��������
	if (arr[pos.x + 1][pos.y] == 4)
	{
		if (arr[pos.x + 1 + 1][pos.y] == 0)//����ǰ���ǿյ�
		{
			arr[pos.x + 1 + 1][pos.y] = 4;
			arr[pos.x + 1][pos.y] = 6;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}

		if (arr[pos.x + 1 + 1][pos.y] == 3)//����ǰ����Ŀ�ĵ�
		{
			arr[pos.x + 1 + 1][pos.y] = 7;
			arr[pos.x + 1][pos.y] = 6;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}
	}

	//�˵�ǰ�������ӡ�������Ŀ�ĵ���
	if (arr[pos.x + 1][pos.y] == 7)
	{
		if (arr[pos.x + 1 + 1][pos.y] == 0)//����ǰ���ǿյ�
		{
			arr[pos.x + 1 + 1][pos.y] = 4;
			arr[pos.x + 1][pos.y] = 9;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}

		if (arr[pos.x + 1 + 1][pos.y] == 3)//����ǰ����Ŀ�ĵ�
		{
			arr[pos.x + 1 + 1][pos.y] = 7;
			arr[pos.x + 1][pos.y] = 9;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}
	}
}

void Left(int arr[10][12])
{
	GamePos pos = GetPlayerPos(arr);
	//��ǰ���ǿյؿ����ƶ�
	if (arr[pos.x ][pos.y-1] == 0)
	{
		arr[pos.x ][pos.y-1] = 6;
		if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}
	//�˵�ǰ����Ŀ�ĵ�
	if (arr[pos.x ][pos.y-1] == 3)
	{
		arr[pos.x ][pos.y-1] = 9;
		if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}

	//�˵�ǰ��������
	if (arr[pos.x][pos.y-1] == 4)
	{
		if (arr[pos.x ][pos.y-1-1] == 0)//����ǰ���ǿյ�
		{
			arr[pos.x][pos.y-1-1] = 4;
			arr[pos.x ][pos.y-1] = 6;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}

		if (arr[pos.x][pos.y-1-1] == 3)//����ǰ����Ŀ�ĵ�
		{
			arr[pos.x ][pos.y-1-1] = 7;
			arr[pos.x][pos.y-1] = 6;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}
	}

	//�˵�ǰ�������ӡ�������Ŀ�ĵ���
	if (arr[pos.x + 1][pos.y] == 7)
	{
		if (arr[pos.x ][pos.y-1-1] == 0)//����ǰ���ǿյ�
		{
			arr[pos.x ][pos.y-1-1] = 4;
			arr[pos.x ][pos.y-1] = 9;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}

		if (arr[pos.x ][pos.y-1-1] == 3)//����ǰ����Ŀ�ĵ�
		{
			arr[pos.x][pos.y-1-1] = 7;
			arr[pos.x ][pos.y-1] = 9;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}
	}
}

void Right(int arr[10][12])
{
	GamePos pos = GetPlayerPos(arr);
	//��ǰ���ǿյؿ����ƶ�
	if (arr[pos.x][pos.y +1] == 0)
	{
		arr[pos.x][pos.y + 1] = 6;
		if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}
	//�˵�ǰ����Ŀ�ĵ�
	if (arr[pos.x][pos.y + 1] == 3)
	{
		arr[pos.x][pos.y + 1] = 9;
		if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}

	//�˵�ǰ��������
	if (arr[pos.x][pos.y + 1] == 4)
	{
		if (arr[pos.x][pos.y + 1 + 1] == 0)//����ǰ���ǿյ�
		{
			arr[pos.x][pos.y + 1 + 1] = 4;
			arr[pos.x][pos.y + 1] = 6;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}

		if (arr[pos.x][pos.y + 1 + 1] == 3)//����ǰ����Ŀ�ĵ�
		{
			arr[pos.x][pos.y + 1 + 1] = 7;
			arr[pos.x][pos.y + 1] = 6;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}
	}

	//�˵�ǰ�������ӡ�������Ŀ�ĵ���
	if (arr[pos.x][pos.y+1] == 7)
	{
		if (arr[pos.x][pos.y + 1 + 1] == 0)//����ǰ���ǿյ�
		{
			arr[pos.x][pos.y + 1 + 1] = 4;
			arr[pos.x][pos.y + 1] = 9;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}

		if (arr[pos.x][pos.y + 1 + 1] == 3)//����ǰ����Ŀ�ĵ�
		{
			arr[pos.x][pos.y + 1 + 1] = 7;
			arr[pos.x][pos.y + 1] = 9;
			if (arr[pos.x][pos.y] == 9)//ԭ������Ŀ�ĵ��Ͼͻ�ԭΪĿ�ĵ�
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}
	}
}

//����������Ӹ���
int CoutBox( int arr[10][12])
{
	int cout = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (arr[i][j] == 4)
			{
				cout++;
			}
		}
	}
	return cout;
}


