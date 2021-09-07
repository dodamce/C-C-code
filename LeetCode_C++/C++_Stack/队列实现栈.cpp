#include<iostream>
#include<stack>
#include<vector>
#include<string>
#include<queue>

using namespace std;

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        if (s1.empty())
        {
            s2.push(x);
        }
        else
        {
            s1.push(x);
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int tmp = 0;
        if (s1.empty())
        {
            int size = s2.size() - 1;
            for (int i = 0; i < size; i++)
            {
                s1.push(s2.front());
                s2.pop();
            }
            tmp = s2.front();
            s2.pop();
        }
        else
        {
            int size = s1.size() - 1;
            for (int i = 0; i < size; i++)
            {
                s2.push(s1.front());
                s1.pop();
            }
            tmp = s1.front();
            s1.pop();
        }
        return tmp;
    }

    /** Get the top element. */
    int top() {
        int tmp = 0;
        if (s1.empty())
        {
            int size = s2.size() - 1;
            for (int i = 0; i < size; i++)
            {
                s1.push(s2.front());
                s2.pop();
            }
            tmp = s2.front();
            s1.push(s2.front());
            s2.pop();
        }
        else
        {
            int size = s1.size() - 1;
            for (int i = 0; i < size; i++)
            {
                s2.push(s1.front());
                s1.pop();
            }
            tmp = s1.front();
            s2.push(s1.front());
            s1.pop();
        }
        return tmp;
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return s1.empty() && s2.empty();
    }
private:
    queue<int>s1;
    queue<int>s2;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */