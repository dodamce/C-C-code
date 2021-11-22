#include<iostream>

using namespace std;



int main()
{
	char ch1,ch2;
	char str1[80];
	char str2[80];
	ch1=cin.get();
	cin.get(ch2);
	cout<<"Êä³ö"<<endl;
	cout<<ch1<<ch2<<endl;
	cin.ignore(1024,'\n');
	cin.get(str1,30);
	cout<<str1<<endl;
	cin.sync();
	cin.getline(str2,30);
	cout<<str2<<endl;
	return 0;
}
