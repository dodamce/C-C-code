#include"string.h"

void TestString1()
{
	My::string s1("abc");
	My::string s2("defen");
	My::string s3("");
	s3 = s2;
	My::string s4(s3);
	for (int i = 0; i < s4.Size(); i++)
	{
		cout << s4[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < s4.Size(); i++)
	{
		s4[i] += 1;
		cout << s4[i] << " ";
	}
}

void TestString2()//µü´úÆ÷±éÀú+·¶Î§for±éÀú
{
	My::string s1("abcdefg");
	My::string::iterator begin = s1.begin();
	while (begin != s1.end())
	{
		cout << *begin << " ";
		begin++;
	}
	cout << endl;
	for (auto a : s1)
	{
		cout << a << " ";
	}
}

void TestString3()//×Ö·û´®µÄÎ²²å£¬×Ö·û´®µÄÆ´½Ó
{
	My::string s1("abcd");
	s1 += "efg";
	for (auto e : s1)
	{
		cout << e << " ";
	}
	s1.push_back('x');
	cout << endl;
	for (int i = 0; i < s1.Size(); i++)
	{
		cout << s1[i] << " ";
	}
}

void TestString4()
{
	My::string s1 = "abc";
	s1.resize(6);
	cout << s1.c_str() << endl;

}

void TestString5()//×Ö·û´®µÄ±È½Ï
{
	My::string s1 = "abc";
	My::string s2 = "defch";
	int a = s1 > s2;
	s1 = s2;
	int b = s1 == s2;
	s1.push_back('x');
	int c = s1 > s2;
	printf("%d %d %d", a, b, c);
}

void TestString6()
{
	My::string s1("abcdexch");
	int pos=s1.find('x');
	cout << pos << endl;
	if (s1[pos] == 'x')
		cout << "yes";
	else
		cout << "No";
	cout << endl;
	s1.insert(1, 'M');
	cout << s1.c_str() << endl;
	s1.insert(s1.Size()-1, 'L');
	cout << s1.c_str() << endl;
}

void TestString7()
{
	My::string s1("abcde");
	s1.insert(s1.Size()-1, "HAHA");
	cout << s1.c_str() <<" "<< s1.Size()<< endl;
	s1.erase(1,8);
	cout << s1.c_str() << endl;
}

int main()
{
	//TestString1();
	//TestString2();
	//TestString3();
	//TestString4();
	//TestString5();
	//TestString6();
	TestString7();
	return 0;
}