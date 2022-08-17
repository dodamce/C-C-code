#include"BTree.h"

int main() {
	int arr[] = { 53, 139, 75, 49, 145, 36, 50, 47, 101 };
	BTree<int, 3>bTree;
	for (auto& e : arr) {
		bTree.Insert(e);
	}
	bTree.Inorder();
	return 0;
}