#pragma once

#include<vector>
#include<map>
#include<iostream>
#include<queue>
#include<algorithm>

#include"UnionFindSet.h"

//v:顶点 w:权值 max_w:最大权值 Direction:判断图是有向图还是无向图

//邻接表保存边关系
namespace link_table {
	template<class w>
	struct Edge{
		int detPos;
		int srcPos;
		w weight;
		Edge<w>* next;
		Edge(int _srcPos, int _detPos, const w& _weight)
			:detPos(_detPos), srcPos(_srcPos), weight(_weight),next(nullptr)
		{}
	};
	template<class v, class w, bool Direction = false>
	class Graph {
		typedef Edge<w> Edge;
	private:
		std::vector<v>_vertexs;//顶点集合
		std::map<v, int>_indexMap;//顶点与下标的映射
		std::vector<Edge*>_tables;//邻接表
		//获取顶点下标
		size_t GetPointIndex(const v& point) {
			auto ptr = _indexMap.find(point);
			if (ptr != _indexMap.end()) {
				return ptr->second;
			}
			else {
				throw std::invalid_argument("顶点不存在");
				return -1;
			}
		}
	public:
		//图的创建
		Graph(std::vector<v>& points) {
			_vertexs.resize(points.size());
			for (size_t i = 0; i < points.size(); i++) {
				_vertexs[i] = points[i];
				_indexMap[points[i]] = i;
			}
			_tables.resize(points.size(), nullptr);
		}

		//添加边关系，输入两个点，以及这两个点连线边的权值。
		void AddEdge(const v& src, const v& det, const w& weight) {
			size_t posSrc = GetPointIndex(src);
			size_t posDet = GetPointIndex(det);

			Edge* edge = new Edge(posSrc, posDet, weight);
			//头插
			edge->next = _tables[posSrc];
			_tables[posSrc] = edge;

			if (Direction == false) {
				//有向图
				Edge* edge = new Edge(posDet, posSrc, weight);
				edge->next = _tables[posDet];
				_tables[posDet] = edge;
			}
		}

		void Print() {
			//打印顶点对应坐标
			for (size_t i = 0; i < _vertexs.size(); i++) {
				std::cout << "[" << i << "]" << "->" << _vertexs[i] << std::endl;
				std::cout << std::endl;
			}

			for (size_t i = 0; i < _tables.size(); i++) {
				std::cout << _vertexs[i] << "[" << i << "]:";
				Edge* node = _tables[i];
				while (node != nullptr) {
					std::cout << _vertexs[node->detPos] <<
						"[" << node->detPos << "]" << "(" << node->weight << ")" << " ";
					node = node->next;
				}
				std::cout << "nullptr" << std::endl;
			}
		}
	};
}

namespace matrix {
	//邻接矩阵保存边关系
	template<class v, class w, w max_w = INT_MAX, bool Direction = false>
	class Graph {
		typedef Graph<v, w, max_w, Direction>Self;
	private:
		std::vector<v>_vertexs;//顶点集合
		std::map<v, int>_indexMap;//顶点与下标的映射
		std::vector<std::vector<w>>_matrix;//邻接矩阵
		//获取顶点下标
		size_t GetPointIndex(const v& point) {
			auto ptr = _indexMap.find(point);
			if (ptr != _indexMap.end()) {
				return ptr->second;
			}
			else {
				throw std::invalid_argument("顶点不存在");
				return -1;
			}
		}
	public:
		//图的创建
		Graph() = default;
		Graph(std::vector<v>& points) {
			_vertexs.resize(points.size());
			for (size_t i = 0; i < points.size(); i++) {
				_vertexs[i] = points[i];
				_indexMap[points[i]] = i;
			}

			_matrix.resize(points.size());
			//邻接矩阵
			for (int i = 0; i < _matrix.size(); i++) {
				_matrix[i].resize(points.size(), max_w);
			}
		}

