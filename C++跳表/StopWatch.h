#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include <random>

struct SkiplistNode {
    int val;
    std::vector<SkiplistNode*>_nextV;//�ڵ��ж��ٲ�
    SkiplistNode(int _val, int leve)
        :val(_val), _nextV(leve, nullptr)
    {}
};

class Skiplist {
    typedef SkiplistNode Node;
private:
    Node* _head;//ͷ�ڵ�
    size_t _maxleve = 32;//ÿ���ڵ����Ĳ���
    double _p = 0.25;//��ÿ���ڵ��һ��ĸ���Ϊp

    int _randomLeve() {
        //�����ڵ���������
        int leve = 1;
        while (rand() < (RAND_MAX * _p) && leve < _maxleve) {
            //rand()<(RAND_MAX*_p�ĸ���Ϊ0.25
            leve += 1;
        }
        return leve;
    }

    //����ĳ���ڵ������ǰһ��ָ��
    std::vector<Node*>_findPrevNode(int num) {
        //����Ҫ���Ҳ����λ�ã�ǰһ���ڵ�ָ��
        Node* cur = _head;
        int curleve = cur->_nextV.size() - 1;
        std::vector<Node*>prev(curleve + 1, _head);//����ǰһ���ڵ��ָ��
        while (curleve >= 0) {//�����û���ҵ��ڵ�����һ��ʱ��Ҫ����ѭ��
            //�ڵ������ƶ�ʱ������ǰһ���ڵ�ָ������
            if (cur->_nextV[curleve] && cur->_nextV[curleve]->val < num) {
                //���������ߣ�������һ���ڵ�
                //�����������һ���ڵ�Ϊ��ʱ��Ҫ������ҲҪ�����ƶ�
                cur = cur->_nextV[curleve];
            }
            else if (cur->_nextV[curleve] == nullptr || cur->_nextV[curleve]->val >= num) {
                //����prev���飬����������
                prev[curleve] = cur;
                curleve -= 1;
            }
        }
        return prev;
    }
public:
    Skiplist() {
        //ͷ�ڵ�ֵΪ-1,��ʼΪ��һ��
        _head = new Node(-1, 1);
        srand(time(0));//���������
    }

    bool search(int target) {
        Node* cur = _head;
        int curleve = cur->_nextV.size() - 1;
        while (curleve >= 0) {//�����û���ҵ��ڵ�����һ��ʱ��Ҫ����ѭ��
            if (cur->_nextV[curleve] && cur->_nextV[curleve]->val < target) {
                //���������ߣ�������һ���ڵ�
                //�����������һ���ڵ�Ϊ��ʱ��Ҫ������ҲҪ�����ƶ�
                cur = cur->_nextV[curleve];
            }
            else if (cur->_nextV[curleve] == nullptr || cur->_nextV[curleve]->val > target) {
                //����������
                curleve -= 1;
            }
            else {
                //�ҵ�������ڵ�
                return true;
            }
        }
        return false;
    }

    void add(int num) {
        //�������ʱ��������
        std::vector<Node*>prev = _findPrevNode(num);
        int newLeve = _randomLeve();
        Node* newNode = new Node(num, newLeve);
        //���newLeve����ͷ�ڵ������������ѡ������head����
        if (newLeve > _head->_nextV.size()) {
            _head->_nextV.resize(newLeve);//���������ڵ㵼��ͷ�ڵ��������
            prev.resize(newLeve, _head);//����Ĳ���ָ��ͷ�ڵ㡣
        }

        //����ǰ��ڵ�
        for (size_t i = 0; i < newLeve; i++) {
            newNode->_nextV[i] = prev[i]->_nextV[i];
            prev[i]->_nextV[i] = newNode;
        }
    }

    //���Դ�ӡÿһ������
    void _Print() {
        int leve = _head->_nextV.size();
        for (int i = leve - 1; i >= 0; i--) {
            Node* cur = _head;
            //��ӡÿһ�������
            while (cur != nullptr) {
                std::cout << cur->val << "->";
                cur = cur->_nextV[i];
            }
            std::cout << "nullptr" << std::endl;
        }
    }

    bool erase(int num) {
        //ɾ���ڵ㣬�ҵ����ڵ��ǰһ��ָ�룬�ڰ�Ҫɾ���ڵ��������һ��ָ����������
        std::vector<Node*>prev = _findPrevNode(num);
        if (prev[0]->_nextV[0] == nullptr || prev[0]->_nextV[0]->val != num) {
            //�������²㶼�Ҳ�������ڵ㣬˵���Ҳ����ڵ�
            return false;
        }
        //�ҵ��˶�Ӧ�ڵ�
        Node* del = prev[0]->_nextV[0];
        for (size_t i = 0; i < del->_nextV.size(); i++) {
            //����del�ڵ��ÿһ��ǰ��ָ��
            prev[i]->_nextV[i] = del->_nextV[i];
        }
        delete del;

        //���ɾ�����Լ�������ĸ߶ȣ��������Ч��
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