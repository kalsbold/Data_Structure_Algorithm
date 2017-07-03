#pragma once
//vector 사용해 구현.
//
#include "stdafx.h"
/*
disjoint set : 자료구조의 일종으로 상호배타적 부분집합들로 나눠진 원소들에 대한 정보를 저장하고 조작하는 자료구조.
주요 연산 : Find 어떤 원소가 주어졌을때 그 원소가 속한 집합을 반환하는 연산. 집합을 대표하는 원소를 반환함으로 구분함.
		   Union 두 개의 집합을 하나의 집합으로 합치는 연산. 
		   MakeSet 한 원소를 가지는 집합을 만드는 연산.
*/
template<class T>
class DisjointSet  // Weighted quick union + Path compression
{
private:
	map<T, unsigned int> size;	//집합의 크기
	map<T, T> parent; // 부모집합

	//집합을 합치는 함수.
	void combine(T set1, T set2)
	{
		parent[set1] = set2;
		size[set2] += size[set1];
	}

public:
	//해당 원소가 존재하는지 검색.
	//해당 원소의 위치가 end와 다르면 true 같으면 false.
	bool exists(T elem)
	{
		return parent.find(elem) != parent.end();
	}

	//해당 원소의 집합을 생성.
	//원소가 있는지부터 검색하고 추가.
	void create(T elem)
	{
		if (!exists(elem))
		{
			parent[elem] = elem;
			size[elem] = 1;
		}
	}

	//Union 역할의 함수. 인수 2개의 원소가 들어있는 집합을 검색해서 
	//합치는 연산을 함.
	void join(T elem1, T elem2)
	{
		T elem1_set = find(elem1);
		T elem2_set = find(elem2);

		if (elem1_set != elem2_set)
		{
			if (size[elem1_set] < size[elem2_set])
			{
				combine(elem1_set, elem2_set);
			}
			else
			{
				combine(elem2_set, elem1_set);
			}
		}
	}

	//두 원소가 연결되어있는지 검색하는 함수.
	//find 연산의 결과가 일치하면 같은 집합에 속하는 것이므로 연결됨.
	bool connected(T elem1, T elem2)
	{
		return find(elem1) == find(elem2);
	}

	//해당 원소를 검색해 찾아내는 함수.
	T find(T elem)
	{
		return (parent[elem] = (parent[elem] == elem ? elem : find(parent[elem])));
	}

	//집합의 크기와 집합을 받는 함수.
	//호출하는 집합의 크기, 집합을 받음.
	map<T, unsigned int> getSetsWithSize()
	{
		map<T, unsigned int> res;

		for (typename map<T, unsigned int>::iterator itr = size.begin(); itr != size.end(); itr++)
		{
			if (parent[itr->first] == itr->first)	// Root of the set
			{
				res[itr->first] = itr->second;
			}
		}

		return res;
	}

	//집합의 원소 개수를 반환하는 함수. 
	unsigned int numSets()
	{
		unsigned int cnt = 0;

		for (typename map<T, unsigned int>::iterator itr = size.begin(); itr != size.end(); itr++)
		{
			if (parent[itr->first] == itr->first)	// Root of the set
			{
				cnt++;
			}
		}

		return cnt;
	}

	friend ostream& operator<<(ostream &out, DisjointSet<T> &s)
	{
		for (typename map<T, T>::iterator itr = s.parent.begin(); itr != s.parent.end(); itr++)
		{
			out << itr->first << " ------> " << itr->second << endl;
		}

		out << "Sets: " << endl;
		map<T, unsigned int> sets = s.getSetsWithSize();
		for (typename map<T, unsigned int>::iterator itr = sets.begin(); itr != sets.end(); itr++)
		{
			out << "|" << itr->first << "| = " << itr->second << endl;
		}

		return out;
	}
};


template <class T>
//그래프의 간선. 엣지를 나타내는 클래스.
class Edge
{
public:
	T src, dest; // 출발지 도착지.
	int cost;	// 비용

	Edge(T src, T dest, int cost) : src(src), dest(dest), cost(cost)
	{
	}

	Edge(const Edge &e)
	{
		this->operator=(e);
	}

	void operator=(const Edge &e)
	{
		src = e.src;
		dest = e.src;
		cost = e.cost;
	}

	friend ostream& operator<<(ostream &out, Edge<T> &e)
	{
		out << e.src << " --------------> " << e.dest << " (" << e.cost << ")" << endl;
		return out;
	}
};

template <class T>
//그래프를 구현하는 클래스.
class Graph
{
private:

	class Vertex // 그래프의 정점. 버텍스를 나타내는 클래스.
	{
	private:
		T label; //해당 버텍스의 정보
		multiset<pair<Vertex *, int> > adj; //인접 버텍스에 대한 정보를 저장할 멀티셋.
		multiset<Vertex *> rev; // 이것은 제거된 정점에 입사하는 에지를 제거하기 위해 유지됩니다. 또한 꼭지점의 밝기를 찾는 데 도움이 됩니다.

		typename multiset<pair<Vertex *, int> >::iterator findAdjacent(Vertex *dest) const;	//인접 버텍스를 찾는 함수.

	public:
		Vertex(T label);
		~Vertex();
		
		//정보 관련 함수. 정보 설정 및 받아오는 함수.
		void setLabel(T label);
		T getLabel() const;

		//인접노드를 찾는 함수.
		multiset<pair<Vertex *, int> > getAdjacentNodes() const;
		//역방향 노드를 찾는 함수.
		multiset<Vertex *> getReverseNodes() const;

		//엣지 추가 삭제 도착지와 비용을 인수로 함.
		void addEdge(Vertex *dest, int cost);
		bool removeEdge(Vertex *dest, int cost);
		bool removeEdge(Vertex *dest);
		//새로운 인접노드를 추가하기 위해 엣지를 추가하는 함수.
		void addEdgesInBatch(multiset<pair<Vertex *, int> > new_adj);

		//엣지의 존재를 확인하는 함수. 도착지, 비용을 인수로 함.
		bool edgeExists(Vertex *dest) const;
		bool edgeExists(Vertex *dest, int cost) const;

		//엣지 수를 찾는 함수. 도착지, 비용을 인수로 함.
		unsigned int countEdge(Vertex *dest) const;
		unsigned int countEdge(Vertex *dest, int cost) const;

		//엣지의 비용을 찾는 함수. 도착지를 인수로 함.
		int edgeCost(Vertex *dest) const;
		vector<int> edgeCosts(Vertex *dest) const;

