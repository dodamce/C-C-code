#include"Snake.h"

////���ع��
//void HideCursor()
//{
//	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
//	//��ȡ�����Ϣ
//	CONSOLE_CURSOR_INFO i;
//	SetConsoleCursorInfo(hOutPut, &i);
//	i.bVisible = FALSE;
//	SetConsoleCursorInfo(hOutPut, &i);
//}

void Welcome()
{
	//���ñ��⣬L��ʾ���ַ�
	SetConsoleTitle(L"Snake");
	//���ô��ڴ�С
	system("mode con cols=100 lines=30");
	SetPos(30, 8);
	printf("��ӭ������Ϸ");
	SetPos(35, 10);
	system("pause");//�û���ͣ�ڻ�ӭ����
	system("cls");
}

void SetPos(int x,int y)
{
	COORD pos = { x, y };
	//��ȡ����̨
	HANDLE hOutPut= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutPut, pos);
}

void DrawMap()
{
	for (int i = 0; i < 58; i+=2)//��ӡ���±߿�
	{
		SetPos(i, 0);
		printf("��");
		SetPos(i, 26);
		printf("��");
	}

	for (int i = 0; i < 26; i++)//��ӡ���ұ߿�
	{
		SetPos(0, i);
		printf("��");
		SetPos(56, i);
		printf("��");
	}

	SetPos(64, 8);//��ӡ�ɼ���Ϣ
	printf("�÷�:%d ��",score);
	SetPos(64, 10);
	printf("�ٶ�:%d Km/h",speed);
	SetPos(64, 12);
	printf("W A S D ����");
}

//�����߽ڵ�(ͷ�巨)

void CreatSnake(int X,int Y)
{
	Snake* tmp = (Snake*)malloc(sizeof(Snake));
	tmp->x = X;
	tmp->y = Y;
	tmp->next = Shead;
	Shead = tmp;
}

void PrintSnake()//��ӡ��
{
	Snake*tmp = Shead;
	while (tmp)
	{
		SetPos(tmp->x, tmp->y);
		printf("��");
		tmp = tmp->next;
	}
	SetPos(50, 29);
}


void InitSnake()//��ʼ������Ϊ4���ڵ�
{
	Shead = (Snake*)malloc(sizeof(Snake));
	Shead->x = 20;
	Shead->y = 13;
	Shead->next = NULL;
	for (int i = 1; i <= 3; i++)
	{
		CreatSnake(20 + 2 * i, 13);//���ַ�
	}
	PrintSnake();
}

void DelTail()//ɾ��β�ڵ�
{
	Snake* tmp = Shead;
	Snake* cur = NULL;
	//��β
	while (tmp->next != NULL)
	{
		cur = tmp;
		tmp = tmp->next;
	}
	//��β�ϴ�ӡ�ո�
	SetPos(tmp->x, tmp->y);
	printf("  ");
	free(tmp);
	cur->next = NULL;
}

void MoveSnake(char dir)//�ߵ��ƶ�(��ͷɾβ)
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
1.ʳ��Ҫ�ڱ߽����ڣ��������߽硣
2.ʳ�ﲻ���������ϡ�
*/
void CreatFood()
{
	srand((unsigned int)time(NULL));
	while (1)//x��2->54  y��1->24 ��x��y��Ϊż��
	{
		int X = rand() % 53 + 2;
		Sfood.x = X % 2 == 0 ? X : X - 1;
		int Y = rand() % 24 + 1;
		Sfood.y = Y % 2 == 0 ? Y : Y - 1;
		//����������
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
	printf("��");
}

//������
void EatFood(int* time)
{
	if (Sfood.x == Shead->x&&Sfood.y == Shead->y)
	{
		CreatSnake(Sfood.x,Sfood.y);
		PrintFood();
		score += 10;
		SetPos(64, 8);//��ӡ�ɼ���Ϣ
		printf("�÷�:%d ��", score);
		//����
		if (*time >= 100)
		{
			speed += 10;
			SetPos(64, 10);
			printf("�ٶ�:%d Km/h", speed);
			*time -= 10;
		}
		else
		{
			SetPos(64, 10);
			printf("�ٶ�:MAX");
		}
	}
}

//�ж�����
bool Death()
{
	//ײǽ
	if (Shead->x == 0 || Shead->x == 56 || Shead->y == 0 || Shead->y == 26)
		return true;
	//��������
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
	printf("��Ϸ����");
	SetPos(15, 15);
	printf("��ĵ÷�Ϊ:%d",score);
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
		char direction = 'd';//Ĭ�������˶�
		while (1)
		{
			//���һ����ż�������ַ�
			if (_kbhit())
			{
				direction = _getch();
			}
			MoveSnake(direction);
			if (Death())
			{
				EndGame();
				SetPos(13, 17);
				system("pause");//�û���ͣ�ڻ�ӭ����
				break;
			}
			EatFood(&time);
			Sleep(time);
		}
	}
}


int main()
{
	HideCursor();//���ع��
	StartGame();
	return 0;
}