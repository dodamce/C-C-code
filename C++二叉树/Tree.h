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


class TreeError :public std::exception   //自己的异常类继承标准库中的异常类
{
public:                               //父类中为char*类型,把string转换为char*
	TreeError(std::string str) :std::exception(str.c_str()) {}
};

class MyTree{
private:
	TreeNode* root;
public:
	MyTree(std::vector<int>&buff){
		if (buff.empty()){
			throw new TreeError("数组大小有误");//可能由于抛异常导致内存泄漏
		}
		std::queue<TreeNode*>Queue;
		root = new TreeNode(buff[0]);
		Queue.push(root);
		for (int i = 0; i < buff.size(); i++){
			TreeNode*node = Queue.front(); Queue.pop();
			node->val = buff[i];
			node->left = new TreeNode(); node->left->parent = node; node->left->flag = false;//父节点的左边
			node->right = new TreeNode(); node->right->parent = node; node->right->flag = true;
			Queue.push(node->left); Queue.push(node->right);
		}
		while (!Queue.empty()){//删除多创建的节点
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
	void _PreDisplayNotRecurve(TreeNode*node){//前序遍历非递归
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
			//如果左子树存在，找到左子树的最右节点
			nodeRight = node->left;
			if (nodeRight != nullptr){
				while (nodeRight->right != nullptr&&nodeRight->right != node){
					nodeRight = nodeRight->right;
				}
				if (nodeRight->right == nullptr){
					//第一次遍历到这个节点
					std::cout << node->val << " ";
					nodeRight->right = node;
					node = node->left;
					continue;
				}
				else if (nodeRight->right == node){
					//node遍历过两次，还原树
					nodeRight->right = nullptr;
				}
			}
			else{
				//左子树不存在
				std::cout << node->val << " ";
			}
			node = node->right;
		}
	}
public:
	void PreDisplay(){
		if (root == nullptr){
			throw new TreeError("树节点为空");
		}
		_PreDisplay(root);
		std::cout << std::endl;
		//前序遍历非递归
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
			//如果左子树存在，找到左子树的最右节点
			nodeRight = node->left;
			if (nodeRight != nullptr){
				while (nodeRight->right != nullptr&&nodeRight->right != node){
					nodeRight = nodeRight->right;
				}
				if (nodeRight->right == nullptr){
					//第一次遍历到这个节点
					nodeRight->right = node;
					node = node->left;
					continue;
				}
				else if (nodeRight->right == node){
					//node遍历过两次，还原树
					nodeRight->right = nullptr;
					std::cout << node->val << " ";
				}
			}
			else{
				//左子树不存在
				std::cout << node->val << " ";
			}
			node = node->right;
		}
	}
public:
	//中序遍历
	void InorDisplay(){
		if (root == nullptr){
			throw new TreeError("树节点为空");
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
				node = nullptr;//避免下次循环重新将node入栈，导致重复遍历
			}
			else{
				Stack.push(node);
				node = node->right;
			}
		}
	}
	void _PostorderMorrisDisPlay(TreeNode*node,std::vector<int>&ret){
		//ret存放后序遍历结果
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
					leftNode->left = nullptr;//还原
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
	//后序遍历
	void PostorderDisPlay(){
		if (root == nullptr){
			throw new TreeError("树节点为空");
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

	//获取二叉树第k层节点个数
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
			throw new TreeError("树节点为空");
		}
		return _getKSize(root,K);
	}

};