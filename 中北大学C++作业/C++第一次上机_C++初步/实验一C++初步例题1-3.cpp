#include<iostream>

using namespace std;

int main()
{
	int a=31;
	cout.width(8);
	cout.fill('*');
	cout.unsetf(ios::dec);
	cout.setf(ios::hex);
	cout<<a<<endl;
	cout.unsetf(ios::hex);
	float f=2.0/3.0,f1=0.00000001,f2=-9.9;
	cout<<f<<','<<f1<<','<<f2<<endl;
	cout.setf(ios::showpoint);
	cout<<f<<','<<f1<<','<<f2<<endl;
	cout.unsetf(ios::showpoint);
	cout.setf(ios::scientific);
	cout<<f<<','<<f1<<','<<f2<<endl;
	cout.unsetf(ios::scientific);
	cout.setf(ios::fixed);
	cout<<f<<','<<f1<<','<<f2<<endl;
	cout.unsetf(ios::fixed);
	cout.precision(2);
	cout<<f<<','<<f1<<','<<f2<<endl;
	getchar();
	return 0;
}