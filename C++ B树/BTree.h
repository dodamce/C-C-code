#pragma once
#include<iostream>

template<class K, size_t M>
struct BTreeNode {
	//�࿪��һ���ռ䷽�����
	K _keys[M];
	BTreeNode<K, M>* _subs[M + 1];
	BTreeNode<K, M>* _parent;//����ڵ�ĸ��ڵ�
	size_t _n;//��¼ʵ�ʴ洢�ؼ��ָ���
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

//����������ڴ����ϣ�K�Ǵ��̵�ַ
template<class K, size_t M>
class BTree {
	typedef BTreeNode<K, M> Node;
public:
	//����Ҫ�����Ҷ�ӽڵ��Ӧ���±�
	std::pair<Node*, int>Find(const K& key) {
		Node* par = nullptr;
		Node* cur = _root;
		while (cur) {
			//��һ���ڵ��в���
			size_t i = 0;
			while (i < cur->_n) {
				if (key < cur->_keys[i]) {
					//_key[size]������
					break;
				}
				else if (key > cur->_keys[i]) {
					i++;
				}
				else {
					return std::make_pair(cur, i);
				}
			}
			par = cur;//��¼cur�ĸ��ڵ�
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
			//����������
			return false;
		}
		//���û���ҵ���Find��������Ҫ�����Ҷ�ӽڵ�
		Node* cur = ret.first;
		K newKey = key;
		Node* child = nullptr;
		while (true) {
			InsertKey(cur, newKey, child);
			if (cur->_n == M) {
				//����ڵ����ˣ���Ҫ����
				size_t mid = M / 2;
				//node����[mid+1,M-1]������
				Node* node = new Node;
				size_t pos = 0;
				//ͬʱ��Ҫ�������ӽڵ�
				for (int i = mid + 1; i < M; i++) {
					node->_keys[pos] = cur->_keys[i];
					node->_subs[pos] = cur->_subs[i];
					if (cur->_subs[i] != nullptr) {
						//���¸��ڵ�
						cur->_subs[i]->_parent = node;
					}
					pos++;
					cur->_keys[i] = K();//����۲�
					cur->_subs[i] = nullptr;
				}
				//���һ���ӽڵ㿽��
				node->_subs[pos] = cur->_subs[M];
				if (cur->_subs[M] != nullptr) {
					//���¸��ڵ�
					cur->_subs[M]->_parent = node;
				}
				cur->_subs[M] = nullptr;
				node->_n = pos;
				cur->_n -= pos + 1;//��Ҫ��ȡһ���ڵ���Ϊ�������ڵ�ĸ��ڵ�

				K midKey = cur->_keys[mid];
				cur->_keys[mid] = K();//������Թ۲�

				//��cur->parent����cur->_keys[mid]��node�ڵ�
				if (cur->_parent == nullptr) {
					//���Ѹ��ڵ�
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
				cur = cur->_parent;//whileѭ������
			}
			else {
				//�ڵ�û�������������
				return true;
			}
		}
		return true;
	}

	//�������
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
		//���ʣ��һ��������
		_Inorder(root->_subs[root->_n]);
	}

	void InsertKey(Node* cur, const K& key, Node* child) {
		int endPos = cur->_n - 1;
		while (endPos >= 0) {
			if (key < cur->_keys[endPos]) {
				//Ų��key���Һ���
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