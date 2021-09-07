#include<iostream>
#include<stack>
#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    void GetStack(stack<int>& st, int& left, int& right)
    {
        right = st.top();
        st.pop();
        left = st.top();
        st.pop();
    }
    int evalRPN(vector<string>& tokens) {
        stack<int>st;
        for (const auto& str : tokens)
        {
            int left = 0; int right = 0;
            switch (str[str.size() - 1])
            {
            case '+':
                GetStack(st, left, right);
                st.push(left + right);
                break;
            case'-':
                GetStack(st, left, right);
                st.push(left - right);
                break;
            case '*':
                GetStack(st, left, right);
                st.push(left * right);
                break;
            case '/':
                GetStack(st, left, right);
                st.push(left / right);
                break;
            default:
                st.push(stoi(str));
                break;
            }
        }
        return st.top();
    }
};