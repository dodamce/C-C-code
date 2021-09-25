
#include"Sort.h"//(排序结果从小到大,引自己写的头文件)

void Test1()//测试冒泡选择
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Bubble_Sort(s);
	Print(s);
	vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Bubble_Sort(s2);
	Print(s2);
}

void Test2()//测试插入排序
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Insert_Sort(s);
	Print(s);
	vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Insert_Sort(s2);
	Print(s2);
}

void Test3()//测试希尔排序
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Shell_Sort(s);
	Print(s);
	vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Shell_Sort(s2);
	Print(s2);
}

void Test4()//测试选择排序
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Select_Sort(s);
	Print(s);
	vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Select_Sort(s2);
	Print(s2);
}

void Test5()//测试堆排序
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Heap_Sort(s);
	Print(s);
	/*vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Heap_Sort(s2);
	Print(s2);*/
}

void Test6()//测试快速排序
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Quick_Sort(s,0,s.size()-1);
	Print(s);
	vector<int>s2 = { 2,1,4,2,4,1,3 };
	Sort<int>::Quick_Sort_stack(s2, 0, s2.size() - 1);
	Print(s2);
}

void Test7()//测试计数排序(只支持整形排序，因为对应数组小标不能为小数)
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Count_Sort(s);
	Print(s);
	/*vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Count_Sort(s2);//小数不支持，小数排序要哈希表自定义键值，这里不设计
	Print(s2);*/
}

int main()
{
	/*Test1();
	Test2();
	Test3();*/
	//Test4();
	//Test5();
	Test6();
	//Test7();
}