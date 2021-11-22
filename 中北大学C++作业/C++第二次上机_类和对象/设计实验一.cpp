#include<iostream>

#include<math.h>

using namespace std;

class Square
{
public:
	Square(double lon=10)
		:Sqlong(lon)
	{}

	~Square()
	{
		cout << "~Square" << endl;
	}
	
	double GetLong() { return Sqlong; }
	double Surface()
	{
		return 6 * pow(Sqlong, 2);
	}
	double Voiume()
	{
		return pow(Sqlong, 3);
	}
protected:
	double Sqlong;
};

int main()
{
	Square s1(20);
	cout << s1.GetLong() << " " << s1.Surface() << " " << s1.Voiume() << endl;
	return 0;
}