		//들어오는 길
		int indegree() const;
		//나가는 길
		int outdegree() const;

		//가중치가 음수인 엣지가 있는지?
		bool hasNegativeWeightedEdge() const;

		//들어가는 엣지 추가.
		void addIncomingEdges(Vertex *dest);

		friend ostream& operator<<(ostream& out, Vertex &v)
		{
			out << v.label << " --->  ";

			for (typename multiset<pair<Vertex *, int> >::iterator itr = v.adj.begin(); itr != v.adj.end(); itr++)
			{
				out << itr->first->getLabel() << "(" << itr->second << "), ";
			}

			out << "\b\b " << endl;

			return out;
		}
	};

	//버텍스 맵.
	map<T, Vertex *> vertices;
	//방향성 있음?
	bool is_directed;
	//버텍스 검색.
	Vertex * findVertex(T label) const;
	
	//차수 0인 버텍스 찾기
	vector<Vertex *> findVerticesWithIndegreeZero() const;
	
	//마지막 방문 버텍스 검색.
	void findFinishOrder(T label, stack<T> & finished_vertices, map<T, bool> & visited) const;

	//엣지 추가.
	bool addOneWayEdge(T head, T tail, int cost = 1);

public:
	Graph(bool is_directed);
	Graph(const Graph<T> &g);
	~Graph();

	//그래프 역
	Graph<T> reverse() const;

	//버텍스 추가
	bool addVertex(T label);
	//버텍스 삭제
	bool removeVertex(T label);
	//버텍스 이름 재설정.
	bool renameVertex(T old_label, T new_label);

	//엣지 추가
	bool addEdge(T head, T tail, int cost = 1);
	//엣지 삭제
	bool removeEdge(T head, T tail, int cost = 1);

	//엣지 수 체크
	int countEdge(T head, T tail) const;
	int countEdge(T head, T tail, int cost) const;

	//엣지 존재?
	bool edgeExists(T head, T tail) const;
	bool edgeExists(T head, T tail, int cost) const;

	//경로 존재?
	bool pathExists(T start, T end) const;

	//엣지 비용
	vector<int> edgeCosts(T head, T tail) const;

	void operator=(const Graph<T> &g);

	//들어오는 길
	int indegree(T label) const;
	//나가는 길
	int outdegree(T label) const;

	//버텍스 수
	unsigned int numVertices() const;
	//엣지 수
	unsigned int numEdges() const;

	//루프 제거
	void removeSelfLoops();

	//버텍스 병합.
	bool mergeVertices(T first, T second, T new_label);

	//랜덤 버텍스 선택
	T pickRandomVertex() const;
	//랜덤 엣지 선택
	Edge<T> * pickRandomEdge() const;

	//최소 컷.
	int minCut() const;

	//위상 정렬
	vector<T> topologicalSort() const;

	//DFS 탐색
	vector<T> dfs() const;
	vector<T> dfs(T start) const;

	//BFS탐색.
	vector<T> bfs() const;
	vector<T> bfs(T start) const;

	//뛰어넘을 거리
	map<T, unsigned int> hop_distance(T from) const;

	//인접 행렬
	pair<vector<T>, vector<vector<int> > > adjacencyMatrix() const;
	//연결 리스트
	pair<vector<T>, vector<vector<bool> > > connectivityList() const;

	//방향 있음?
	bool isDirected() const;
	//가중치 있음?
	bool isWeighted() const;
	//연결됨?
	bool isConnected() const;
	//순환 없음?
	bool isAcyclic() const;
	//간단함?
	bool isSimple() const;

	//음의 가중치 엣지 있음?
	bool hasNegativeWeightedEdge() const;

	//BFS 최소 경로 
	map<T, pair<T, int> > bfsShortestPath(T source) const;
	//위상 정렬 최소 경로
	map<T, pair<T, int> > topologicalShortestPath(T source) const;
	//다익스트라 최소 경로
	map<T, pair<T, int> > dijkstraShortestPath(T source) const;
	//벨만 포드 최소 경로
	map<T, pair<T, int> > bellmanFordShortestPath(T source) const;

	//최소경로
	map<T, pair<T, int> > shortestPath(T source) const;
	pair<vector<T>, vector<vector<pair<T, int> > > > shortestPath() const;

	//최소 신장 트리
	Graph<T> minimumSpanningTree() const;

	//경로 출력
	void printPath(ostream &out, map<T, pair<T, int> > path) const;
	void printPath(ostream &out, pair<vector<T>, vector<vector<pair<T, int> > > > dist) const;

	//버텍스 반환
	vector<T> getVertices() const;
	//엣지 반환
	vector<Edge<T> *> getEdges() const;

	//버텍스 구성요소 
	vector<vector<T> > getVerticesComponentwise() const;
	//연결된 요소
	vector<Graph<T> *> getConnectedComponents() const;

