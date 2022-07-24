#include<iostream>
#include<unordered_map>
#include<list>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        auto pos = _lruHash.find(key);
        if (pos != _lruHash.end()) {
            //Cache���У����������� ����key��Ӧ�Ľڵ��λ��
            list<pair<int, int>>::iterator ptr = pos->second;
            //ת�ƽڵ�⺯��std::list::splice
            //void splice (iterator position, list& x, iterator i);
            //Transfers elements from x into the container, inserting them at position.
            //��x�ĵ�i���ڵ�ת�ƴ�positionλ����
            _lruCacheList.splice(_lruCacheList.begin(), _lruCacheList, ptr);
            return pos->second->second;
        }
        return -1;
    }

    void put(int key, int value) {
        auto pos = _lruHash.find(key);
        if (pos != _lruHash.end()) {
            //����Cache�����¶�Ӧ�ڵ��λ��
            list<pair<int, int>>::iterator ptr = pos->second;
            ptr->second = value;//��������
            _lruCacheList.splice(_lruCacheList.begin(), _lruCacheList, ptr);//ת�ƽڵ�
        }
        else {
            //����Cache
            if (capacity == _lruHash.size()) {
                //���ˣ��滻ɾ��β�ϵ�����
                pair<int, int>& back = _lruCacheList.back();
                _lruHash.erase(back.first);
                _lruCacheList.pop_back();
            }
            _lruCacheList.push_front(make_pair(key, value));
            _lruHash[key] = _lruCacheList.begin();
        }
    }
private:
    unordered_map<int, list<pair<int, int>>::iterator>_lruHash;//�������
    list<pair<int, int>>_lruCacheList;//��������
    size_t capacity;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */