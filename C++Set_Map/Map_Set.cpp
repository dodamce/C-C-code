#include<iostream>
#include<map>
#include<set>
#include<string>

using namespace std;

//����ʽ����:vector deque list ->�ڴ��д洢����

//����ʽ����:map/set    /unordered_map/unordered_set ->�����ڴ��д��������
//     ƽ�����������        ��ϣ��


/*

������������Keyģ�� ->set

������������Key_Valueģ�� ->map

*/


void Test_Set1()//setģ�Ͳ���(��������������ģ��)��set��ӡ(�����������������)
{
	set<int> s;
	s.insert(10);
	s.insert(4);
	s.insert(1);
	s.insert(6);
	s.insert(2);
	s.insert(13);
	//�ײ���ƽ�������������STL�е����������൱���������,��ӡ��ͱ���������
	set<int>::iterator ptr = s.begin();
	while (ptr != s.end())
	{
		cout << *ptr << endl;
		ptr++;
	}
	//C++11��Χfor��ӡ���ײ�ʵ��Ϊ������
	cout << endl;
	for (auto& e : s)//���ü��ٿ���
	{
		cout << e << endl;
	}
}

void Test_Set2()//��֤set��ȥ�ع���
{
	//set���벻�����ظ����ظ���������ʧ��

	set<int>s;
	s.insert(19);
	s.insert(19);//ֻ�ᱣ��һ��19
	for (auto& e : s)
		cout << e << endl;
}

void Test_Set3()//setӦ�ã�����ƥ��(�������Ĳ���)
{
	set<string>WordStr;
	WordStr.insert("Hello");
	WordStr.insert("Left");
	WordStr.insert("Right");
	WordStr.insert("Map");
	WordStr.insert("Set");
	//...���뵥��
	string Word;
	cin >> Word;
	set<string>::iterator ptr = WordStr.find(Word);//����������
    //set->find()���ҳɹ������ҵ�λ�õĵ�������ʧ�ܷ������������ĩβ
	if (ptr != WordStr.end())
	{
		cout << "����ƥ��ɹ�" << endl;
	}
	else
	{
		cout << "����ƥ�����" << endl;
	}
}

void Test_Set4()//�������������(���������)�����ӡ����������
{
	set<int> s;
	s.insert(10);
	s.insert(4);
	s.insert(1);
	s.insert(6);
	s.insert(2);
	s.insert(13);
	set<int>::reverse_iterator bptr = s.rbegin();//���������
	while (bptr != s.rend())
	{
		cout << *bptr << endl;
		bptr++;
	}
}

//ע�⣺set��Ӧ������������keyģ�ͣ���������ֵ���ܱ��޸ģ���������ƻ�������������
/*
   set<int>a;
   a.insert(1);
   set<int>::iterate p=a.begin();
   *p+=1;������set�����ֵ�����޸ģ�
*/

template<class T>//��ӡsetģ�庯��
void PrintSet(const set<T>& tmp)
{
	for (const auto& e : tmp)
		cout << e << " ";
	cout << endl;
}

void Test_Set5()//set��ɾ������
{
	set<int> s;
	s.insert(10);
	s.insert(4);
	s.insert(1);
	s.insert(6);
	s.insert(2);
	s.insert(13);
	for (const auto& e : s)
		cout << e << endl;
	s.erase(10);//ֱ��ɾ��ֵ
	PrintSet(s);
	s.erase(s.find(2));//ɾ��������λ�õ�Ԫ��
	PrintSet(s);
	//ɾ��û�е���ֵ
	//s.erase(100);->û���ҵ���ִ���κβ���
	//s.erase(s.find(100));->����find�����Ҳ�������ַǷ������ڴ�����
}

void Test_Set6()
{
	set<int> s;
	s.insert(10);
	s.insert(4);
	s.insert(1);
	set<int>s2;
	s2.insert(6);
	s2.insert(2);
	s2.insert(13);
	PrintSet(s); PrintSet(s2);
	cout << endl;
	s.swap(s2);
	PrintSet(s); PrintSet(s2);
//ע����C++11ǰ���������Լ���swap��std::swap��ͬ��Ч�ʱ�std::swap��
}

//�����Ϊset���������ݲ����ظ������������Ч

//�����multiset�ṹ������set��ͬ����������������ݿ����ظ�������ֻ���ص�һ���ҵ����Ԫ�صĵ�����
//ɾ��ʱɾ��������ֵͬ��Ԫ��

template<class T>
void PrintMiltsSet(const multiset<T>& s)
{
	for (const auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

void Test_MiltisSet7()//����multiset�Ĳ���
{
	set<int>s;
	s.insert(10);
	s.insert(10);
	s.insert(20);//ֻ�ᱣ��һ��10
	PrintSet(s);
	multiset<int>s2;//�������࣬2��10
	s2.insert(10);
	s2.insert(10);
	s2.insert(20);
	PrintMiltsSet(s2);
	//����
	multiset<int>::iterator ptr = s2.find(10);
	while (*ptr == 10)//��֤multiset�������ҵ�һ����ӦԪ��,�����ӡ����10
	{
		cout << "Find:" << *ptr << endl;
		ptr++;
	}
	//cout << s2.count(10) << endl;//��ӡ��ӦԪ�صĸ���
	s.erase(10);
	PrintSet(s);
	s2.erase(10);
	PrintMiltsSet(s2);
}


int main()
{
	//Test_Set1();
	//Test_Set2();
	//Test_Set3();
	//Test_Set4();
	//Test_Set5();
	//Test_Set6();
	//Test_MiltisSet7();

	return 0;
}