		//添加边关系，输入两个点，以及这两个点连线边的权值。
	private:
		void _AddEdge(size_t posSrc, size_t posDst, const w& weight) {
			//区分有向图与无向图
			_matrix[posSrc][posDst] = weight;
			if (Direction == false) {
				//无向图，添加两条边关系
				_matrix[posDst][posSrc] = weight;
			}
		}
	public:
		void AddEdge(const v& src, const v& dst, const w& weight) {
			size_t posSrc = GetPointIndex(src);
			size_t posDst = GetPointIndex(dst);
			_AddEdge(posSrc, posDst, weight);
		}
	private:
		void _DFS(size_t srcPos, std::vector<bool>& visited) {
			std::cout << srcPos << ":" << _vertexs[srcPos] << " ";
			visited[srcPos] = true;
			for (size_t i = 0; i < _vertexs.size(); i++) {
				if (_matrix[srcPos][i] != max_w && visited[i] == false) {
					_DFS(i, visited);
				}
			}
		}
	public:
		struct Edge {
			size_t posSrc;
			size_t posDst;
			w weight;
			Edge(size_t _posSrc, size_t _posDst, const w& _weight)
				:posSrc(_posSrc), posDst(_posDst), weight(_weight)
			{}
		};
		struct rules {
			bool operator()(const Edge& left, const Edge& right) {
				return left.weight > right.weight;//从小到大
			}
		};
		//最小生成树，返回最小生成树权值，传入一个图，这个参数是输入输出参数，函数结束后，minTree是图的最小生成树
		w Kruskal(Self& minTree) {
			size_t size = _vertexs.size();
			//初始化minTree
			minTree._vertexs = _vertexs;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(size);
			for (size_t i = 0; i < size; i++) {
				minTree._matrix[i].resize(size, max_w);
			}
			std::priority_queue<Edge, std::vector<Edge>,rules> MinQueue;//从小到大
			//将所有的边添加到优先级队列中
			for (int i = 0; i < size; i++) {
				//因为最小生成树只在无向图中成立，所以只要遍历邻接矩阵一半即可
				for (size_t j = 0; j < i; j++) {
					if (_matrix[i][j] != max_w) {
						MinQueue.push(Edge(i, j, _matrix[i][j]));
					}
				}
			}

			//选出n-1条边
			int dstSize = 0;
			w totalW = w();//总共的权值
			//创建并查集来标记是否成环,大小为图顶点个数。
			UnionFindSet ufs(size);
			while (!MinQueue.empty()) {
				Edge minEdge = MinQueue.top();
				MinQueue.pop();
				//判断这条边顶点是否在并查集中，在并查集中构成环，不符合最小生成树定义。
				if (!ufs.InSet(minEdge.posSrc, minEdge.posDst)) {
					//打印选的边测试
					std::cout << _vertexs[minEdge.posSrc] << "->" << _vertexs[minEdge.posDst] << "权值:" << minEdge.weight << std::endl;
					minTree._AddEdge(minEdge.posSrc, minEdge.posDst, minEdge.weight);
					ufs.Unoin(minEdge.posSrc, minEdge.posDst);
					dstSize++;
					totalW += minEdge.weight;
				}
			}
			if (dstSize == size - 1) {
				//找到最小生成树
				return totalW;
			}
			else {
				//没找到最小生成树，返回权值的默认值,如果权值是整数则返回0
				return w();
			}
		}

