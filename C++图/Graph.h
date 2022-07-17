#pragma once

#include<vector>
#include<map>
#include<iostream>
#include<queue>
#include<algorithm>

#include"UnionFindSet.h"

//v:���� w:Ȩֵ max_w:���Ȩֵ Direction:�ж�ͼ������ͼ��������ͼ

//�ڽӱ���߹�ϵ
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
		std::vector<v>_vertexs;//���㼯��
		std::map<v, int>_indexMap;//�������±��ӳ��
		std::vector<Edge*>_tables;//�ڽӱ�
		//��ȡ�����±�
		size_t GetPointIndex(const v& point) {
			auto ptr = _indexMap.find(point);
			if (ptr != _indexMap.end()) {
				return ptr->second;
			}
			else {
				throw std::invalid_argument("���㲻����");
				return -1;
			}
		}
	public:
		//ͼ�Ĵ���
		Graph(std::vector<v>& points) {
			_vertexs.resize(points.size());
			for (size_t i = 0; i < points.size(); i++) {
				_vertexs[i] = points[i];
				_indexMap[points[i]] = i;
			}
			_tables.resize(points.size(), nullptr);
		}

		//��ӱ߹�ϵ�����������㣬�Լ������������߱ߵ�Ȩֵ��
		void AddEdge(const v& src, const v& det, const w& weight) {
			size_t posSrc = GetPointIndex(src);
			size_t posDet = GetPointIndex(det);

			Edge* edge = new Edge(posSrc, posDet, weight);
			//ͷ��
			edge->next = _tables[posSrc];
			_tables[posSrc] = edge;

			if (Direction == false) {
				//����ͼ
				Edge* edge = new Edge(posDet, posSrc, weight);
				edge->next = _tables[posDet];
				_tables[posDet] = edge;
			}
		}

		void Print() {
			//��ӡ�����Ӧ����
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
	//�ڽӾ��󱣴�߹�ϵ
	template<class v, class w, w max_w = INT_MAX, bool Direction = false>
	class Graph {
		typedef Graph<v, w, max_w, Direction>Self;
	private:
		std::vector<v>_vertexs;//���㼯��
		std::map<v, int>_indexMap;//�������±��ӳ��
		std::vector<std::vector<w>>_matrix;//�ڽӾ���
		//��ȡ�����±�
		size_t GetPointIndex(const v& point) {
			auto ptr = _indexMap.find(point);
			if (ptr != _indexMap.end()) {
				return ptr->second;
			}
			else {
				throw std::invalid_argument("���㲻����");
				return -1;
			}
		}
	public:
		//ͼ�Ĵ���
		Graph() = default;
		Graph(std::vector<v>& points) {
			_vertexs.resize(points.size());
			for (size_t i = 0; i < points.size(); i++) {
				_vertexs[i] = points[i];
				_indexMap[points[i]] = i;
			}

			_matrix.resize(points.size());
			//�ڽӾ���
			for (int i = 0; i < _matrix.size(); i++) {
				_matrix[i].resize(points.size(), max_w);
			}
		}

		//��ӱ߹�ϵ�����������㣬�Լ������������߱ߵ�Ȩֵ��
	private:
		void _AddEdge(size_t posSrc, size_t posDst, const w& weight) {
			//��������ͼ������ͼ
			_matrix[posSrc][posDst] = weight;
			if (Direction == false) {
				//����ͼ����������߹�ϵ
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
				return left.weight > right.weight;//��С����
			}
		};
		//��С��������������С������Ȩֵ������һ��ͼ����������������������������������minTree��ͼ����С������
		w Kruskal(Self& minTree) {
			size_t size = _vertexs.size();
			//��ʼ��minTree
			minTree._vertexs = _vertexs;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(size);
			for (size_t i = 0; i < size; i++) {
				minTree._matrix[i].resize(size, max_w);
			}
			std::priority_queue<Edge, std::vector<Edge>,rules> MinQueue;//��С����
			//�����еı���ӵ����ȼ�������
			for (int i = 0; i < size; i++) {
				//��Ϊ��С������ֻ������ͼ�г���������ֻҪ�����ڽӾ���һ�뼴��
				for (size_t j = 0; j < i; j++) {
					if (_matrix[i][j] != max_w) {
						MinQueue.push(Edge(i, j, _matrix[i][j]));
					}
				}
			}

			//ѡ��n-1����
			int dstSize = 0;
			w totalW = w();//�ܹ���Ȩֵ
			//�������鼯������Ƿ�ɻ�,��СΪͼ���������
			UnionFindSet ufs(size);
			while (!MinQueue.empty()) {
				Edge minEdge = MinQueue.top();
				MinQueue.pop();
				//�ж������߶����Ƿ��ڲ��鼯�У��ڲ��鼯�й��ɻ�����������С���������塣
				if (!ufs.InSet(minEdge.posSrc, minEdge.posDst)) {
					//��ӡѡ�ı߲���
					std::cout << _vertexs[minEdge.posSrc] << "->" << _vertexs[minEdge.posDst] << "Ȩֵ:" << minEdge.weight << std::endl;
					minTree._AddEdge(minEdge.posSrc, minEdge.posDst, minEdge.weight);
					ufs.Unoin(minEdge.posSrc, minEdge.posDst);
					dstSize++;
					totalW += minEdge.weight;
				}
			}
			if (dstSize == size - 1) {
				//�ҵ���С������
				return totalW;
			}
			else {
				//û�ҵ���С������������Ȩֵ��Ĭ��ֵ,���Ȩֵ�������򷵻�0
				return w();
			}
		}

		//��С��������������С������Ȩֵ������һ��ͼ����������������������������������minTree��ͼ����С������
		//Src:Prim�㷨�������ʼ��
		w Prim(Self& minTree, const v& Src) {
			size_t posSrc = GetPointIndex(Src);
			//��ʼ��minTree
			size_t size = _vertexs.size();
			minTree._vertexs = _vertexs;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(size);
			for (size_t i = 0; i < size; i++) {
				minTree._matrix[i].resize(size, max_w);
			}
			std::vector<bool>X(size,false);//�Ѿ�����Ķ���ļ���
			std::vector<bool>Y(size, true);//δ����Ķ���ļ���
			X[posSrc] = true; Y[posSrc] = false;

			//������������ѡ�������㣬����Ȩֵ��С�ı�
			std::priority_queue<Edge, std::vector<Edge>, rules> minQueue;
			//������������ӵı������
			for (size_t i = 0; i < size; i++) {
				if (_matrix[posSrc][i] != max_w) {
					minQueue.push(Edge(posSrc, i, _matrix[posSrc][i]));
				}
			}

			//ѡ��Ȩֵ��С�ıߣ���ӵ���С������
			size_t edgeSize = 0;
			w weight = w();
			while (!minQueue.empty()) {
				Edge minEdge = minQueue.top();
				minQueue.pop();

				//��������ߵ�����������һ������X��,˵�����ɻ�
				if (X[minEdge.posDst]) {
					//���ɻ�
					continue;
				}

				std::cout << _vertexs[minEdge.posSrc] << "->" << _vertexs[minEdge.posDst] << "Ȩֵ:" << minEdge.weight << endl;

				minTree._AddEdge(minEdge.posSrc, minEdge.posDst, minEdge.weight);
				X[minEdge.posDst] = true;
				Y[minEdge.posDst] = false;
				edgeSize++;
				weight += minEdge.weight;
				//size���㣬ѡsize-1���߾Ϳ��Խ���ѭ����
				if (edgeSize == size - 1) {
					break;
				}
				//posSrc---posDst����posDst�����бߣ�����posSrc---posDst���������ȼ�����
				//����posDst����һ���㲻�ڼ���X���ɡ�
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

		//������ȱ���
		void DFS(const v& src) {
			size_t posSrc = GetPointIndex(src);
			std::vector<bool>visited(_vertexs.size(), false);
			_DFS(posSrc, visited);
			std::cout << std::endl;
		}

		void BFS(const v& src) {//�������
			size_t srcPos = GetPointIndex(src);
			std::queue<size_t>q;
			q.push(srcPos);
			//�������
			std::vector<bool>visited(_vertexs.size(), false);
			visited[srcPos] = true;//����б��
			size_t leveSize = 1;//ÿ��ڵ����
			size_t leve = 1;//����
			while (!q.empty()) {
				for (size_t i = 0; i < leveSize; i++) {
					size_t front = q.front();
					std::cout << front << ":" << _vertexs[front] << " ";
					q.pop();
					//����ڵ���Χ�Ľڵ����
					for (size_t i = 0; i < _vertexs.size(); i++) {
						if (_matrix[front][i] != max_w) {
							//�����ʱ����Ѿ�����
							if (visited[i] == false) {
								q.push(i);
								visited[i] = true;
							}
						}
					}
				}
				leveSize = q.size();
				std::cout << "��" << leve++ << "��" << std::endl;
			}
			std::cout << std::endl;
		}

		void Print() {
			//��ӡ�����Ӧ����
			for (size_t i = 0; i < _vertexs.size(); i++) {
				std::cout << "[" << i << "]" << "->" << _vertexs[i] << std::endl;
				std::cout << std::endl;
			}

			//��ӡ��
			std::cout << "  ";
			for (int i = 0; i < _vertexs.size(); i++) {
				std::cout << _vertexs[i] << " ";
			}
			std::cout << std::endl;

			//��ӡ����
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