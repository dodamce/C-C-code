#include"Sokoban.h"




//��ͼ���
/*
0->�յ� 1->ǽ�� 3->����Ŀ�ĵ� 4->���� 6->�� 7->���Ӻ�Ŀ�ĵ��غ� 9->��վ��Ŀ�ĵ���
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
		char ch = _getch();//����Ҫ����س����Ϳ��Զ�ȡ����(���Բ���_)
		Move(ch);
	}

	return 0;
}