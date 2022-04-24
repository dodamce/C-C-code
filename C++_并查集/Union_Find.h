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
		ufs.resize(size,-1);//��ʼ�����鼯
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
		int ret = 0;
		while (x >= 0) {
			ret = x;
			x = ufs[x];
		}
		return ret;
	}

	size_t Size() {
		int ret = 0;
		for (int i = 0; i < ufs.size(); i++) {
			if (ufs[i] < 0) {
				ret++;
			}
		}
		return ret;
	}
};