#pragma once

#pragma once

#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

class UnionFindSet {
private:
	vector<int>ufs;
public:
	UnionFindSet(size_t size) {
		ufs.resize(size, -1);//初始化并查集
	}

	//x1和x2所在的两个集合合并
	void Unoin(int x, int y) {
		assert(x < ufs.size() && y < ufs.size());
		//找到两个集合的根节点
		int root1 = FindRoot(x);
		int root2 = FindRoot(y);
		//本身在一个集合中，不需要合并
		if (root1 != root2) {
			ufs[root1] += ufs[root2];
			ufs[root2] = root1;
		}
	}

	//找到某个集合的根节点
	int FindRoot(int x) {
		assert(x < ufs.size());
		int root = 0;
		while (x >= 0) {
			root = x;
			x = ufs[x];
		}

		//把这个节点，这个节点到根节点路径上的所有节点插入到根节点上
		while (ufs[x] >= 0) {
			int parent = ufs[x];
			ufs[x] = root;
			x = parent;
		}

		return root;
	}

	size_t Size() {//返回并查集中集合的个数
		int ret = 0;
		for (int i = 0; i < ufs.size(); i++) {
			if (ufs[i] < 0) {
				ret++;
			}
		}
		return ret;
	}
};
