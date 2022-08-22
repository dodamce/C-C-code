#include"StopWatch.h"

void TestAdd() {
	Skiplist sp;
	int arr[] = { 1,2,3,4 };
	for (auto num : arr) {
		sp.add(num);
	}
	//sp.search(0);
	sp._Print();
	for (auto num : arr) {
		sp.erase(num);
	}
}

int main() {
	TestAdd();
	return 0;
}