	friend ostream &operator<<(ostream &out, Graph &g)
	{
		out << (g.isDirected() ? "Directed, " : "Undirected, ");
		out << (g.isWeighted() ? "Weighted, " : "Unweighted, ");
		out << (g.isAcyclic() ? "Acyclic, " : "Cyclic, ");
		out << (g.isConnected() ? "Connected, " : "Disconnected, ");
		out << (g.isSimple() ? "Simple " : "Non simple ");
		out << "graph" << endl;

		for (typename map<T, Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
		{
			out << (*(v->second));
		}

#ifdef DEBUG
		for (typename map<T, Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
		{
			multiset<Vertex *> nbh = v->second->getReverseNodes();

			out << v->second->getLabel() << "(" << nbh.size() << " nodes) --->  ";

			for (typename multiset<Vertex *>::iterator adj = nbh.begin(); adj != nbh.end(); adj++)
			{
				out << (*adj)->getLabel() << ", ";
			}

			out << "\b\b " << endl;
		}
#endif

		return out;
	}

};

/*
Vertex 구현부
*/

template <class T>
Graph<T>::Vertex::Vertex(T label) : label(label)
{
}

template <class T>
Graph<T>::Vertex::~Vertex()
{
	vector<typename multiset<pair<Graph<T>::Vertex *, int> >::iterator> avec;

	for (typename multiset<pair<Graph<T>::Vertex *, int> >::iterator v = adj.begin(); v != adj.end(); v++)
	{
		avec.push_back(v);
	}

	// 나가는 엣지 삭제
	for (int i = avec.size() - 1; i >= 0; i--)
	{
		this->removeEdge(avec[i]->first, avec[i]->second);
	}

	assert(adj.empty());

	vector<typename multiset<Graph<T>::Vertex *>::iterator> vec;

	for (typename multiset<Graph<T>::Vertex *>::iterator v = rev.begin(); v != rev.end(); v++)
	{
		vec.push_back(v);
	}

	// 들어오는 엣지 삭제
	for (int i = vec.size() - 1; i >= 0; i--)
	{
		(*vec[i])->removeEdge(this);
	}

	assert(rev.empty());
}

template <class T>
void Graph<T>::Vertex::setLabel(T label)
{
	this->label = label;
}

template <class T>
T Graph<T>::Vertex::getLabel() const
{
	return label;
}

template <class T>
multiset<pair<typename Graph<T>::Vertex *, int> > Graph<T>::Vertex::getAdjacentNodes() const
{
	return adj;
}

template <class T>
multiset<typename Graph<T>::Vertex *> Graph<T>::Vertex::getReverseNodes() const
{
	return rev;
}

template <class T>
typename multiset<pair<typename Graph<T>::Vertex *, int> >::iterator Graph<T>::Vertex::findAdjacent(Graph<T>::Vertex *dest) const
{
	for (typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if (itr->first == dest)
		{
			return itr;
		}
	}

	return adj.end();
}

template <class T>
void Graph<T>::Vertex::addEdge(Graph<T>::Vertex *dest, int cost)
{
	assert(dest != NULL);

	adj.insert(make_pair(dest, cost));
	dest->rev.insert(this);
}

template <class T>
bool Graph<T>::Vertex::removeEdge(Graph<T>::Vertex *dest, int cost)
{
	assert(dest != NULL);

	typename multiset<pair<Graph<T>::Vertex *, int> >::iterator pos = adj.find(make_pair(dest, cost));

	if (pos == adj.end())
	{
		return false;
	}

	this->adj.erase(pos); // 인접노드에서 단 하나의 엣지 카피를 제거한다.
	dest->rev.erase(dest->rev.find(this)); // 도착지의 역 엣지 카피를 삭제한다. 

	return true;
}

template <class T>
bool Graph<T>::Vertex::removeEdge(Graph<T>::Vertex *dest)
{
	assert(dest != NULL);

	typename multiset<pair<Graph<T>::Vertex *, int> >::iterator pos = findAdjacent(dest);

	if (pos == adj.end())
	{
		return false;
	}

	this->adj.erase(pos); // This is done so that only one copy of the edge is deleted
	dest->rev.erase(dest->rev.find(this));

	return true;
}

template <class T>
void Graph<T>::Vertex::addEdgesInBatch(multiset<pair<Graph<T>::Vertex *, int> > new_adj)
{
	// adj.insert() is not used intentionally because, backword pointers are needed for deletion
	for (typename multiset<pair<Graph<T>::Vertex *, int> >::iterator v = new_adj.begin(); v != new_adj.end(); v++)
	{
		addEdge(v->first, v->second);
	}
}

template <class T>
bool Graph<T>::Vertex::edgeExists(Graph<T>::Vertex *dest, int cost) const
{
	assert(dest != NULL);
	return adj.find(make_pair(dest, cost)) != adj.end();
}

template <class T>
bool Graph<T>::Vertex::edgeExists(Graph<T>::Vertex *dest) const
{
	assert(dest != NULL);
	return findAdjacent(dest) != adj.end();
}

template <class T>
unsigned int Graph<T>::Vertex::countEdge(Graph<T>::Vertex *dest, int cost) const
{
	assert(dest != NULL);
	return adj.count(make_pair(dest, cost));
}

template <class T>
unsigned int Graph<T>::Vertex::countEdge(Graph<T>::Vertex *dest) const
{
	assert(dest != NULL);

	unsigned int count = 0;

	for (typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if (itr->first == dest)
		{
			count++;
		}
	}

	return count;
}

template <class T>
int Graph<T>::Vertex::edgeCost(Graph<T>::Vertex *dest) const
{
	assert(dest != NULL);

	typename multiset<pair<Graph<T>::Vertex *, int> >::iterator pos = findAdjacent(dest);

	return (pos == adj.end() ? (int)INFINITY : pos->second);
}

template <class T>
vector<int> Graph<T>::Vertex::edgeCosts(Graph<T>::Vertex *dest) const
{
	assert(dest != NULL);

	vector<int> res;

	for (typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if (itr->first == dest)
		{
			res.push_back(itr->second);
		}
	}

	return res;
}

template <class T>
int Graph<T>::Vertex::indegree() const
{
	return rev.size();
}

template <class T>
int Graph<T>::Vertex::outdegree() const
{
	return adj.size();
}

template <class T>
bool Graph<T>::Vertex::hasNegativeWeightedEdge() const
{
	for (typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if (itr->second < 0)
		{
			return true;
		}
	}

	return false;
}

template <class T>
void Graph<T>::Vertex::addIncomingEdges(Graph<T>::Vertex *dest)
{
	assert(dest != NULL);

	for (typename multiset<Graph<T>::Vertex *>::iterator v = rev.begin(); v != rev.end(); v++)
	{
		typename multiset<pair<Graph<T>::Vertex *, int> >::iterator fd = (*v)->findAdjacent(this);
		(*v)->addEdge(dest, fd->second);
	}
}

/*
Graph 구현부
*/


template <class T>
Graph<T>::Graph(bool is_directed) : is_directed(is_directed)
{
}

template <class T>
Graph<T>::Graph(const Graph<T> &g)
{
	operator=(g);
}

template <class T>
Graph<T>::~Graph()
{
	for (typename map<T, Vertex *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		//버텍스를 지운다.
		delete v->second;
	}
	//맵 전체를 지운다.
	vertices.clear();
}

template <class T>
void Graph<T>::operator=(const Graph<T> &g)
{
	is_directed = g.is_directed;

	for (typename map<T, Vertex *>::const_iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
	{
		addVertex(v->first);
	}

	for (typename map<T, Vertex *>::const_iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = v->second->getAdjacentNodes();

		for (typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
		{
			// Graph<T>::addEdge() is intentionally not called, because it might cause problems in case of undirected graph
			findVertex(v->first)->addEdge(findVertex(a->first->getLabel()), a->second);
		}
	}
}

template <class T>
Graph<T> Graph<T>::reverse() const
{
	Graph<T> g(is_directed);

	for (typename map<T, Vertex *>::const_iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		g.addVertex(v->first);
	}

	for (typename map<T, Vertex *>::const_iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = v->second->getAdjacentNodes(); // Unfortunately rev cannot be used because it does not contain weight information

		for (typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
		{
			// Graph<T>::addEdge() is intentionally not called, because it might cause problems in case of undirected graph
			g.findVertex(a->first->getLabel())->addEdge(g.findVertex(v->first), a->second);
		}
	}

	return g;
}

template <class T>
typename Graph<T>::Vertex * Graph<T>::findVertex(T label) const
{
	typename map<T, Vertex *>::const_iterator vtx = vertices.find(label);
	return ((vtx == vertices.end()) ? NULL : vtx->second);
}

template <class T>
void Graph<T>::findFinishOrder(T label, stack<T> & finished_vertices, map<T, bool> & visited) const
{
	Vertex *vertex = findVertex(label);
	assert(vertex != NULL);

	multiset<pair<Vertex *, int> > adj = vertex->getAdjacentNodes();

	visited[label] = true;

	for (typename multiset<pair<Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if (!visited[itr->first->getLabel()])
		{
			findFinishOrder(itr->first->getLabel(), finished_vertices, visited);
		}
	}

	finished_vertices.push(label);
}

template <class T>
bool Graph<T>::addOneWayEdge(T head, T tail, int cost)
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);

	// 라벨중 하나라도 없으면.
	if ((hd == NULL) || (tl == NULL))
	{
		return false;
	}

	hd->addEdge(tl, cost);

	return true;
}

template <class T>
int Graph<T>::indegree(T label) const
{
	Vertex *vtx = findVertex(label);
	return ((vtx == NULL) ? -1 : vtx->indegree());
}

template <class T>
int Graph<T>::outdegree(T label) const
{
	Vertex *vtx = findVertex(label);
	return ((vtx == NULL) ? -1 : vtx->outdegree());
}

template <class T>
unsigned int Graph<T>::numVertices() const
{
	return vertices.size();
}

template <class T>
unsigned int Graph<T>::numEdges() const
{
	unsigned int cnt = 0;

	for (typename map<T, typename Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		cnt += itr->second->outdegree();
	}

	return is_directed ? cnt : (cnt >> 1);
}

template <class T>
vector<typename Graph<T>::Vertex *> Graph<T>::findVerticesWithIndegreeZero() const
{
	vector<typename Graph<T>::Vertex *> res;

	for (typename map<T, typename Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if (itr->second->indegree() == 0)
		{
			res.push_back(itr->second);
		}
	}

	return res;
}

template <class T>
bool Graph<T>::addVertex(T label)
{
	// 같은 라벨의 버텍스가 있나?
	if (findVertex(label) != NULL)
	{
		return false;
	}

	Vertex *new_node = new Vertex(label);
	// 메모리 다참.
	assert(new_node != NULL);

	vertices[label] = new_node;

	return true;
} 

template <class T>
bool Graph<T>::removeVertex(T label)
{
	Vertex* node = findVertex(label);

	// 라벨의 버텍스가 없음.
	if (node == NULL)
	{
		return false;
	}

	delete node;
	vertices.erase(label);

	return true;
}

template <class T>
bool Graph<T>::renameVertex(T old_label, T new_label)
{
	//바꿀라벨하고 같음??
	if (old_label == new_label)
	{
		return true;
	}

	//원래 라벨의 버텍스 찾아서
	Vertex *ft = findVertex(old_label);

	//원래 라벨 버텍스가 없거나 새 라벨의 버텍스가 있으면
	if (ft == NULL || findVertex(new_label) != NULL)	
	{
		return false;
	}

	//라벨 재설정 
	ft->setLabel(new_label);
	//원래 라벨 버텍스 삭제
	vertices.erase(old_label);
	//새 라벨 버텍스 추가.
	vertices[new_label] = ft;

	return true;
}

template <class T>
bool Graph<T>::addEdge(T head, T tail, int cost)
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);

	// 버텍스 2개중에 하나라도 없으면.
	if ((hd == NULL) || (tl == NULL))
	{
		return false;
	}

	//헤드쪽에 엣지 추가.
	hd->addEdge(tl, cost);

	//방향성 있음?
	if (!is_directed)
	{
		if (hd != tl)		// 출발지와 도착지가 다름?
		{
			//도착지에도 엣지 추가.
			tl->addEdge(hd, cost);
		}
	}

	return true;
}

template <class T>
bool Graph<T>::removeEdge(T head, T tail, int cost)
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);

	// 버텍스 2개중 하나라도 없음?
	if ((hd == NULL) || (tl == NULL))
	{
		return false;
	}

	bool forward = true, backword = true;

	//출발쪽 엣지 삭제
	forward = hd->removeEdge(tl, cost);

	//방향성 있음?
	if (!is_directed)
	{
		if (hd != tl)		// 출발지랑 도착지 다르면
		{
			//도착지쪽 엣지 삭제
			backword = tl->removeEdge(hd, cost);
		}
	}

	return (forward && backword);
}

