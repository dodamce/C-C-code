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
            //Cache命中，调整计数器 更新key对应的节点的位置
            list<pair<int, int>>::iterator ptr = pos->second;
            //转移节点库函数std::list::splice
            //void splice (iterator position, list& x, iterator i);
            //Transfers elements from x into the container, inserting them at position.
            //将x的第i个节点转移带position位置上
            _lruCacheList.splice(_lruCacheList.begin(), _lruCacheList, ptr);
            return pos->second->second;
        }
        return -1;
    }

    void put(int key, int value) {
        auto pos = _lruHash.find(key);
        if (pos != _lruHash.end()) {
            //更新Cache，更新对应节点的位置
            list<pair<int, int>>::iterator ptr = pos->second;
            ptr->second = value;//更新数据
            _lruCacheList.splice(_lruCacheList.begin(), _lruCacheList, ptr);//转移节点
        }
        else {
            //新增Cache
            if (capacity == _lruHash.size()) {
                //满了，替换删除尾上的数据
                pair<int, int>& back = _lruCacheList.back();
                _lruHash.erase(back.first);
                _lruCacheList.pop_back();
            }
            _lruCacheList.push_front(make_pair(key, value));
            _lruHash[key] = _lruCacheList.begin();
        }
    }
private:
    unordered_map<int, list<pair<int, int>>::iterator>_lruHash;//方便查找
    list<pair<int, int>>_lruCacheList;//保存数据
    size_t capacity;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */