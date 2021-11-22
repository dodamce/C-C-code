//C++�������ʽ��ֵ
//����(2*(9+6/3+5)+4)���ʽ��ֵ

#include<iostream>

#include<stack>

#include<string>

using namespace std;

//�������������֮������ȼ���ϵ

/*  '+' '-' '*' '\' '(' ')' '#'//���Ƕ���#Ϊ���ʽ�Ľ�β
'+'  >   >   <   <   <   >   >
'-'  >   >   <   <   <   >   >
'*'  >   >   >   >   <   >   >
'\'  >   >   >   >   <   >   >
'('  <   <   <   <   <   =
')'  >   >   >   >       >   >  
'#'  <   <   <   <   <

*/

                           //'+', '-', '*', '/', '(', ')', '#'  
char oprrelation[7][7] = { {'>', '>', '<', '<', '<', '>', '>'}, //'+'  
                          {'>', '>', '<', '<', '<', '>', '>'}, //'-'  
                          {'>', '>', '>', '>', '<', '>', '>'}, //'*'  
                          {'>', '>', '>', '>', '<', '>', '>'}, //'/'  
                          {'<', '<', '<', '<', '<', '=', ' '}, //'('  
                          {'>', '>', '>', '>', ' ', '>', '>'}, //')'  
                          {'<', '<', '<', '<', '<', ' ', '='} };//'#'  

int ConvertToIndex(char opr)//ͨ���ַ����ҵ����ǵڼ��еڼ��е������
{
    int index;

    switch (opr)
    {
    case '+':
        index = 0;
        break;
    case '-':
        index = 1;
        break;
    case '*':
        index = 2;
        break;
    case '/':
        index = 3;
        break;
    case '(':
        index = 4;
        break;
    case ')':
        index = 5;
        break;
    case '#':
        index = 6;
        break;
    }

    return index;
}

//��ȡ�����ַ������ȼ�
char Precede(const char opr1, const char opr2)
{
    int pos1 = ConvertToIndex(opr1);
    int pos2 = ConvertToIndex(opr2);
    return oprrelation[pos1][pos2];
}

int Operate(int opnd1, char op, int opnd2)//ͨ���������ַ���������
{
    int ret;

    switch (op)
    {
    case '+':
        ret = opnd1 + opnd2;
        break;
    case '-':
        ret = opnd1 - opnd2;
        break;
    case '*':
        ret = opnd1 * opnd2;
        break;
    case '/':
        ret = opnd1 / opnd2;
        break;
    }
    return ret;
}

bool IsOperator(char ch)//�ж������ֻ��ǲ�����
{
    if (ch == '+' || ch == '-' ||
        ch == '*' || ch == '/' ||
        ch == '(' || ch == ')' || ch == '#')
        return true;
    else
        return false;

}

//��ջ������������ȼ�������ȡ�������ȼ���ʱ���ȼ���ջ�����������漰�����㡣
//��������ٰ������뵽����ջ��,�������ջ�����Ǳ��ʽ�Ľ��

int Evaluation(string Str)
{
    stack<int>Num;//���ֽ�Numջ
    stack<char>Apen;//�������Apenջ
    Str += '#';//����ַ��������ı�־
    Apen.push('#');
    int Pos = 0;
    char ch = Str[Pos]; 
    while (ch != '#' || Apen.top() != '#')//�ַ���û�д������
    {
        if (!IsOperator(ch))//������
        {
            Num.push(ch - '0');
            Pos++;
            ch = Str[Pos];
        }
        else//�������
        {
            switch (Precede(Apen.top(), ch))
            {
            case '<'://ջ�����ȶȵͣ��������ջ
            {
                Apen.push(ch);
                Pos++;
                ch = Str[Pos];
                break;
            }
            case '='://��ʱֻ�����ǣ��룩������������֮��û������
                //�����ŵ��������ջ��
            {
                Apen.pop();
                Pos++;
                ch = Str[Pos];
                break;
            }
            case '>'://ջ�������ȶȵͣ�����ջ�������������
            {
                char oper = Apen.top();
                Apen.pop();
                int Num2 = Num.top();//����ջ�ĺ��ջ������ջ���ǲ������ĵڶ�������
                Num.pop();
                int Num1 = Num.top();
                Num.pop();//�������ֳ�ջ
                int ret = Operate(Num1, oper, Num2);
                //����������ջ
                Num.push(ret);
                break;
            }
            default:
                break;
            }
        }
    }
    return Num.top();
}

int main()
{
    string Str;
    int Num = 1;
    while (1)
    {
        cout << endl << Num << ":������ʽ" << endl;
        cin >> Str;
        cout << "���ʽ���Ϊ:" << Evaluation(Str) << endl;
        Num++;
    }
	return 0;
}