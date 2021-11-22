#include<iostream>

using namespace std;

int fadd(int i,int j)
{
	return i+j;
}

double fadd(double i,double j)
{
	return i+j;
}

int fadd(int i,int j,int k)
{
	return i+fadd(j,k);
}


int main()
{
	int a=1;
	int b(2),c(3),e,f;
	double x=3.5,y=4.5,z;
	e=fadd(a,b);
	f=fadd(a,b,c);
	z=fadd(x,y);
	cout<<e<<" "<<f<<" "<<z<<endl;
	getchar();
}