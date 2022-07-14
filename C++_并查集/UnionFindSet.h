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
		ufs.resize(size, -1);//��ʼ�����鼯
	}

	//x1��x2���ڵ��������Ϻϲ�
	void Unoin(int x, int y) {
		assert(x < ufs.size() && y < ufs.size());
		//�ҵ��������ϵĸ��ڵ�
		int root1 = FindRoot(x);
		int root2 = FindRoot(y);
		//������һ�������У�����Ҫ�ϲ�
		if (root1 != root2) {
			ufs[root1] += ufs[root2];
			ufs[root2] = root1;
		}
	}

	//�ҵ�ĳ�����ϵĸ��ڵ�
	int FindRoot(int x) {
		assert(x < ufs.size());
		int root = 0;
		while (x >= 0) {
			root = x;
			x = ufs[x];
		}

		//������ڵ㣬����ڵ㵽���ڵ�·���ϵ����нڵ���뵽���ڵ���
		while (ufs[x] >= 0) {
			int parent = ufs[x];
			ufs[x] = root;
			x = parent;
		}

		return root;
	}

	size_t Size() {//���ز��鼯�м��ϵĸ���
		int ret = 0;
		for (int i = 0; i < ufs.size(); i++) {
			if (ufs[i] < 0) {
				ret++;
			}
		}
		return ret;
	}
};
