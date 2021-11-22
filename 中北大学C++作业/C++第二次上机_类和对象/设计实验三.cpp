#include<iostream>

using namespace std;

class Student
{
public:
	Student(int ID,const char*name,int score=60)
		:_ID(ID),_score(score)
	{
		strcmp(_name, name);
	}

	int GetScore() { return _score; }
	int GetID() { return _ID; }
	static int _ClassNumber;
private:
	int _score;
	const int _ID;
	char _name[10];
};
int Student::_ClassNumber = 3;

double Average(Student(&Class)[3])//数组的引用
{
	int sum = 0;
	for (int i = 0; i < Student::_ClassNumber; i++)
	{
		sum += Class[i].GetScore();
	}
	return 1.0*sum / (Student::_ClassNumber);
}

int main()
{
	Student Class[3] = { {31,"小明",75},{13,"小红",89},{26,"小刚",65} };
	double ave= Average(Class);
	cout << ave << endl;
	return 0;
}