#define _CRT_SECURE_NO_WARNINGS 1//vs2019防止报错

#define MAX_NAME 20

#define MAX_SEX 5

#define MAX_TELE 20

#define MAX_ADDRESS 20

//#define MAX 1000 //锁定通讯录大小为1000个

#define MAX_CAP 3

#include<stdio.h>

#include<windows.h>

#include<stdlib.h>

#include<string.h>

enum option
{
	Exit,
	Add,
	Delete,
	Search,
	Modify,
	Show,
	Sort,
	Save,
};

typedef struct people
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char address[MAX_ADDRESS];
}people;

typedef struct contect
{
	int sz;
	people* data;
	int capacity;
}contect;

void menu();

void initcontect(contect* p);

void Addcontect(contect* p);

void Showcontect(contect* p);

void Deletecontect(contect* p);

void menu_search();

int search_name(char name[], contect* ps);

int search_tele(char tele[], contect* ps);

int search_name2(char name[], contect* ps);

void dele_name2(int p,contect* ps); 

void Searchcontect(contect* ps);

void Modifycontect(contect* ps);

void menu_modify();

void menu_modify_option();

void Sortcontect(contect* ps);

int CmpByName(const void* e1, const void* e2);

void Deletinformation(contect*ps);

void Savecontect(contect*ps);

void CheckCapacity(contect* ps);

void LodeContact(contect* ps);