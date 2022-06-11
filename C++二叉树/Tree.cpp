#include"Tree.h"

using namespace std;

int main(){
	std::vector<int> vet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	MyTree tree(vet);
	tree.PreDisplay();
	//cout << tree.getKSize(1) << endl;
	tree.InorDisplay();
	tree.PostorderDisPlay();
	tree.SequenceDisplay();
	return 0;
}