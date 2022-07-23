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

void TestGraphDijkstra()
{
	vector<char> str = { 's','y','z','t','x' };
	matrix::Graph<char, int, INT_MAX, true> g(str); 
	g.AddEdge('s', 't', 10);
	g.AddEdge('s', 'y', 5);
	g.AddEdge('y', 't', 3);
	g.AddEdge('y', 'x', 9);
	g.AddEdge('y', 'z', 2);
	g.AddEdge('z', 's', 7);
	g.AddEdge('z', 'x', 6);
	g.AddEdge('t', 'y', 2);
	g.AddEdge('t', 'x', 1);
	g.AddEdge('x', 'z', 4);
	vector<int> dist; vector<int> parentPath;
	g.Dijkstra('s', dist, parentPath);
	g.PrintShortPath('s',dist, parentPath);
}

void TestGraphBellmanFord()
{
	//vector<char> str = { 's','y','z','t','x' };
	//matrix::Graph<char, int, INT_MAX, true> g(str);
	//g.AddEdge('s', 't', 6);
	//g.AddEdge('s', 'y', 7);
	//g.AddEdge('y', 'z', 9);
	//g.AddEdge('y', 'x', -3);
	//g.AddEdge('z', 's', 2);
	//g.AddEdge('z', 'x', 7);
	//g.AddEdge('t', 'x', 5);
	//g.AddEdge('t', 'y', 8);
	//g.AddEdge('t', 'z', -4);
	//g.AddEdge('x', 't', -2);
	//vector<int> dist;
	//vector<int> parentPath;
	//g.BellmanFord('s', dist, parentPath);
	//g.PrintShortPath('s', dist, parentPath);

	vector<char> str = { 's','y','z','t','x' };
	matrix::Graph<char, int, INT_MAX, true> g(str);
	g.AddEdge('s', 't', 6);
	g.AddEdge('s', 'y', 7);
	g.AddEdge('y', 'z', 9);
	g.AddEdge('y', 'x', -3);
	g.AddEdge('y', 's', 1); // 新增
	g.AddEdge('z', 's', 2);
	g.AddEdge('z', 'x', 7);
	g.AddEdge('t', 'x', 5);
	g.AddEdge('t', 'y', -8); //更改
	//g.AddEdge('t', 'y', 8);

	g.AddEdge('t', 'z', -4);
	g.AddEdge('x', 't', -2);
	vector<int> dist;
	vector<int> parentPath;
	if (g.BellmanFord('s', dist, parentPath))
		g.PrintShortPath('s', dist, parentPath);
	else
		cout << "带负权回路" << endl;
}

void TestFloydWarShall()
{
	vector<char> str = { '1','2','3','4','5' };
	matrix::Graph<char, int, INT_MAX, true> g(str);
	g.AddEdge('1', '2', 3);
	g.AddEdge('1', '3', 8);
	g.AddEdge('1', '5', -4);
	g.AddEdge('2', '4', 1);
	g.AddEdge('2', '5', 7);
	g.AddEdge('3', '2', 4);
	g.AddEdge('4', '1', 2);
	g.AddEdge('4', '3', -5);
	g.AddEdge('5', '4', 6);


	vector<vector<int>> vDist; vector<vector<int>> vPath; 
	g.FloydWarShall(vDist, vPath);

	// 打印任意两点之间的最短路径
	for (size_t i = 0; i < str.size(); ++i)
	{
		g.PrintShortPath(str[i], vDist[i], vPath[i]);
		cout << endl;
	}
}
int main() {
	TestFloydWarShall();
}