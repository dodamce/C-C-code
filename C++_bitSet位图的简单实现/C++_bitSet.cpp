#include"bitSet.h"
#include<time.h>

#define MAX_SIZE 100

void Test1()
{
	dodamce::bitSet Map(-1);
	std::vector<int> ret = { 1,2,3,4,5,6,7,8,9,10 };
	for (int i = 0; i < ret.size(); i++)
	{
		Map.Set(ret[i]);
	}
	for (int i = 0; i < ret.size(); i++)
	{
		if (Map.Find(ret[i]) == true)
		{
			std::cout << ret[i] << " ";
		}
		else
		{
			std::cout << "error" << std::endl;
		}
	}
	std::cout << std::endl;
	for (const auto& Num : ret)
	{
		Map.Reset(Num);
	}
	for (int i = 0; i < ret.size(); i++)
	{
		if (Map.Find(ret[i]) == true)
		{
			std::cout << ret[i] << " ";
		}
		else
		{
			std::cout << "* " << " ";
		}
	}
}

int main()
{
	Test1();
	return 0;
}