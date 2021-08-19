#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>

//数字1表示为墙或已经走过的位置，0表示可以走的位置.地图就是个二维数组

typedef struct pos //运动位置(行列)
{
	int row;
	int col;
}pos;

pos PosStack[100];//存放每次寻路的坐标（数组栈）

int StackTop = -1;//栈顶标记

//生成迷宫

int** CreatArray(int row, int col)
{
	int** map = (int**)malloc(sizeof(int*)*row);//row行，每行放col个int数据
	for (int i = 0; i < row; i++)
	{
		map[i] = (int*)malloc(sizeof(int)*col);//每行有col个int
	}
	return map;
}

int**map;//全局变量存地图
int n;//地图大小

void CreatMap()
{
	printf("输入迷宫大小\n");
	scanf("%d",&n);
	map = CreatArray(n + 2, n + 2);//加上前后边框
	//输入迷宫（用户输入，这里不采用随机数生成）
	printf("输入迷宫结构\n");
	//加了边框，所以for循环从1开始
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
	//加边框
	for (int i = 0; i < n + 2; i++)
	{
		map[0][i] = 1;
		map[n + 1][i] = 1;
		map[i][0] = 1;
		map[i][n + 1] = 1;
	}
}

//打印路径（因为栈是后入先出，所以正常打印的路径是反的，我们采用正序打印数组，这样路径就正常了）

void Print()
{
	printf("寻路路径为:\n");
	//正序打印数组
	if (StackTop == -1)//空栈
	{
		printf("没有可以找到的路径\n");
	}
	else
	{
		pos tmp;
		for (int i = 0; i <= StackTop; i++)
		{
			tmp = PosStack[i];
			printf("(%d,%d)-->",tmp.row,tmp.col);
		}
		printf("(%d,%d)\n",n,n);//(n.n)设计为终点
	}
}

//寻找路径
int findRow()
{
	//每一次寻找路径有四个方向我们用一个结构体数组储存
	pos offSet[4] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };//分别表示为右，下，左，上方向走的坐标偏移量
	//设定第一次出发的起点,并且将其在地图上的数字改为1，证明走过这里
	pos begin = { 1, 1 };
	map[1][1] = 1;
	int beginPos = 0;//开始方向为向右走
	int endPos = 3;//终止方向为向上走
	//设终点坐标为(n,n)
	while (begin.row != n || begin.col != n)//没有到终点
	{
		//记录变化后的坐标，看看能不能走
		int ChangeRow = 0; int ChangeCol = 0;
		while (beginPos <= endPos)//还有方向时
		{
			ChangeRow = begin.row + offSet[beginPos].row;//原坐标+偏移值
			ChangeCol = begin.col + offSet[beginPos].col;
			if (map[ChangeRow][ChangeCol] == 0)//可以移动
			{
				break;//跳出修改begin的坐标
			}
			else
			{
				++beginPos;//找下一个坐标
			}
		}
		if (beginPos <= endPos)//找到了可以移动的位置了
		{
			++StackTop;//先把坐标入栈了再修改到下一个坐标，并且把下一个坐标的地图数据改为1(堵上)
			PosStack[StackTop] = begin;
			begin.row = ChangeRow;
			begin.col = ChangeCol;
			map[ChangeRow][ChangeCol] = 1;
			//起始方向又从0开始
			beginPos = 0;
		}
		else//出栈回退
		{
			if (StackTop == -1)//退到开头。没有路可以走
				return 0;
			else
			{
				begin = PosStack[StackTop];//回到前一个位置
				StackTop--;//出栈
				beginPos = 0;
			//之前走过的位置已经被堵上了，所以beginePos可以从0开始，但是这样之前走过的方向还要判断一次，效率下降
			}
		}
	}
	return 1;//找到路径了
}

int main()
{
	CreatMap();
	if (findRow())//找到返回1
	{
		Print();
	}
	else
	{
		printf("没有找到路径\n");
	}
	return 0;
}