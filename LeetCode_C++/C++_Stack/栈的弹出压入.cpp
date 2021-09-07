#include<iostream>
#include<vector>
#include<stack>

using namespace std;

class Solution {
public:
    bool IsPopOrder(vector<int> pushV, vector<int> popV) {
        stack<int>st;
        int i = 0;
        int j = 0;
        while (i < pushV.size())
        {
            st.push(pushV[i]);
            ++i;
            while (!st.empty() && st.top() == popV[j])
            {
                st.pop();
                ++j;
            }
        }
        return st.empty();
    }
};