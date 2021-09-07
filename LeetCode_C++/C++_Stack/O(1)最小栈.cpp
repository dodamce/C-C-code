#include<stack>

using std::stack;

class MinStack {
public:
    /** initialize your data structure here. */

    void push(int val) {
        St.push(val);
        if (MinSt.empty() || val <= MinSt.top())
        {
            MinSt.push(val);
        }
    }

    void pop() {
        if (St.top() == MinSt.top())
        {
            MinSt.pop();
        }
        St.pop();
    }

    int top() {
        return St.top();
    }

    int getMin() {
        return MinSt.top();
    }
private:
    stack<int>St;
    stack<int>MinSt;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */