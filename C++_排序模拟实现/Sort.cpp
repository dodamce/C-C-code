
#include"Sort.h"//(��������С����,���Լ�д��ͷ�ļ�)

void Test1()//����ð��ѡ��
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Bubble_Sort(s);
	Print(s);
	vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Bubble_Sort(s2);
	Print(s2);
}

void Test2()//���Բ�������
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Insert_Sort(s);
	Print(s);
	vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Insert_Sort(s2);
	Print(s2);
}

void Test3()//����ϣ������
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Shell_Sort(s);
	Print(s);
	vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Shell_Sort(s2);
	Print(s2);
}

void Test4()//����ѡ������
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Select_Sort(s);
	Print(s);
	vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Select_Sort(s2);
	Print(s2);
}

void Test5()//���Զ�����
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Heap_Sort(s);
	Print(s);
	/*vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Heap_Sort(s2);
	Print(s2);*/
}

void Test6()//���Կ�������
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Quick_Sort(s,0,s.size()-1);
	Print(s);
	vector<int>s2 = { 2,1,4,2,4,1,3 };
	Sort<int>::Quick_Sort_stack(s2, 0, s2.size() - 1);
	Print(s2);
}

void Test7()//���Լ�������(ֻ֧������������Ϊ��Ӧ����С�겻��ΪС��)
{
	vector<int>s = { 2,1,4,2,4,1,3 };
	Sort<int>::Count_Sort(s);
	Print(s);
	/*vector<float>s2 = { 1.1,3.2,5.3,1.8 };
	Sort<float>::Count_Sort(s2);//С����֧�֣�С������Ҫ��ϣ���Զ����ֵ�����ﲻ���
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