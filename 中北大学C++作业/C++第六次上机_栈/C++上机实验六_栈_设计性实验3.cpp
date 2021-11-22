//C++函数表达式求值
//计算(2*(9+6/3+5)+4)表达式的值

#include<iostream>

#include<stack>

#include<string>

using namespace std;

//定义两个运算符之间的优先级关系

/*  '+' '-' '*' '\' '(' ')' '#'//我们定义#为表达式的结尾
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

int ConvertToIndex(char opr)//通过字符来找到其是第几行第几列的运算符
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

//获取两个字符的优先级
char Precede(const char opr1, const char opr2)
{
    int pos1 = ConvertToIndex(opr1);
    int pos2 = ConvertToIndex(opr2);
    return oprrelation[pos1][pos2];
}

int Operate(int opnd1, char op, int opnd2)//通过传来的字符计算数字
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

bool IsOperator(char ch)//判断是数字还是操作符
{
    if (ch == '+' || ch == '-' ||
        ch == '*' || ch == '/' ||
        ch == '(' || ch == ')' || ch == '#')
        return true;
    else
        return false;

}

//当栈顶的运算符优先级比我们取到的优先级低时，先计算栈顶这个运算符涉及的运算。
//计算完后再把它插入到数字栈中,最后数字栈顶就是表达式的结果

int Evaluation(string Str)
{
    stack<int>Num;//数字进Num栈
    stack<char>Apen;//运算符进Apen栈
    Str += '#';//添加字符串结束的标志
    Apen.push('#');
    int Pos = 0;
    char ch = Str[Pos]; 
    while (ch != '#' || Apen.top() != '#')//字符串没有处理完毕
    {
        if (!IsOperator(ch))//是数字
        {
            Num.push(ch - '0');
            Pos++;
            ch = Str[Pos];
        }
        else//是运算符
        {
            switch (Precede(Apen.top(), ch))
            {
            case '<'://栈顶优先度低，运算符进栈
            {
                Apen.push(ch);
                Pos++;
                ch = Str[Pos];
                break;
            }
            case '='://此时只可能是（与）相遇，且括号之间没有数字
                //把括号弹出运算符栈中
            {
                Apen.pop();
                Pos++;
                ch = Str[Pos];
                break;
            }
            case '>'://栈顶的优先度低，处理栈顶运算符的运算
            {
                char oper = Apen.top();
                Apen.pop();
                int Num2 = Num.top();//先入栈的后出栈，所以栈顶是操作符的第二个数字
                Num.pop();
                int Num1 = Num.top();
                Num.pop();//两个数字出栈
                int ret = Operate(Num1, oper, Num2);
                //讲计算结果入栈
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
        cout << endl << Num << ":输入表达式" << endl;
        cin >> Str;
        cout << "表达式结果为:" << Evaluation(Str) << endl;
        Num++;
    }
	return 0;
}