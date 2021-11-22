#include<iostream>

using namespace std;

template<class T>

T fmax(T x,T y)
{
	return x>y?x:y;
}

int main()
{
	cout<<fmax(2,5)<<fmax(1.3,1.5)<<endl;
}