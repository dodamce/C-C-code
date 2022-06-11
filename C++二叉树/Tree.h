#pragma once

#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<exception>
#include<memory>
#include<stack>

struct TreeNode
{
	int val;
	TreeNode*left;
	TreeNode*right;
	TreeNode*parent;
	bool flag = false;
	TreeNode(int _val){
		val = _val;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	TreeNode(){
		val = -1;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};


class TreeError :public std::exception   //�Լ����쳣��̳б�׼���е��쳣��
{
public:                               //������Ϊchar*����,��stringת��Ϊchar*
	TreeError(std::string str) :std::exception(str.c_str()) {}
};

class MyTree{
private:
	TreeNode* root;
public:
	MyTree(std::vector<int>&buff){
		if (buff.empty()){
			throw new TreeError("�����С����");//�����������쳣�����ڴ�й©
		}
		std::queue<TreeNode*>Queue;
		root = new TreeNode(buff[0]);
		Queue.push(root);
		for (int i = 0; i < buff.size(); i++){
			TreeNode*node = Queue.front(); Queue.pop();
			node->val = buff[i];
			node->left = new TreeNode(); node->left->parent = node; node->left->flag = false;//���ڵ�����
			node->right = new TreeNode(); node->right->parent = node; node->right->flag = true;
			Queue.push(node->left); Queue.push(node->right);
		}
		while (!Queue.empty()){//ɾ���ഴ���Ľڵ�
			TreeNode*node = Queue.front(); Queue.pop();
			if (node->flag == true){
				node->parent->right = nullptr;
			}
			else{
				node->parent->left = nullptr;
			}
			delete node;
			node = nullptr;
		}
	}
private:
	void _delNode(TreeNode*node){
		if (node == nullptr){
			return;
		}
		_delNode(node->left);
		_delNode(node->right);
		delete node;
	}
public:
	~MyTree(){
		_delNode(root);
	}
private:
	void _SequenceDisplay(TreeNode*node){
		if (node == nullptr){
			return;
		}
		std::queue<TreeNode*>q;
		q.push(node);
		while (!q.empty()){
			TreeNode*nodeTmp = q.front(); q.pop();
			std::cout << nodeTmp->val << " ";
			if (nodeTmp->left != nullptr){
				q.push(nodeTmp->left);
			}
			if (nodeTmp->right != nullptr){
				q.push(nodeTmp->right);
			}
		}
	}
public:
	void SequenceDisplay(){
		_SequenceDisplay(root);
	}
private:
	void _PreDisplay(TreeNode* node){
		if (node == nullptr){
			return;
		}
		std::cout << node->val << " ";
		_PreDisplay(node->left);
		_PreDisplay(node->right);
	}
	void _PreDisplayNotRecurve(TreeNode*node){//ǰ������ǵݹ�
		if (node == nullptr){
			return;
		}
		std::stack<TreeNode*>Stack;
		while (node!=nullptr||!Stack.empty()){
			while (node != nullptr){
				std::cout << node->val << " ";
				Stack.push(node);
				node = node->left;
			}
			node = Stack.top(); Stack.pop();
			node = node->right;
		}
	}
	void _PreMorrisDisplay(TreeNode*node){
		if (node == nullptr){
			return;
		}
		TreeNode*nodeRight = nullptr;
		while (node != nullptr){
			//������������ڣ��ҵ������������ҽڵ�
			nodeRight = node->left;
			if (nodeRight != nullptr){
				while (nodeRight->right != nullptr&&nodeRight->right != node){
					nodeRight = nodeRight->right;
				}
				if (nodeRight->right == nullptr){
					//��һ�α���������ڵ�
					std::cout << node->val << " ";
					nodeRight->right = node;
					node = node->left;
					continue;
				}
				else if (nodeRight->right == node){
					//node���������Σ���ԭ��
					nodeRight->right = nullptr;
				}
			}
			else{
				//������������
				std::cout << node->val << " ";
			}
			node = node->right;
		}
	}
public:
	void PreDisplay(){
		if (root == nullptr){
			throw new TreeError("���ڵ�Ϊ��");
		}
		_PreDisplay(root);
		std::cout << std::endl;
		//ǰ������ǵݹ�
		_PreDisplayNotRecurve(root);
		std::cout << std::endl;
		_PreMorrisDisplay(root);
		std::cout << std::endl;
	}
private:
	void _InorDisplay(TreeNode*node){
		if (node == nullptr){
			return;
		}
		_InorDisplay(node->left);
		std::cout << node->val << " ";
		_InorDisplay(node->right);
	}
	void _InorDisplayNotRecurve(TreeNode*node){
		if (node == nullptr){
			return;
		}
		std::stack<TreeNode*>Stack;
		while (node!=nullptr||!Stack.empty()){
			while (node != nullptr){
				Stack.push(node);
				node = node->left;
			}
			node = Stack.top(); Stack.pop();
			std::cout << node->val << " ";
			node = node->right;
		}
	}
	void _InorMorrisDisplay(TreeNode*node){
		if (node == nullptr){
			return;
		}
		TreeNode*nodeRight = nullptr;
		while (node != nullptr){
			//������������ڣ��ҵ������������ҽڵ�
			nodeRight = node->left;
			if (nodeRight != nullptr){
				while (nodeRight->right != nullptr&&nodeRight->right != node){
					nodeRight = nodeRight->right;
				}
				if (nodeRight->right == nullptr){
					//��һ�α���������ڵ�
					nodeRight->right = node;
					node = node->left;
					continue;
				}
				else if (nodeRight->right == node){
					//node���������Σ���ԭ��
					nodeRight->right = nullptr;
					std::cout << node->val << " ";
				}
			}
			else{
				//������������
				std::cout << node->val << " ";
			}
			node = node->right;
		}
	}
public:
	//�������
	void InorDisplay(){
		if (root == nullptr){
			throw new TreeError("���ڵ�Ϊ��");
		}
		_InorDisplay(root);
		std::cout << std::endl;
		_InorDisplayNotRecurve(root);
		std::cout << std::endl;
		_InorMorrisDisplay(root);
		std::cout << std::endl;
	}

private:
	void _PostorderDisPlay(TreeNode*node){
		if (node == nullptr){
			return;
		}
		_PostorderDisPlay(node->left);
		_PostorderDisPlay(node->right);
		std::cout << node->val << " ";
	}
	void  _PostorderDisPlayNotRecurve(TreeNode*node){
		if (node == nullptr){
			return;
		}
		std::stack<TreeNode*>Stack;
		TreeNode*prev = nullptr;
		while (node != nullptr || !Stack.empty()){
			while (node != nullptr){
				Stack.push(node);
				node = node->left;
			}
			node = Stack.top(); Stack.pop();
			if (node->right == nullptr || node->right == prev){
				std::cout << node->val << " ";
				prev = node;
				node = nullptr;//�����´�ѭ�����½�node��ջ�������ظ�����
			}
			else{
				Stack.push(node);
				node = node->right;
			}
		}
	}
	void _PostorderMorrisDisPlay(TreeNode*node,std::vector<int>&ret){
		//ret��ź���������
		if (node == nullptr){
			return;
		}
		TreeNode*leftNode = nullptr;
		while (node != nullptr){
			leftNode = node->right;
			if (leftNode != nullptr){
				while (leftNode->left != nullptr&&leftNode->left != node){
					leftNode = leftNode->left;
				}
				if (leftNode->left == nullptr){
					ret.emplace_back(node->val);
					leftNode->left = node;
					node=node->right;
					continue;
				}
				else{
					leftNode->left = nullptr;//��ԭ
				}
			}
			else{
				ret.emplace_back(node->val);
			}
			node = node->left;
		}
		std::reverse(ret.begin(), ret.end());
	}

public:
	//�������
	void PostorderDisPlay(){
		if (root == nullptr){
			throw new TreeError("���ڵ�Ϊ��");
		}
		_PostorderDisPlay(root);
		std::cout << std::endl;
		_PostorderDisPlayNotRecurve(root);
		std::cout << std::endl;
		std::vector<int>ret;
		_PostorderMorrisDisPlay(root, ret);
		for (auto num : ret){
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}

	//��ȡ��������k��ڵ����
private:
	int _getKSize(TreeNode*root, int K){
		if (root == nullptr || K <= 0){
			return 0;
		}
		if (K == 1){
			return 1;
		}
		return _getKSize(root->left, K - 1) + _getKSize(root->right, K - 1);
	}
public:
	int getKSize(int K){
		if (root == nullptr){
			throw new TreeError("���ڵ�Ϊ��");
		}
		return _getKSize(root,K);
	}

};