template <class T>
bool Graph<T>::edgeExists(T head, T tail, int cost) const
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);

	// One of the lables does not exist
	if ((hd == NULL) || (tl == NULL))
	{
		return false;
	}

	return hd->edgeExists(tl, cost);
}

template <class T>
bool Graph<T>::edgeExists(T head, T tail) const
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);

	//버텍스 2개중에 하나라도 없음?
	if ((hd == NULL) || (tl == NULL))
	{
		return false;
	}

	return hd->edgeExists(tl);
}

template <class T>
vector<int> Graph<T>::edgeCosts(T head, T tail) const
{
	vector<int> empty;

	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);

	// One of the lables does not exist
	if ((hd == NULL) || (tl == NULL))
	{
		return empty;
	}

	return hd->edgeCosts(tl);
}

template <class T>
int Graph<T>::countEdge(T head, T tail, int cost) const
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);

	// One of the lables does not exist
	if ((hd == NULL) || (tl == NULL))
	{
		return -1;
	}

	return hd->countEdge(tl, cost);
}

template <class T>
int Graph<T>::countEdge(T head, T tail) const
{
	Vertex * hd = findVertex(head);
	Vertex * tl = findVertex(tail);

	// One of the lables does not exist
	if ((hd == NULL) || (tl == NULL))
	{
		return -1;
	}

	return hd->countEdge(tl);
}

