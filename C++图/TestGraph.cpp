#include"Graph.h"

using namespace std;

void TestGraph() {
	vector<char>points = { 'A','B','C','D' };
	matrix::Graph<char, int, INT_MAX, true>graph(points);
	graph.AddEdge('A', 'B', 1);
	graph.AddEdge('A', 'D', 4);
	graph.AddEdge('B', 'D', 2);
	graph.AddEdge('B', 'C', 9);
	graph.AddEdge('C', 'D', 8);
	graph.AddEdge('C', 'B', 5);
	graph.AddEdge('C', 'A', 3);
	graph.AddEdge('D', 'C', 6);
	graph.Print();
	graph.BFS('A');
	graph.DFS('C');
}

void Test2() {
	vector<char>points = { 'A','B','C','D' };
	matrix::Graph<char, int, INT_MAX>graph(points);
	graph.AddEdge('A', 'B', 1);
	graph.AddEdge('A', 'D', 4);
	graph.AddEdge('B', 'D', 2);
	graph.AddEdge('B', 'C', 9);
	graph.AddEdge('C', 'D', 8);
	graph.AddEdge('C', 'A', 3);
	graph.Print();
	graph.BFS('A');
	graph.DFS('C');
}

void TestGraphMinTree()
{
	std::vector<char>vet{ 'a','b','c','d','e','f','g','h','i' };
	matrix::Graph<char, int> g(vet);
	g.AddEdge('a', 'b', 4);
	g.AddEdge('a', 'h', 8);
	//g.AddEdge('a', 'h', 9);
	g.AddEdge('b', 'c', 8);
	g.AddEdge('b', 'h', 11);
	g.AddEdge('c', 'i', 2);
	g.AddEdge('c', 'f', 4);
	g.AddEdge('c', 'd', 7);
	g.AddEdge('d', 'f', 14);
	g.AddEdge('d', 'e', 9);
	g.AddEdge('e', 'f', 10);
	g.AddEdge('f', 'g', 2);
	g.AddEdge('g', 'h', 1);
	g.AddEdge('g', 'i', 6);
	g.AddEdge('h', 'i', 7);
	/*matrix::Graph<char, int> kminTree;
	std::cout << "Kruskal:" << g.Kruskal(kminTree) << std::endl;*/
	matrix::Graph<char, int> primTree;
	std::cout << "Prim:" << g.Prim(primTree,'a') << std::endl;
	primTree.Print();
}
int main() {
	TestGraphMinTree();
}