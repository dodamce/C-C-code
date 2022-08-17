#pragma once
#include<iostream>

template<class K, size_t M>
struct BTreeNode {
	//多开辟一个空间方便插入
	K _keys[M];
	BTreeNode<K, M>* _subs[M + 1];
	BTreeNode<K, M>* _parent;//这个节点的父节点
	size_t _n;//记录实际存储关键字个数
	BTreeNode() {
		for (size_t i = 0; i < M; i++) {
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		_subs[M] = nullptr;
		_n = 0;
		_parent = nullptr;
	}
};

//数据如果存在磁盘上，K是磁盘地址
template<class K, size_t M>
class BTree {
	typedef BTreeNode<K, M> Node;
public:
	//查找要插入的叶子节点对应的下标
	std::pair<Node*, int>Find(const K& key) {
		Node* par = nullptr;
		Node* cur = _root;
		while (cur) {
			//在一个节点中查找
			size_t i = 0;
			while (i < cur->_n) {
				if (key < cur->_keys[i]) {
					//_key[size]的左孩子
					break;
				}
				else if (key > cur->_keys[i]) {
					i++;
				}
				else {
					return std::make_pair(cur, i);
				}
			}
			par = cur;//记录cur的父节点
			cur = cur->_subs[i];
		}
		return std::make_pair(par, -1);
	}
	bool Insert(const K& key) {
		if (_root == nullptr) {
			_root = new Node;
			_root->_keys[0] = key;
			_root->_n++;
			return true;
		}
		std::pair<Node*,int> ret = Find(key);
		if (ret.second >= 0) {
			//不允许冗余
			return false;
		}
		//如果没有找到，Find函数返回要插入的叶子节点
		Node* cur = ret.first;
		K newKey = key;
		Node* child = nullptr;
		while (true) {
			InsertKey(cur, newKey, child);
			if (cur->_n == M) {
				//这个节点满了，需要分裂
				size_t mid = M / 2;
				//node中有[mid+1,M-1]的数据
				Node* node = new Node;
				size_t pos = 0;
				//同时还要拷贝孩子节点
				for (int i = mid + 1; i < M; i++) {
					node->_keys[pos] = cur->_keys[i];
					node->_subs[pos] = cur->_subs[i];
					if (cur->_subs[i] != nullptr) {
						//更新父节点
						cur->_subs[i]->_parent = node;
					}
					pos++;
					cur->_keys[i] = K();//方便观察
					cur->_subs[i] = nullptr;
				}
				//最后一个子节点拷贝
				node->_subs[pos] = cur->_subs[M];
				if (cur->_subs[M] != nullptr) {
					//更新父节点
					cur->_subs[M]->_parent = node;
				}
				cur->_subs[M] = nullptr;
				node->_n = pos;
				cur->_n -= pos + 1;//还要提取一个节点作为这两个节点的父节点

				K midKey = cur->_keys[mid];
				cur->_keys[mid] = K();//方便调试观察

				//向cur->parent插入cur->_keys[mid]和node节点
				if (cur->_parent == nullptr) {
					//分裂根节点
					_root = new Node;
					_root->_keys[0] = midKey;
					_root->_subs[0] = cur;
					_root->_subs[1] = node;
					_root->_n = 1;
					cur->_parent = _root;
					node->_parent = _root;
					break;
				}
				newKey = midKey;
				child = node; 
				cur = cur->_parent;//while循环插入
			}
			else {
				//节点没有满，插入结束
				return true;
			}
		}
		return true;
	}

	//中序遍历
	void Inorder() {
		_Inorder(_root);
	}
private:
	void _Inorder(Node* root) {
		if (root == nullptr) {
			return;
		}
		for (size_t i = 0; i < root->_n; i++) {
			_Inorder(root->_subs[i]);
			std::cout << root->_keys[i] << " ";
		}
		//最后还剩余一个右子树
		_Inorder(root->_subs[root->_n]);
	}

	void InsertKey(Node* cur, const K& key, Node* child) {
		int endPos = cur->_n - 1;
		while (endPos >= 0) {
			if (key < cur->_keys[endPos]) {
				//挪动key和右孩子
				cur->_keys[endPos + 1] = cur->_keys[endPos];
				cur->_subs[endPos + 2] = cur->_subs[endPos + 1];
				endPos -= 1;
			}
			else {
				break;
			}
		}
		cur->_keys[endPos + 1] = key;
		cur->_subs[endPos + 2] = child;
		if (child != nullptr) {
			child->_parent = cur;
		}
		cur->_n += 1;
	}
	Node* _root = nullptr;
};