template <class T>
bool Graph<T>::pathExists(T start, T end) const
{
	Vertex *st = findVertex(start);
	Vertex *ed = findVertex(end);

	if ((st == NULL) || (ed == NULL))
	{
		return false;
	}

	vector<T> intermediate = dfs(start);

	return find(intermediate.begin(), intermediate.end(), end) != intermediate.end();
}

template <class T>
void Graph<T>::removeSelfLoops()
{
	for (typename map<T, Graph<T>::Vertex *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		while (edgeExists(v->second->getLabel(), v->second->getLabel()))
		{
			v->second->removeEdge(v->second);
		}
	}
}

template <class T>
vector<T> Graph<T>::topologicalSort() const
{
	if (!is_directed)
	{
		throw strdup(NOT_A_DIRECTED_GRAPH);
	}

	vector<Vertex *> l = findVerticesWithIndegreeZero();

	if (l.size() == 0)
	{
		throw strdup(NOT_AN_ACYCLIC_GRAPH);
	}

	queue<Vertex *> q;
	vector<T> res;
	const unsigned int sz = vertices.size();

	// Create and initialize table
	map<T, unsigned int> indegree_table;
	for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		indegree_table[itr->first] = itr->second->indegree();
	}

	for (int i = l.size() - 1; i >= 0; i--)
	{
		q.push(l[i]);
	}

	while (res.size() < sz)
	{
		if (q.empty())
		{
			throw strdup(NOT_AN_ACYCLIC_GRAPH);
		}

		Vertex *ft = q.front();
		q.pop();

		res.push_back(ft->getLabel());

		multiset<pair<Graph<T>::Vertex *, int> > adj = ft->getAdjacentNodes();
		for (typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
		{
			indegree_table[a->first->getLabel()]--;

			if (indegree_table[a->first->getLabel()] == 0)
			{
				q.push(a->first);
			}
		}
	}

	return res;
}

template <class T>
vector<T> Graph<T>::dfs() const
{
	vector<T> v;

	if (vertices.size() == 0)
	{
		return v;
	}

	return dfs(vertices.begin()->first);
}

