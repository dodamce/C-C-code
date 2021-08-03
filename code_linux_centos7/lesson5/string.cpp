include<iostream>
#include<string>
#include<vector>
using namespace std;


string replaceSpace(string s) {
    // write code here
    string tmp;
    string a("%20");
    int begin = 0;
    int pos = 0;
    while (s.find(' ', begin) != s.npos)
    {
        pos = s.find(' ');
        string b(s,begin,pos-begin);
        tmp += b + a;
        begin = pos+1;
        s[pos] = '*';
    }
    if (pos != s.size() - 1&&pos!=0)
    {
        string c(s, pos+1, s.npos);
        tmp += c;
    }
    return tmp;
}
int main()
{
    string s = replaceSpace("helloworld");
    cout << s;
    return 0;
}

//int main(int argc, char* argv[])
//
//{
//
//	string strText = "How are you?";
//
//	string strSeparator = " ";
//
//	string strResult;
//
//	int size_pos = 0;
//
//	int size_prev_pos = 0;
//
//	while ((size_pos = strText.find_first_of(strSeparator, size_pos)) != string::npos)
//
//	{
//
//		strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
//
//		cout << strResult << " ";
//
//		size_prev_pos = ++size_pos;
//
//	}
//
//	if (size_prev_pos != strText.size())
//
//	{
//
//		strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
//
//		cout << strResult << " ";
//
//	}
//
//	cout << endl;
//
//	return 0;
//
//}
//

//void Find(const string& s)
//{
//	string::const_iterator it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		it++;
//	}
//
//}
//
//void test1()
//{
//	string s1;
//	string s2("hello word");
//	string s3 = s2;
//	string s4(s3);
//	string s5 = "hello word";
//	string s6(s5, 3, string::npos);
//	cout << s1 << endl << s2 << endl << s3 << endl << s4 << endl << s5 << endl << s6 << endl;
//	string  s7("hello bit", 5);
//	cout << s7 << endl;
//	string s8(7, 'x');
//	cout << s8 << endl;
//	for (size_t i = 0; i < s2.size(); i++)
//	{
//		cout << s2[i] << " ";
//		cout << s2.at(i) << " ";
//	}
//	cout << endl;
//	try
//	{
//		s2.at(10);
//	}
//	catch (const std::exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	cout << endl;
//	string s10("zbdx");
//	string::iterator it = s10.begin();
//	string::iterator end = s10.end();
//	while (it != s10.end())
//	{
//		cout << *it << " ";
//		it++;
//	}
//	string::reverse_iterator rs = s10.rbegin();
//	while (rs != s10.rend())
//	{
//		cout << *rs << " ";
//		rs++;
//	}
//	cout << endl;
//	vector<int>i = { 1,2,3,4,5 };
//	vector<int>::iterator vit = i.begin();
//	while (vit != i.end())
//	{
//		cout << *vit << " ";
//		vit++;
//	}
//	cout << endl;
//
//	for (auto& e : s10)
//	{
//		e += 1;
//	}
//
//	for (auto e : s10)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//}
//
//void test2()
//{
//	string s1;
//	s1.push_back('h');
//	s1.push_back('e');
//	s1.push_back('l');
//	s1.push_back('l');
//	s1.push_back('o');
//	cout << s1 << endl;
//	s1.append(" word");
//	cout << s1 << endl;
//	string s2("!!!");
//	s1.append(s2);
//	cout << s1 << endl;
//	s1.append(s2.begin(), s2.end());
//	cout << s1;
//	string s3 = "中北大学";
//	s3 += "信息与通信工程学院\n";
//	cout << s3 << endl;
//	s3 += "1113";
//	cout << s3 << endl;
//	s3 += '6';
//	cout << s3 << endl;
//	s3 += s2;
//	cout << s3 << endl;
//	s3.insert(0, "山西省");
//	s3.insert(6, "太原市");
//	cout << s3 << endl;
//	s3.erase(0, 6);
//	cout << s3 << endl;
//	s3.erase(10);
//	cout << s3 << endl;
//	s3.erase();
//	cout << endl;
//	string s4("hello word\n");
//	cout << s4.size() << endl;
//	cout << s4.max_size() << endl;
//	s4.clear();
//	cout << s4 <<" "<< "size=" << s4.size() << endl;
//}
//
//void test3()
//{
//	string s;
//	s.resize(20, 'x');
//	cout << s << endl;
//	string s2("hello");
//	int size = s2.size();
//	s2.resize(size + 1, '!');
//	cout << s2 << endl;
//	string s3;
//	int Scap = s3.capacity();
//	for (char ch = 0; ch < 127; ch++)
//	{
//		s3 += ch;
//		if (Scap != s3.capacity())
//		{
//			printf("增容%d->%d\n",Scap,s3.capacity());
//			Scap = s3.capacity();
//		}
//	}
//	cout << s3 << endl;
//}
//
//void test4()
//{
//	string s4("hello word");
//	s4.resize(20);
//	s4 += "!!!!";
//	cout << s4 << endl;//operator(cout,s4)调用
//	cout << s4.c_str() << endl;//operator(cout,const char*)调用，遇到\0停止
//	string text = "test.cpp";
//	int pos = text.find('.');
//	if (pos != string::npos)
//	{
//		//string tmp(text, pos, string::npos);
//		//string tmp(text, pos, text.size()-pos);
//		string tmp = text.substr(pos, text.size() - pos);
//		cout << tmp << endl;
//	}
//}
//
//int main()
//{
//	//test1();
//	//test2();
//	//test3();
//	test4();
//	return 0;
//}
