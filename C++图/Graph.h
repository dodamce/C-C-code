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

		//单源最短路径
		//src:源顶点 dist保存src到各个顶点的最短距离 pPath:保存最短路径的节点
		void Dijkstra(const v& src, std::vector<w>& dist, std::vector<int>& pPath) {
			size_t srcPos = GetPointIndex(src);
			size_t size = _vertexs.size();
			dist.resize(size, max_w);
			pPath.resize(size, -1);

			dist[srcPos] = 0;//源顶点到自己本身最短距离为0
			pPath[srcPos] = srcPos;//源顶点的最短路径的父节点是自己本身
			
			std::vector<bool>S(size, false);//已经确定最短路径的顶点的集合
			//循环判断所有的顶点
			for (size_t time = 0; time < size; time++) {
				//选不在S集合 最短路径的顶点，更新其他路径
				//选p点,p点不在S集合中
				int p = 0;
				w min = max_w;//最小权值
				for (size_t i = 0; i < size; i++) {
					if (S[i] == false && dist[i] < min) {
						p = i;
						min = dist[i];
					}
				}
				//把p点放入S集合中
				S[p] = true;
				//松弛更新 src->p + p->p邻接节点 与 src ->p邻接节点权值相比较小，要更新
				for (size_t adP = 0; adP < size; adP++) {
					//找p点所有的邻接顶点
					if (S[adP] == false && _matrix[p][adP] != max_w) {
						if ((dist[p] + _matrix[p][adP]) < dist[adP]) {
							dist[adP] = dist[p] + _matrix[p][adP];
							//更新这个顶点最短路径的父节点
							pPath[adP] = p;
						}
					}
				}
			}
		}

		//如果出现负权回路。函数返回false值
		bool BellmanFord(const v& src, vector<w>& dist, vector<int>& pPath) {
			size_t size = _vertexs.size();
			size_t srcPos = GetPointIndex(src);

			// vector<W> dist,记录srcPos-其他顶点最短路径权值数组
			dist.resize(size, max_w);

			// vector<int> pPath 记录srcPos-其他顶点最短路径父顶点数组
			pPath.resize(size, -1);

			// 先更新srci->srci为缺省值
			dist[srcPos] = w();

			// 总体最多更新size轮
			for (size_t time = 0; time < size; time++) {
				// i->j 更新松弛
				bool update = false;
				for (size_t i = 0; i < size; i++) {
					for (size_t j = 0; j < size; j++) {
						// srci -> i + i ->j松弛判断
						if (_matrix[i][j] != max_w && (dist[i] + _matrix[i][j]) < dist[j]) {
							dist[j]= dist[j] = dist[i] + _matrix[i][j];
							update = true;
							pPath[j] = i;
						}
					}
				}
				if (update == false) {
					break;//这次没有更新出最短路径，可以退出循环了
				}
			}

			//判断负权回路,如果退出循环还可以更新，就是负权回路返回false
			// 还能更新就是带负权回路
			for (size_t i = 0; i < size; ++i)
			{
				for (size_t j = 0; j < size; ++j)
				{
					if (_matrix[i][j] != max_w && dist[i] + _matrix[i][j] < dist[j])
					{
						return false;
					}
				}
			}
			return true;
		}
		void FloydWarShall(std::vector<std::vector<w>>& vDist, std::vector<std::vector<int>>& vPath) {
			size_t size = _vertexs.size();

			//初始化顶点矩阵与路径矩阵
			vDist.resize(size);
			vPath.resize(size);
			for (size_t i = 0; i < size; i++) {
				vDist[i].resize(size, max_w);
				vPath[i].resize(size, -1);
			}

			//直接相连的边更新初始化
			for (size_t i = 0; i < size; i++) {
				for (size_t j = 0; j < size; j++) {
					if (_matrix[i][j] != max_w) {
						vDist[i][j] = _matrix[i][j];
						vPath[i][j] = i;//i->j起点是i点
					}
					if (i == j) {
						//i->i时路径长度为0
						vDist[i][j] = w();
					}
				}
			}

			//最短路径的更新i->{其他顶点}->j
			//k作为中间点，尝试更新i->j的路径
			for (size_t k = 0; k < size; k++) {
				for (size_t i = 0; i < size; i++) {
					for (size_t j = 0; j < size; j++) {
						//经过了k点
						if (vDist[i][k] != max_w && vDist[k][j] != max_w) {
							if ((vDist[i][k] + vDist[k][j]) < vDist[i][j]) {
								//经过k更小，则更新长度
								vDist[i][j] = vDist[i][k] + vDist[k][j];
								//找上一个与j邻接的节点
								//k->j入过k与j直接相连，则vPath[i][j]=k
								//但是k->j不一定直接相连 k->...->x->j则vPath[i][j]=x,就是vPath[k][j]
								vPath[i][j] = vPath[k][j];
							}
						}
					}
				}
			}
		}

		//打印最短路径
		void PrintShortPath(const v& src, std::vector<w>& dist, std::vector<int>& pPath) {
			size_t srcPos = GetPointIndex(src);
			size_t size = _vertexs.size();
			//计算src点到其他点的最短路径长度，src到src=0不用计算
			for (size_t i = 0; i < size; i++) {
				if (i != srcPos) {
					//src到顶点i的最短路径节点（双亲表示法）
					std::vector<int>path;
					size_t pos = i;
					std::cout <<"最短路径为:";
					while (pos != srcPos) {
						path.push_back(pos);
						pos = pPath[pos];
					}
					path.push_back(srcPos);
					std::reverse(path.begin(), path.end());
					for (auto index : path) {
						std::cout << _vertexs[index] << "->";
					}
					std::cout << "长度:" << dist[i];
					std::cout << std::endl;
				}
			}
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