template <class T>
vector<T> Graph<T>::dfs(T start) const
{
	vector<T> res;
	Vertex *vtx = findVertex(start);

	if (vtx == NULL)
	{
		return res;
	}

	// Create and initialize table
	map<T, bool> visited;
	for (typename map<T, typename Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}

	stack<Vertex *> stk;

	stk.push(vtx);

	while (!stk.empty())
	{
		vtx = stk.top();
		stk.pop();

		if (!visited[vtx->getLabel()])
		{
			res.push_back(vtx->getLabel());
			visited[vtx->getLabel()] = true;

			multiset<pair<Graph<T>::Vertex *, int> > adj = vtx->getAdjacentNodes();
			for (typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
			{
				stk.push(a->first);
			}
		}
	}

	return res;
}

template <class T>
vector<T> Graph<T>::bfs() const
{
	vector<T> v;

	if (vertices.size() == 0)
	{
		return v;
	}

	return bfs(vertices.begin()->first);
}

template <class T>
vector<T> Graph<T>::bfs(T start) const
{
	vector<T> res;
	Vertex *vtx = findVertex(start);

	if (vtx == NULL)
	{
		return res;
	}

	// Create and initialize table
	map<T, bool> visited;
	for (typename map<T, typename Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}

	queue<Vertex *> q;

	q.push(vtx);

	while (!q.empty())
	{
		vtx = q.front();
		q.pop();

		if (!visited[vtx->getLabel()])
		{
			res.push_back(vtx->getLabel());
			visited[vtx->getLabel()] = true;

			multiset<pair<Graph<T>::Vertex *, int> > adj = vtx->getAdjacentNodes();
			for (typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
			{
				q.push(a->first);
			}
		}
	}

	return res;
}

template <class T>
map<T, unsigned int> Graph<T>::hop_distance(T from) const
{
	map<T, unsigned int> res;
	Vertex *vtx = findVertex(from);

	if (vtx == NULL)
	{
		return res;
	}

	// Create and initialize table
	map<T, bool> visited;
	for (typename map<T, typename Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}

	queue<pair<Vertex *, unsigned int> > q;

	q.push(make_pair(vtx, 0));

	while (!q.empty())
	{
		pair<Vertex *, unsigned int> pr = q.front();
		q.pop();

		if (!visited[pr.first->getLabel()])
		{
			res[pr.first->getLabel()] = pr.second;
			visited[pr.first->getLabel()] = true;

			multiset<pair<Graph<T>::Vertex *, int> > adj = pr.first->getAdjacentNodes();
			for (typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
			{
				q.push(make_pair(a->first, pr.second + 1));
			}
		}
	}

	return res;
}

template <class T>
pair<vector<T>, vector<vector<int> > > Graph<T>::adjacencyMatrix() const
{
	vector<T> v;
	vector<vector<int> > res;

	if (isSimple())
	{
		for (typename map<T, Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			v.push_back(itr->first);
		}

		for (typename vector<T>::const_iterator i = v.begin(); i != v.end(); i++)
		{
			vector<int> l;

			for (typename vector<T>::const_iterator j = v.begin(); j != v.end(); j++)
			{
				if (*i == *j)
				{
					l.push_back(0);
				}
				else
				{
					l.push_back(findVertex(*i)->edgeCost(findVertex(*j)));
				}
			}

			res.push_back(l);
		}
	}

	return make_pair(v, res);
}

template <class T>
pair<vector<T>, vector<vector<bool> > > Graph<T>::connectivityList() const
{
	vector<T> v;
	vector<vector<bool> > res;

	for (typename map<T, Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		v.push_back(itr->first);
	}

	for (typename vector<T>::const_iterator i = v.begin(); i != v.end(); i++)
	{
		vector<bool> l;

		for (typename vector<T>::const_iterator j = v.begin(); j != v.end(); j++)
		{
			l.push_back((*i == *j) || edgeExists(*i, *j));
		}

		res.push_back(l);
	}

	return make_pair(v, res);
}

template <class T>
bool Graph<T>::isDirected() const
{
	return is_directed;
}

template <class T>
bool Graph<T>::isWeighted() const
{
	for (typename map<T, Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = itr->second->getAdjacentNodes();
		for (typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
		{
			if (a->second != 1)
			{
				return true;
			}
		}
	}

	return false;
}

template <class T>
bool Graph<T>::isConnected() const
{
	if (numVertices() <= 1)
	{
		return true;
	}

	if (is_directed)
	{
		pair<vector<T>, vector<vector<bool> > > pr = connectivityList();
		vector<vector<bool> > curr_matrix = pr.second;
		vector<vector<bool> > prev_matrix;
		const unsigned int n = numVertices();

		for (int k = 0; k < n; k++)
		{
			prev_matrix = curr_matrix;

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					curr_matrix[i][j] = prev_matrix[i][j] || (prev_matrix[i][k] && prev_matrix[k][j]);
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!curr_matrix[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}

	// Undirected graph
	T src = vertices.begin()->first;
	vector<T> traversed = dfs(src);

	return traversed.size() == vertices.size();
}

template <class T>
bool Graph<T>::isAcyclic() const
{
	if (numVertices() == 0)
	{
		return true;
	}

	if (is_directed)
	{
		// TODO: This is not the right way of detecting cycle in directed graph
		try
		{
			topologicalSort();
		}
		catch (char *e)
		{
			if (strcmp(e, NOT_AN_ACYCLIC_GRAPH) == 0)
			{
				return false;
			}
		}

		return true;
	}

	// Undirected graph
	if (numEdges() > numVertices() - 1)
	{
		return false;
	}

	Graph<T> g = *this;
	DisjointSet<T> s;

	for (typename map<T, Graph<T>::Vertex *>::const_iterator itr = g.vertices.begin(); itr != g.vertices.end(); itr++)
	{
		s.create(itr->first);
	}

	for (typename map<T, Graph<T>::Vertex *>::const_iterator itr = g.vertices.begin(); itr != g.vertices.end(); itr++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = itr->second->getAdjacentNodes();

		for (typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator it = adj.begin(); it != adj.end(); it++)
		{
			if (s.connected(itr->second->getLabel(), it->first->getLabel()))
			{
				return false;
			}

			s.join(itr->second->getLabel(), it->first->getLabel());
			itr->second->removeEdge(it->first);
			it->first->removeEdge(itr->second);
		}
	}

	return true;
}

template <class T>
bool Graph<T>::isSimple() const
{
	for (typename map<T, Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if (edgeExists(itr->first, itr->first))	// Self loops
		{
			return false;
		}

		for (typename map<T, Graph<T>::Vertex *>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
		{
			if (countEdge(itr->first, it->first) > 1)
			{
				return false;
			}
		}
	}

	return true;
}

template <class T>
bool Graph<T>::hasNegativeWeightedEdge() const
{
	for (typename map<T, Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if (itr->second->hasNegativeWeightedEdge())
		{
			return true;
		}
	}

	return false;
}

template <class T>
map<T, pair<T, int> > Graph<T>::bfsShortestPath(T source) const
{
	map<T, pair<T, int> > res;

	if (!isDirected() && !isWeighted())
	{
		Vertex *vtx = findVertex(source);

		if (vtx != NULL)
		{
			// Create and initialize table
			map<T, bool> visited;
			for (typename map<T, typename Graph<T>::Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
			{
				visited[itr->first] = false;
			}

			queue<pair<Vertex *, pair<T, int> > > q;

			q.push(make_pair(vtx, make_pair(source, 0)));

			while (!q.empty())
			{
				pair<Vertex *, pair<T, int> > pr = q.front();
				q.pop();

				if (!visited[pr.first->getLabel()])
				{
					res[pr.first->getLabel()] = pr.second;
					visited[pr.first->getLabel()] = true;

					multiset<pair<Graph<T>::Vertex *, int> > adj = pr.first->getAdjacentNodes();
					for (typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
					{
						q.push(make_pair(a->first, make_pair(pr.first->getLabel(), pr.second.second + 1)));
					}
				}
			}

			for (typename map<T, bool>::const_iterator itr = visited.begin(); itr != visited.end(); itr++)
			{
				if (!itr->second)
				{
					res[itr->first] = make_pair(itr->first, (int)INFINITY);
				}
			}
		}
	}

	return res;
}

template <class T>
map<T, pair<T, int> > Graph<T>::topologicalShortestPath(T source) const
{
	map<T, pair<T, int> > res;

	if (isDirected() && isAcyclic())
	{
		if (findVertex(source) != NULL)
		{
			vector<T> ord = topologicalSort();
			const unsigned int sz = ord.size();
			int pos = -1;

			assert(sz == numVertices());

			for (int i = 0; i < sz; i++)
			{
				if (ord[i] == source)
				{
					pos = i;
					break;
				}
			}

			assert(pos != -1);

			for (int i = 0; i < sz; i++)
			{
				res[ord[i]] = make_pair(ord[i], (int)INFINITY);
			}

			res[ord[pos]] = make_pair(ord[pos], 0);

			for (int i = pos; i < sz; i++)
			{
				Vertex *cur = findVertex(ord[i]);

				assert(cur != NULL);

				multiset<pair<Graph<T>::Vertex *, int> > adj = cur->getAdjacentNodes();
				for (typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
				{
					// First condition is checked to avoid overflow
					if ((res[ord[i]].second != (int)INFINITY) && (res[ord[i]].second + a->second < res[a->first->getLabel()].second))
					{
						res[a->first->getLabel()] = make_pair(ord[i], res[ord[i]].second + a->second);
					}
				}
			}
		}
	}

	return res;
}

template <class T>
map<T, pair<T, int> > Graph<T>::dijkstraShortestPath(T source) const
{
	map<T, pair<T, int> > res;

	if (!hasNegativeWeightedEdge())
	{
		if (findVertex(source) != NULL)
		{
			map<T, bool> visited;

			for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
			{
				res[itr->first] = make_pair(itr->first, (int)INFINITY);
				visited[itr->first] = false;
			}

			res[source] = make_pair(source, 0);

			while (1)
			{
				// TODO: Try to use min heap
				int min_dist = (int)INFINITY;
				T curr;

				for (typename map<T, pair<T, int> >::const_iterator itr = res.begin(); itr != res.end(); itr++)
				{
					if (!visited[itr->first] && (itr->second.second < min_dist))
					{
						min_dist = itr->second.second;
						curr = itr->first;
					}
				}

				if (min_dist == (int)INFINITY)
				{
					break;
				}

				visited[curr] = true;

				assert(findVertex(curr) != NULL);

				multiset<pair<Vertex *, int> > adj = findVertex(curr)->getAdjacentNodes();
				for (typename multiset<pair<Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
				{
					if (res[curr].second + a->second < res[a->first->getLabel()].second)
					{
						res[a->first->getLabel()] = make_pair(curr, res[curr].second + a->second);
					}
				}
			}
		}
	}

	return res;
}

template <class T>
map<T, pair<T, int> > Graph<T>::bellmanFordShortestPath(T source) const
{
	map<T, pair<T, int> > emp, res;
	int iter = numVertices() - 1;

	for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		res[itr->first] = make_pair(itr->first, (int)INFINITY);
	}

	res[source] = make_pair(source, 0);

	while (iter--)
	{
		for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			assert(itr->second != NULL);

			multiset<pair<Vertex *, int> > adj = itr->second->getAdjacentNodes();
			for (typename multiset<pair<Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
			{
				// First condition is checked to avoid overflow
				if ((res[itr->first].second != (int)INFINITY) && (res[itr->first].second + a->second < res[a->first->getLabel()].second))
				{
					res[a->first->getLabel()] = make_pair(itr->first, res[itr->first].second + a->second);
				}
			}
		}
	}

	for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		assert(itr->second != NULL);

		multiset<pair<Vertex *, int> > adj = itr->second->getAdjacentNodes();
		for (typename multiset<pair<Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
		{
			// First condition is checked to avoid overflow
			if ((res[itr->first].second != (int)INFINITY) && (res[itr->first].second + a->second < res[a->first->getLabel()].second))
			{
				// Graph contains negative cycle(s)
				return emp;
			}
		}
	}

	return res;
}

template <class T>
map<T, pair<T, int> > Graph<T>::shortestPath(T source) const
{
	map<T, pair<T, int> > res;

	// Invalid source vertex
	if (findVertex(source) == NULL)
	{
		return res;
	}

	res = bfsShortestPath(source);

	if (res.size() != 0)
	{
		return res;
	}

	res = topologicalShortestPath(source);

	if (res.size() != 0)
	{
		return res;
	}

	res = dijkstraShortestPath(source);

	if (res.size() != 0)
	{
		return res;
	}

	// If the graph has negative cycles, it will be handled by Bellman-Ford algorithm
	return bellmanFordShortestPath(source);
}

template <class T>
pair<vector<T>, vector<vector<pair<T, int> > > > Graph<T>::shortestPath() const
{
	if (isSimple())
	{
		pair<vector<T>, vector<vector<int> > > pr = adjacencyMatrix();
		vector<vector<int> > curr_matrix = pr.second;
		vector<vector<int> > prev_matrix;
		vector<vector<pair<T, int> > > path;
		const unsigned int n = numVertices();

		for (int i = 0; i < n; i++)
		{
			vector<pair<T, int> > tmp;

			for (int j = 0; j < n; j++)
			{
				tmp.push_back(make_pair(pr.first[j], (int)INFINITY));
			}

			path.push_back(tmp);
		}

		for (int k = 0; k < n; k++)
		{
			prev_matrix = curr_matrix;

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					// First two conditions are to avoid overflow
					if ((prev_matrix[i][k] == (int)INFINITY) || (prev_matrix[k][j] == (int)INFINITY) || (prev_matrix[i][j] <= prev_matrix[i][k] + prev_matrix[k][j]))
					{
						curr_matrix[i][j] = prev_matrix[i][j];
						path[i][j] = make_pair(path[i][j].first, curr_matrix[i][j]);
					}
					else
					{
						curr_matrix[i][j] = prev_matrix[i][k] + prev_matrix[k][j];
						path[i][j] = make_pair(pr.first[k], curr_matrix[i][j]);
					}
				}
			}
		}

		return make_pair(pr.first, path);
	}

	// Not a simple graph
	return make_pair(vector<T>(), vector<vector<pair<T, int> > >());
}

template <class T>
void Graph<T>::printPath(ostream &out, map<T, pair<T, int> > path) const
{
	for (typename map<T, pair<T, int> >::const_iterator itr = path.begin(); itr != path.end(); itr++)
	{
		out << itr->first << " =====> ";

		if (itr->second.second == (int)INFINITY)
		{
			out << "(Unreachable)" << endl;
		}
		else
		{
			stack<T> stk;

			T curr = itr->first;
			T prev;

			do
			{
				prev = curr;
				stk.push(curr);
				curr = path[curr].first;
			} while (prev != curr);

			while (!stk.empty())
			{
				out << stk.top() << ", ";
				stk.pop();
			}

			out << "\b\b (" << itr->second.second << ")" << endl;
		}
	}
}

template <class T>
void Graph<T>::printPath(ostream &out, pair<vector<T>, vector<vector<pair<T, int> > > > dist) const
{
	const int n = numVertices();

	assert(dist.first.size() == n);

	out << "Path: " << endl;

	for (int i = 0; i < n; i++)
	{
		out << "\t" << i + 1;
	}

	out << endl;

	for (int i = 0; i < n; i++)
	{
		out << "____________";
	}

	out << endl;

	for (int i = 0; i < n; i++)
	{
		out << dist.first[i] << "(" << i + 1 << ") | ";

		for (int j = 0; j < n; j++)
		{
			if (dist.second[i][j].second == (int)INFINITY)
			{
				out << "\t---";
			}
			else
			{
				out << "\t" << dist.second[i][j].first;
			}
		}

		out << endl;
	}

	out << "Distance: " << endl;

	for (int i = 0; i < n; i++)
	{
		out << "\t" << i + 1;
	}

	out << endl;

	for (int i = 0; i < n; i++)
	{
		out << "____________";
	}

	out << endl;

	for (int i = 0; i < n; i++)
	{
		out << dist.first[i] << "(" << i + 1 << ") | ";

		for (int j = 0; j < n; j++)
		{
			if (dist.second[i][j].second == (int)INFINITY)
			{
				out << "\tinf";
			}
			else
			{
				out << "\t" << dist.second[i][j].second;
			}
		}

		out << endl;
	}
}

template <class T>
vector<T> Graph<T>::getVertices() const
{
	vector<T> res;

	for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		res.push_back(itr->first);
	}

	return res;
}

template <class T>
vector<Edge<T> *> Graph<T>::getEdges() const
{
	vector<Edge<T> *> res;

	for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		multiset<pair<Vertex *, int> > adj = itr->second->getAdjacentNodes();

		for (typename multiset<pair<Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
		{
			res.push_back(new Edge<T>(itr->first, a->first->getLabel(), a->second));
		}
	}

	return res;
}

template <class T>
vector<vector<T> > Graph<T>::getVerticesComponentwise() const
{
	vector<vector<T> > res;
	map<T, bool> visited;

	if (isDirected())	// Kosaraju's algorithm for finding Strongly Connected Components (SCCs) in a directed graph
	{
		stack<T> finished_vertices;
		map<T, bool> visited;

		for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			visited[itr->first] = false;
		}

		for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			if (!visited[itr->first])
			{
				findFinishOrder(itr->first, finished_vertices, visited);
			}
		}

		Graph<T> rev_graph = reverse();

		for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			visited[itr->first] = false;
		}

		while (!finished_vertices.empty())
		{
			T curr = finished_vertices.top();
			finished_vertices.pop();

			if (!visited[curr])
			{
				vector<T> vlist = rev_graph.dfs(curr);

				for (int i = vlist.size() - 1; i >= 0; i--)
				{
					rev_graph.removeVertex(vlist[i]); // Done to avoid revisiting
					visited[vlist[i]] = true;
				}

				res.push_back(vlist);
			}
		}

		return res;
	}

	for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		visited[itr->first] = false;
	}

	for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		if (!visited[itr->first])
		{
			vector<T> vlist = dfs(itr->first);

			for (int i = vlist.size() - 1; i >= 0; i--)
			{
				visited[vlist[i]] = true;
			}

			res.push_back(vlist);
		}
	}

	return res;
}

template <class T>
vector<Graph<T> *> Graph<T>::getConnectedComponents() const
{
	vector<Graph<T> *> res;
	vector<vector<T> > vertices_compwise = getVerticesComponentwise();

	for (typename vector<vector<T> >::const_iterator i = vertices_compwise.begin(); i != vertices_compwise.end(); i++)
	{
		Graph<T> *g = new Graph<T>(is_directed);

		for (typename vector<T>::const_iterator j = i->begin(); j != i->end(); j++)
		{
			g->addVertex(*j);
		}

		for (typename vector<T>::const_iterator j = i->begin(); j != i->end(); j++)
		{
			multiset<pair<Vertex *, int> > adj = findVertex(*j)->getAdjacentNodes();

			for (typename multiset<pair<Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
			{
				// Graph::addEdge() is intentionally not called here
				Vertex *src = g->findVertex(*j);
				Vertex *dest = g->findVertex(a->first->getLabel());

				if (src != NULL && dest != NULL)
				{
					src->addEdge(dest, a->second);
				}
			}
		}

		res.push_back(g);
	}

	return res;
}

template <class T>
Graph<T> Graph<T>::minimumSpanningTree() const
{
	Graph<T> t(is_directed);

	if (!isDirected() && isConnected())
	{
		if (vertices.size() != 0)
		{
			map<T, bool> visited;

			for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
			{
				visited[itr->first] = false;
				t.addVertex(itr->first);
			}

			visited[vertices.begin()->first] = true;

			while (1)
			{
				int min_dist = (int)INFINITY;
				pair<T, T> curr;

				for (typename map<T, Vertex *>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
				{
					if (visited[itr->first])
					{
						multiset<pair<Vertex *, int> > adj = itr->second->getAdjacentNodes();
						for (typename multiset<pair<Vertex *, int> >::const_iterator a = adj.begin(); a != adj.end(); a++)
						{
							if (!visited[a->first->getLabel()] && a->second < min_dist)
							{
								min_dist = a->second;
								curr = make_pair(itr->first, a->first->getLabel());
							}
						}
					}
				}

				if (min_dist == (int)INFINITY)
				{
					break;
				}

				visited[curr.second] = true;
				t.addEdge(curr.first, curr.second, min_dist);
			}
		}
	}

	return t;
}

template <class T>
bool Graph<T>::mergeVertices(T first, T second, T new_label)
{
	Vertex * ft = findVertex(first);
	Vertex * sd = findVertex(second);
	Vertex * nw = findVertex(new_label);

	// One of the lables does not exist
	if ((ft == NULL) || (sd == NULL))
	{
		return false;
	}

	// Cannot merge a vertex with itself
	if (ft == sd)
	{
		return false;
	}

	// Node with same name already exists (and it does not match with one of the nodes being merged
	if ((nw != NULL) && (ft != nw) && (sd != nw))
	{
		return false;
	}

	// Rename the vertex
	assert(renameVertex(first, new_label));

	// Add outgoing edges from second vertex
	ft->addEdgesInBatch(sd->getAdjacentNodes());

	// Add incoming edges from second vertex
	sd->addIncomingEdges(ft);

	// Erase entry from the list of vertices
	vertices.erase(second);

	// Delete the vertex
	delete sd;

	return true;
}

template <class T>
T Graph<T>::pickRandomVertex() const
{
	int rnd = rand() % vertices.size();
	typename map<T, Graph<T>::Vertex *>::const_iterator it(vertices.begin());
	advance(it, rnd);

	return it->first;
}

template <class T>
Edge<T> * Graph<T>::pickRandomEdge() const
{
	Vertex *hd;
	multiset<pair<Graph<T>::Vertex *, int> > adj;
	int cnt = 0;
	const int double_num_vertices = 4 * vertices.size();

	do
	{
		hd = findVertex(pickRandomVertex());
		adj = hd->getAdjacentNodes();
		cnt++;
	} while ((adj.size() == 0) && (cnt < double_num_vertices));

	// Adjacency list empty
	if (adj.size() == 0)
	{
		return NULL;
	}

	int rnd = rand() % adj.size();
	typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator it(adj.begin());
	advance(it, rnd);

	Vertex *tl = it->first;

	return new Edge<T>(hd->getLabel(), tl->getLabel(), it->second);
}

template <class T>
int Graph<T>::minCut() const
{
	if (is_directed)
	{
		return -1;
	}

	int rep = 2000;
	int min = vertices.size() + 2;

	for (int i = 0; i < rep; i++)
	{
		Graph<T> g = *this;

		srand(i);

		g.removeSelfLoops();

		while (g.vertices.size() > 2)
		{
			Edge<T> * rn = g.pickRandomEdge();

			if (rn == NULL)
			{
				break;
			}

			g.mergeVertices(rn->src, rn->dest, rn->src);
			g.removeSelfLoops();
		}

		if (g.vertices.size() == 2)
		{
			int loc_min = g.vertices.begin()->second->getAdjacentNodes().size();

			if (loc_min < min)
			{
				min = loc_min;
			}
		}
	}

	return min;
}