		//最小生成树，返回最小生成树权值，传入一个图，这个参数是输入输出参数，函数结束后，minTree是图的最小生成树
		//Src:Prim算法传入的起始点
		w Prim(Self& minTree, const v& Src) {
			size_t posSrc = GetPointIndex(Src);
			//初始化minTree
			size_t size = _vertexs.size();
			minTree._vertexs = _vertexs;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(size);
			for (size_t i = 0; i < size; i++) {
				minTree._matrix[i].resize(size, max_w);
			}
			std::vector<bool>X(size,false);//已经加入的顶点的集合
			std::vector<bool>Y(size, true);//未加入的顶点的集合
			X[posSrc] = true; Y[posSrc] = false;

			//从两个集合中选择两个点，构成权值最小的边
			std::priority_queue<Edge, std::vector<Edge>, rules> minQueue;
			//将这个顶点连接的边入队列
			for (size_t i = 0; i < size; i++) {
				if (_matrix[posSrc][i] != max_w) {
					minQueue.push(Edge(posSrc, i, _matrix[posSrc][i]));
				}
			}

			//选择权值最小的边，添加到最小生成树
			size_t edgeSize = 0;
			w weight = w();
			while (!minQueue.empty()) {
				Edge minEdge = minQueue.top();
				minQueue.pop();

				//如果这条边的两个顶点在一个集合X中,说明构成环
				if (X[minEdge.posDst]) {
					//构成环
					continue;
				}

				std::cout << _vertexs[minEdge.posSrc] << "->" << _vertexs[minEdge.posDst] << "权值:" << minEdge.weight << endl;

				minTree._AddEdge(minEdge.posSrc, minEdge.posDst, minEdge.weight);
				X[minEdge.posDst] = true;
				Y[minEdge.posDst] = false;
				edgeSize++;
				weight += minEdge.weight;
				//size个点，选size-1条边就可以结束循环了
				if (edgeSize == size - 1) {
					break;
				}
				//posSrc---posDst，把posDst点所有边（除了posSrc---posDst）加入优先级队列
				//所以posDst的另一个点不在集合X即可。
				for (size_t i = 0; i < size; i++) {
					if (_matrix[minEdge.posDst][i] != max_w && X[i] == false) {
						minQueue.push(Edge(minEdge.posDst, i, _matrix[minEdge.posDst][i]));
					}
				}
			}
			if (edgeSize == size - 1) {
				return weight;
			}
			else {
				return w();
			}
		}

		//深度优先遍历
		void DFS(const v& src) {
			size_t posSrc = GetPointIndex(src);
			std::vector<bool>visited(_vertexs.size(), false);
			_DFS(posSrc, visited);
			std::cout << std::endl;
		}

		void BFS(const v& src) {//传入起点
			size_t srcPos = GetPointIndex(src);
			std::queue<size_t>q;
			q.push(srcPos);
			//标记数组
			std::vector<bool>visited(_vertexs.size(), false);
			visited[srcPos] = true;//入队列标记
			size_t leveSize = 1;//每层节点个数
			size_t leve = 1;//层数
			while (!q.empty()) {
				for (size_t i = 0; i < leveSize; i++) {
					size_t front = q.front();
					std::cout << front << ":" << _vertexs[front] << " ";
					q.pop();
					//这个节点周围的节点入队
					for (size_t i = 0; i < _vertexs.size(); i++) {
						if (_matrix[front][i] != max_w) {
							//入队列时标记已经访问
							if (visited[i] == false) {
								q.push(i);
								visited[i] = true;
							}
						}
					}
				}
				leveSize = q.size();
				std::cout << "第" << leve++ << "层" << std::endl;
			}
			std::cout << std::endl;
		}

		void Print() {
			//打印顶点对应坐标
			for (size_t i = 0; i < _vertexs.size(); i++) {
				std::cout << "[" << i << "]" << "->" << _vertexs[i] << std::endl;
				std::cout << std::endl;
			}

			//打印边
			std::cout << "  ";
			for (int i = 0; i < _vertexs.size(); i++) {
				std::cout << _vertexs[i] << " ";
			}
			std::cout << std::endl;

			//打印矩阵
			for (size_t i = 0; i < _matrix.size(); i++) {
				std::cout << _vertexs[i] << " ";
				for (size_t j = 0; j < _matrix[i].size(); j++) {
					if (_matrix[i][j] == max_w) {
						std::cout << "*" << " ";
					}
					else {
						std::cout << _matrix[i][j] << " ";
					}
				}
				std::cout << std::endl;
			}
		}
	};
}