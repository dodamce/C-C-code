#include<iostream>

using namespace std;

class point
{
public:
	point(int X,int Y)
		:x(X),y(Y)
	{}
	~point()
	{
		cout<<x<<","<<y<<endl;
	}
private:
	int x;
	int y;
};

int main()
{
	point x(11,15);
	return 0;
}