#include<stdio.h>

#include<stdlib.h>

#include<Windows.h>

#include<conio.h>

#include<time.h>

#include<stdbool.h>

//全局变量

 int score = 0;

 int speed = 10;

 //蛇类
 typedef struct Snake
 {
	 int x;
	 int y;
	 struct Snake*next;
 }Snake;

//食物类
typedef struct Food
 {
	 int x;
	 int y;
 }Food;

 Snake* Shead = NULL;

 Food Sfood;

//设置界面

void Welcome();

//创建地图

void DrawMap();

//设置打印光标位置

void SetPos(int x,int y);

//开始游戏

void StartGame();

//初始化蛇

void InitSnake();

//创建蛇节点(头插法)
void CreatSnake(int X, int Y);

//删除蛇尾
void DelTail();

//打印蛇
void PrintSnake();

//移动蛇
void MoveSnake(char dir);

//创建食物
void CreatFood();

//打印食物
void PrintFood();

//蛇增长
void EatFood(int* time);

//判断游戏结束
bool Death();

//结束游戏
void EndGame();

//隐藏光标
//void HideCursor();