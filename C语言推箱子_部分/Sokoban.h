#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

#include<Windows.h>

#include<stdlib.h>

#include<conio.h>



typedef struct GamePos//获取玩家坐标
{
	int x;
	int y;
}GamePos;


//界面优化

void SetColor(int color)
{
	HANDLE hconst = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台窗口
	SetConsoleTextAttribute(hconst, color);
}

void InitGrap()//更改控制台名称，大小
{
	SetConsoleTitle("Sokoban");
	system("mode con cols=26 lines=12");
}

void DrawMap(int arr[10][12])//打印地图  0->空地 1->墙壁 3->箱子目的地 4->箱子 6->人 7->箱子和目的地重合 9->人站在目的地上
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
				printf("■");
			}
			if (arr[i][j] == 3)
			{
				SetColor(FOREGROUND_BLUE);
				printf("☆");
			}
		    if (arr[i][j] == 4)
				printf("□");
			if (arr[i][j] == 6)
				printf("♀");
			if (arr[i][j] == 7)
				printf("★");
			if (arr[i][j]==9)
				printf("♀");
		}
		printf("\n");
	}
}

GamePos GetPlayerPos(int arr[10][12])//获取玩家的坐标
{
	GamePos pos={ -1, -1 };//默认没有找到
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

//向上移动

//交换数据
void swap(int* a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void Up(int arr[10][12])
{
	GamePos pos = GetPlayerPos(arr);
	//人前面是空地可以移动
	if (arr[pos.x - 1][pos.y] == 0)
	{
		arr[pos.x - 1][pos.y] = 6;
		if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}
	//人的前面是目的地
	if (arr[pos.x - 1][pos.y] == 3)
	{
		arr[pos.x - 1][pos.y] = 9;
		if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}

	//人的前面是箱子
	if (arr[pos.x - 1][pos.y] == 4)
	{
		if (arr[pos.x - 1 - 1][pos.y] == 0)//箱子前面是空地
		{
			arr[pos.x - 1 - 1][pos.y] = 4;
			arr[pos.x - 1][pos.y] = 6;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}

		if (arr[pos.x - 1 - 1][pos.y] == 3)//箱子前面是目的地
		{
			arr[pos.x - 1 - 1][pos.y] = 7;
			arr[pos.x - 1][pos.y] = 6;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}
	}

	//人的前面是箱子。箱子在目的地上
	if (arr[pos.x - 1][pos.y] == 7)
	{
		if (arr[pos.x - 1 - 1][pos.y] == 0)//箱子前面是空地
		{
			arr[pos.x - 1 - 1][pos.y] = 4;
			arr[pos.x - 1][pos.y] = 9;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}

		if (arr[pos.x - 1 - 1][pos.y] == 3)//箱子前面是目的地
		{
			arr[pos.x - 1 - 1][pos.y] = 7;
			arr[pos.x - 1][pos.y] = 9;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
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
	//人前面是空地可以移动
	if (arr[pos.x + 1][pos.y] == 0)
	{
		arr[pos.x + 1][pos.y] = 6;
		if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}
	//人的前面是目的地
	if (arr[pos.x + 1][pos.y] == 3)
	{
		arr[pos.x + 1][pos.y] = 9;
		if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}

	//人的前面是箱子
	if (arr[pos.x + 1][pos.y] == 4)
	{
		if (arr[pos.x + 1 + 1][pos.y] == 0)//箱子前面是空地
		{
			arr[pos.x + 1 + 1][pos.y] = 4;
			arr[pos.x + 1][pos.y] = 6;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}

		if (arr[pos.x + 1 + 1][pos.y] == 3)//箱子前面是目的地
		{
			arr[pos.x + 1 + 1][pos.y] = 7;
			arr[pos.x + 1][pos.y] = 6;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}
	}

	//人的前面是箱子。箱子在目的地上
	if (arr[pos.x + 1][pos.y] == 7)
	{
		if (arr[pos.x + 1 + 1][pos.y] == 0)//箱子前面是空地
		{
			arr[pos.x + 1 + 1][pos.y] = 4;
			arr[pos.x + 1][pos.y] = 9;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}

		if (arr[pos.x + 1 + 1][pos.y] == 3)//箱子前面是目的地
		{
			arr[pos.x + 1 + 1][pos.y] = 7;
			arr[pos.x + 1][pos.y] = 9;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
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
	//人前面是空地可以移动
	if (arr[pos.x ][pos.y-1] == 0)
	{
		arr[pos.x ][pos.y-1] = 6;
		if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}
	//人的前面是目的地
	if (arr[pos.x ][pos.y-1] == 3)
	{
		arr[pos.x ][pos.y-1] = 9;
		if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}

	//人的前面是箱子
	if (arr[pos.x][pos.y-1] == 4)
	{
		if (arr[pos.x ][pos.y-1-1] == 0)//箱子前面是空地
		{
			arr[pos.x][pos.y-1-1] = 4;
			arr[pos.x ][pos.y-1] = 6;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}

		if (arr[pos.x][pos.y-1-1] == 3)//箱子前面是目的地
		{
			arr[pos.x ][pos.y-1-1] = 7;
			arr[pos.x][pos.y-1] = 6;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}
	}

	//人的前面是箱子。箱子在目的地上
	if (arr[pos.x + 1][pos.y] == 7)
	{
		if (arr[pos.x ][pos.y-1-1] == 0)//箱子前面是空地
		{
			arr[pos.x ][pos.y-1-1] = 4;
			arr[pos.x ][pos.y-1] = 9;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}

		if (arr[pos.x ][pos.y-1-1] == 3)//箱子前面是目的地
		{
			arr[pos.x][pos.y-1-1] = 7;
			arr[pos.x ][pos.y-1] = 9;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
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
	//人前面是空地可以移动
	if (arr[pos.x][pos.y +1] == 0)
	{
		arr[pos.x][pos.y + 1] = 6;
		if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}
	//人的前面是目的地
	if (arr[pos.x][pos.y + 1] == 3)
	{
		arr[pos.x][pos.y + 1] = 9;
		if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
			arr[pos.x][pos.y] = 3;
		else
			arr[pos.x][pos.y] = 0;
		return;
	}

	//人的前面是箱子
	if (arr[pos.x][pos.y + 1] == 4)
	{
		if (arr[pos.x][pos.y + 1 + 1] == 0)//箱子前面是空地
		{
			arr[pos.x][pos.y + 1 + 1] = 4;
			arr[pos.x][pos.y + 1] = 6;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}

		if (arr[pos.x][pos.y + 1 + 1] == 3)//箱子前面是目的地
		{
			arr[pos.x][pos.y + 1 + 1] = 7;
			arr[pos.x][pos.y + 1] = 6;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return;
		}
	}

	//人的前面是箱子。箱子在目的地上
	if (arr[pos.x][pos.y+1] == 7)
	{
		if (arr[pos.x][pos.y + 1 + 1] == 0)//箱子前面是空地
		{
			arr[pos.x][pos.y + 1 + 1] = 4;
			arr[pos.x][pos.y + 1] = 9;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}

		if (arr[pos.x][pos.y + 1 + 1] == 3)//箱子前面是目的地
		{
			arr[pos.x][pos.y + 1 + 1] = 7;
			arr[pos.x][pos.y + 1] = 9;
			if (arr[pos.x][pos.y] == 9)//原来人在目的地上就还原为目的地
				arr[pos.x][pos.y] = 3;
			else
				arr[pos.x][pos.y] = 0;
			return 0;
		}
	}
}

//计算空余箱子个数
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


