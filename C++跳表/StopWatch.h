#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include <random>

struct SkiplistNode {
    int val;
    std::vector<SkiplistNode*>_nextV;//节点有多少层
    SkiplistNode(int _val, int leve)
        :val(_val), _nextV(leve, nullptr)
    {}
};

class Skiplist {
    typedef SkiplistNode Node;
private:
    Node* _head;//头节点
    size_t _maxleve = 32;//每个节点最大的层数
    double _p = 0.25;//设每个节点多一层的概率为p

    int _randomLeve() {
        //产生节点的随机层数
        int leve = 1;
        while (rand() < (RAND_MAX * _p) && leve < _maxleve) {
            //rand()<(RAND_MAX*_p的概率为0.25
            leve += 1;
        }
        return leve;
    }

    //查找某个节点的所有前一个指针
    std::vector<Node*>_findPrevNode(int num) {
        //首先要查找插入的位置，前一个节点指针
        Node* cur = _head;
        int curleve = cur->_nextV.size() - 1;
        std::vector<Node*>prev(curleve + 1, _head);//保存前一个节点的指针
        while (curleve >= 0) {//如果还没有找到节点的最后一层时都要继续循环
            //节点向下移动时，更新前一个节点指针数组
            if (cur->_nextV[curleve] && cur->_nextV[curleve]->val < num) {
                //跳表向右走，跳到下一个节点
                //特殊情况，下一个节点为空时，要向跳表也要向下移动
                cur = cur->_nextV[curleve];
            }
            else if (cur->_nextV[curleve] == nullptr || cur->_nextV[curleve]->val >= num) {
                //更新prev数组，跳表向下走
                prev[curleve] = cur;
                curleve -= 1;
            }
        }
        return prev;
    }
public:
    Skiplist() {
        //头节点值为-1,开始为第一层
        _head = new Node(-1, 1);
        srand(time(0));//随机数种子
    }

    bool search(int target) {
        Node* cur = _head;
        int curleve = cur->_nextV.size() - 1;
        while (curleve >= 0) {//如果还没有找到节点的最后一层时都要继续循环
            if (cur->_nextV[curleve] && cur->_nextV[curleve]->val < target) {
                //跳表向右走，跳到下一个节点
                //特殊情况，下一个节点为空时，要向跳表也要向下移动
                cur = cur->_nextV[curleve];
            }
            else if (cur->_nextV[curleve] == nullptr || cur->_nextV[curleve]->val > target) {
                //跳表向下走
                curleve -= 1;
            }
            else {
                //找到了这个节点
                return true;
            }
        }
        return false;
    }

    void add(int num) {
        //添加数据时可以冗余
        std::vector<Node*>prev = _findPrevNode(num);
        int newLeve = _randomLeve();
        Node* newNode = new Node(num, newLeve);
        //如果newLeve超过头节点的最大层数，则选择升高head层数
        if (newLeve > _head->_nextV.size()) {
            _head->_nextV.resize(newLeve);//避免新增节点导致头节点层数不足
            prev.resize(newLeve, _head);//多余的层数指向头节点。
        }

        //连接前后节点
        for (size_t i = 0; i < newLeve; i++) {
            newNode->_nextV[i] = prev[i]->_nextV[i];
            prev[i]->_nextV[i] = newNode;
        }
    }

    //测试打印每一层跳表
    void _Print() {
        int leve = _head->_nextV.size();
        for (int i = leve - 1; i >= 0; i--) {
            Node* cur = _head;
            //打印每一层的链表
            while (cur != nullptr) {
                std::cout << cur->val << "->";
                cur = cur->_nextV[i];
            }
            std::cout << "nullptr" << std::endl;
        }
    }

    bool erase(int num) {
        //删除节点，找到到节点的前一个指针，在把要删除节点的所有下一个指针连接起来
        std::vector<Node*>prev = _findPrevNode(num);
        if (prev[0]->_nextV[0] == nullptr || prev[0]->_nextV[0]->val != num) {
            //跳表最下层都找不到这个节点，说明找不到节点
            return false;
        }
        //找到了对应节点
        Node* del = prev[0]->_nextV[0];
        for (size_t i = 0; i < del->_nextV.size(); i++) {
            //连接del节点的每一层前后指针
            prev[i]->_nextV[i] = del->_nextV[i];
        }
        delete del;

        //如果删除可以减少跳表的高度，提高搜索效率
        int _headLeve = _head->_nextV.size() - 1;
        while (_headLeve >= 0) {
            if (_head->_nextV[_headLeve] == nullptr) {
                _headLeve -= 1;
            }
            else {
                break;
            }
        }
        _head->_nextV.resize(_headLeve + 1);
        return true;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */