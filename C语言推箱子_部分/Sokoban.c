#include"Sokoban.h"




//地图设计
/*
0->空地 1->墙壁 3->箱子目的地 4->箱子 6->人 7->箱子和目的地重合 9->人站在目的地上
*/
int map[10][12] =
{
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 4, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 4, 6, 1, 0, 1, 0, 0, 0, 3, 1 },
		{ 1, 1, 1, 4, 1, 1, 1, 0, 0, 0, 3, 1 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1 },
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
};


/*int map2[10][12]=
{
    {
	     ......
	}
}
*/


void Move(char ch)
{
	switch (ch)
	{
	case 'w':
	{
				Up(map);
				break;
	}
	case 's':
	{
				Down(map);
				break;
	}
	case'a':
	{
			   Left(map);
			   break;
	}
	case'd':
	{
			   Right(map);
			   break;
	}
	default:
		break;
	}
}

int main()
{
	InitGrap();
	while (1)
	{
		if (CoutBox(map) == 0)
		{
			leve++;
		}
		if (leve == 0)
		{
			system("cls");
			DrawMap(map);
		}
		/*if (leve == 1)
		{
		    system("cls");
		    DrawMap(map2);
		}*/
		char ch = _getch();//不需要输入回车键就可以读取数据(可以不加_)
		Move(ch);
	}

	return 0;
}