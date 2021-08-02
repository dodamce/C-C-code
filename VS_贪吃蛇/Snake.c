#include"Snake.h"

////隐藏光标
//void HideCursor()
//{
//	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
//	//获取光标信息
//	CONSOLE_CURSOR_INFO i;
//	SetConsoleCursorInfo(hOutPut, &i);
//	i.bVisible = FALSE;
//	SetConsoleCursorInfo(hOutPut, &i);
//}

void Welcome()
{
	//设置标题，L表示宽字符
	SetConsoleTitle(L"Snake");
	//设置窗口大小
	system("mode con cols=100 lines=30");
	SetPos(30, 8);
	printf("欢迎进入游戏");
	SetPos(35, 10);
	system("pause");//让画面停在欢迎界面
	system("cls");
}

void SetPos(int x,int y)
{
	COORD pos = { x, y };
	//获取控制台
	HANDLE hOutPut= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutPut, pos);
}

void DrawMap()
{
	for (int i = 0; i < 58; i+=2)//打印上下边框
	{
		SetPos(i, 0);
		printf("■");
		SetPos(i, 26);
		printf("■");
	}

	for (int i = 0; i < 26; i++)//打印左右边框
	{
		SetPos(0, i);
		printf("■");
		SetPos(56, i);
		printf("■");
	}

	SetPos(64, 8);//打印成绩信息
	printf("得分:%d 分",score);
	SetPos(64, 10);
	printf("速度:%d Km/h",speed);
	SetPos(64, 12);
	printf("W A S D 操作");
}

//创建蛇节点(头插法)

void CreatSnake(int X,int Y)
{
	Snake* tmp = (Snake*)malloc(sizeof(Snake));
	tmp->x = X;
	tmp->y = Y;
	tmp->next = Shead;
	Shead = tmp;
}

void PrintSnake()//打印蛇
{
	Snake*tmp = Shead;
	while (tmp)
	{
		SetPos(tmp->x, tmp->y);
		printf("■");
		tmp = tmp->next;
	}
	SetPos(50, 29);
}


void InitSnake()//初始化蛇设为4个节点
{
	Shead = (Snake*)malloc(sizeof(Snake));
	Shead->x = 20;
	Shead->y = 13;
	Shead->next = NULL;
	for (int i = 1; i <= 3; i++)
	{
		CreatSnake(20 + 2 * i, 13);//宽字符
	}
	PrintSnake();
}

void DelTail()//删除尾节点
{
	Snake* tmp = Shead;
	Snake* cur = NULL;
	//找尾
	while (tmp->next != NULL)
	{
		cur = tmp;
		tmp = tmp->next;
	}
	//在尾上打印空格
	SetPos(tmp->x, tmp->y);
	printf("  ");
	free(tmp);
	cur->next = NULL;
}

void MoveSnake(char dir)//蛇的移动(增头删尾)
{
	switch (dir)
	{
	case 'd':case 'D':
		CreatSnake(Shead->x + 2, Shead->y);
		break;
	case 'a':case 'A':
		CreatSnake(Shead->x - 2, Shead->y);
		break;
	case'w':case'W':
		CreatSnake(Shead->x, Shead->y - 1);
		break;
	case's':case'S':
		CreatSnake(Shead->x, Shead->y + 1);
	default:
		break;
	}
	DelTail();
	PrintSnake();
}

/*
1.食物要在边界以内，不包括边界。
2.食物不能在蛇身上。
*/
void CreatFood()
{
	srand((unsigned int)time(NULL));
	while (1)//x在2->54  y在1->24 且x，y都为偶数
	{
		int X = rand() % 53 + 2;
		Sfood.x = X % 2 == 0 ? X : X - 1;
		int Y = rand() % 24 + 1;
		Sfood.y = Y % 2 == 0 ? Y : Y - 1;
		//不在蛇身上
		Snake* tmp = Shead;
		while (tmp&&Sfood.y != 0 && Sfood.x != 0)
		{
			if (tmp->x == Sfood.x&&tmp->y == Sfood.y)
			{
				break;
			}
			tmp = tmp->next;
		}
		if (tmp == NULL)
		{
			break;
		}
	}

}

void PrintFood()
{
	CreatFood();
	SetPos(Sfood.x, Sfood.y);
	printf("●");
}

//蛇增长
void EatFood(int* time)
{
	if (Sfood.x == Shead->x&&Sfood.y == Shead->y)
	{
		CreatSnake(Sfood.x,Sfood.y);
		PrintFood();
		score += 10;
		SetPos(64, 8);//打印成绩信息
		printf("得分:%d 分", score);
		//加速
		if (*time >= 100)
		{
			speed += 10;
			SetPos(64, 10);
			printf("速度:%d Km/h", speed);
			*time -= 10;
		}
		else
		{
			SetPos(64, 10);
			printf("速度:MAX");
		}
	}
}

//判断死亡
bool Death()
{
	//撞墙
	if (Shead->x == 0 || Shead->x == 56 || Shead->y == 0 || Shead->y == 26)
		return true;
	//碰到蛇身
	struct Snake* fast = Shead->next;
	while (fast!=NULL)
	{
		if (fast->x == Shead->x&&fast->y == Shead->y)
		{
			return true;
		}
		fast = fast->next;
	}
	return false;
}

void EndGame()
{
	SetPos(20, 13);
	printf("游戏结束");
	SetPos(15, 15);
	printf("你的得分为:%d",score);
}

void StartGame()
{
	while (1)
	{

		int time = 510;
		score = 0;
		speed = 10;
		Welcome();
		DrawMap();
		InitSnake();
		PrintFood();
		char direction = 'd';//默认向右运动
		while (1)
		{
			//如果一输入才检测输入字符
			if (_kbhit())
			{
				direction = _getch();
			}
			MoveSnake(direction);
			if (Death())
			{
				EndGame();
				SetPos(13, 17);
				system("pause");//让画面停在欢迎界面
				break;
			}
			EatFood(&time);
			Sleep(time);
		}
	}
}


int main()
{
	HideCursor();//隐藏光标
	StartGame();
	return 0;
}