#include<stdio.h>

#include<stdlib.h>

#include<Windows.h>

#include<conio.h>

#include<time.h>

#include<stdbool.h>

//ȫ�ֱ���

 int score = 0;

 int speed = 10;

 //����
 typedef struct Snake
 {
	 int x;
	 int y;
	 struct Snake*next;
 }Snake;

//ʳ����
typedef struct Food
 {
	 int x;
	 int y;
 }Food;

 Snake* Shead = NULL;

 Food Sfood;

//���ý���

void Welcome();

//������ͼ

void DrawMap();

//���ô�ӡ���λ��

void SetPos(int x,int y);

//��ʼ��Ϸ

void StartGame();

//��ʼ����

void InitSnake();

//�����߽ڵ�(ͷ�巨)
void CreatSnake(int X, int Y);

//ɾ����β
void DelTail();

//��ӡ��
void PrintSnake();

//�ƶ���
void MoveSnake(char dir);

//����ʳ��
void CreatFood();

//��ӡʳ��
void PrintFood();

//������
void EatFood(int* time);

//�ж���Ϸ����
bool Death();

//������Ϸ
void EndGame();

//���ع��
//void HideCursor();