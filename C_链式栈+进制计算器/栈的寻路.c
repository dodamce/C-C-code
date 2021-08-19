#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>

//����1��ʾΪǽ���Ѿ��߹���λ�ã�0��ʾ�����ߵ�λ��.��ͼ���Ǹ���ά����

typedef struct pos //�˶�λ��(����)
{
	int row;
	int col;
}pos;

pos PosStack[100];//���ÿ��Ѱ·�����꣨����ջ��

int StackTop = -1;//ջ�����

//�����Թ�

int** CreatArray(int row, int col)
{
	int** map = (int**)malloc(sizeof(int*)*row);//row�У�ÿ�з�col��int����
	for (int i = 0; i < row; i++)
	{
		map[i] = (int*)malloc(sizeof(int)*col);//ÿ����col��int
	}
	return map;
}

int**map;//ȫ�ֱ������ͼ
int n;//��ͼ��С

void CreatMap()
{
	printf("�����Թ���С\n");
	scanf("%d",&n);
	map = CreatArray(n + 2, n + 2);//����ǰ��߿�
	//�����Թ����û����룬���ﲻ������������ɣ�
	printf("�����Թ��ṹ\n");
	//���˱߿�����forѭ����1��ʼ
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
	//�ӱ߿�
	for (int i = 0; i < n + 2; i++)
	{
		map[0][i] = 1;
		map[n + 1][i] = 1;
		map[i][0] = 1;
		map[i][n + 1] = 1;
	}
}

//��ӡ·������Ϊջ�Ǻ����ȳ�������������ӡ��·���Ƿ��ģ����ǲ��������ӡ���飬����·���������ˣ�

void Print()
{
	printf("Ѱ··��Ϊ:\n");
	//�����ӡ����
	if (StackTop == -1)//��ջ
	{
		printf("û�п����ҵ���·��\n");
	}
	else
	{
		pos tmp;
		for (int i = 0; i <= StackTop; i++)
		{
			tmp = PosStack[i];
			printf("(%d,%d)-->",tmp.row,tmp.col);
		}
		printf("(%d,%d)\n",n,n);//(n.n)���Ϊ�յ�
	}
}

//Ѱ��·��
int findRow()
{
	//ÿһ��Ѱ��·�����ĸ�����������һ���ṹ�����鴢��
	pos offSet[4] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };//�ֱ��ʾΪ�ң��£����Ϸ����ߵ�����ƫ����
	//�趨��һ�γ��������,���ҽ����ڵ�ͼ�ϵ����ָ�Ϊ1��֤���߹�����
	pos begin = { 1, 1 };
	map[1][1] = 1;
	int beginPos = 0;//��ʼ����Ϊ������
	int endPos = 3;//��ֹ����Ϊ������
	//���յ�����Ϊ(n,n)
	while (begin.row != n || begin.col != n)//û�е��յ�
	{
		//��¼�仯������꣬�����ܲ�����
		int ChangeRow = 0; int ChangeCol = 0;
		while (beginPos <= endPos)//���з���ʱ
		{
			ChangeRow = begin.row + offSet[beginPos].row;//ԭ����+ƫ��ֵ
			ChangeCol = begin.col + offSet[beginPos].col;
			if (map[ChangeRow][ChangeCol] == 0)//�����ƶ�
			{
				break;//�����޸�begin������
			}
			else
			{
				++beginPos;//����һ������
			}
		}
		if (beginPos <= endPos)//�ҵ��˿����ƶ���λ����
		{
			++StackTop;//�Ȱ�������ջ�����޸ĵ���һ�����꣬���Ұ���һ������ĵ�ͼ���ݸ�Ϊ1(����)
			PosStack[StackTop] = begin;
			begin.row = ChangeRow;
			begin.col = ChangeCol;
			map[ChangeRow][ChangeCol] = 1;
			//��ʼ�����ִ�0��ʼ
			beginPos = 0;
		}
		else//��ջ����
		{
			if (StackTop == -1)//�˵���ͷ��û��·������
				return 0;
			else
			{
				begin = PosStack[StackTop];//�ص�ǰһ��λ��
				StackTop--;//��ջ
				beginPos = 0;
			//֮ǰ�߹���λ���Ѿ��������ˣ�����beginePos���Դ�0��ʼ����������֮ǰ�߹��ķ���Ҫ�ж�һ�Σ�Ч���½�
			}
		}
	}
	return 1;//�ҵ�·����
}

int main()
{
	CreatMap();
	if (findRow())//�ҵ�����1
	{
		Print();
	}
	else
	{
		printf("û���ҵ�·��\n");
	}
	return 0;
}