// My implementation for Prim's Algorithm, for minimum spanning tree problem.
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INFINITY = 1000000000;

struct Edge {
	int x;
	int y;
	int cost;
	Edge(int _x = 0, int _y = 0, int _cost = 0): x(_x), y(_y), cost(_cost) {};
};

struct GreaterFunctor {
	bool operator () (const Edge &e1, const Edge &e2) {
		return e1.cost > e2.cost;
	}
};

int primsAlgorithm(const vector<vector<int> > &graph)
{
	// Prim's Algorithm for weighted undirected graph.
	
	int n;
	n = (int)graph.size();
	if (n < 2) {
		return 0;
	}

	int i;
	// Minimal heap, the top is smallest.
	priority_queue<Edge, vector<Edge>, GreaterFunctor> pq;
	vector<bool> visited;
	int visited_count;
	int min_cost;
	
	visited.resize(n, false);
	
	// Start constructing the tree from 0th vertex.
	min_cost = 0;
	visited[0] = true;
	for (i = 1; i < n; ++i) {
		if (graph[0][i] == INFINITY) {
			continue;
		}
		pq.push(Edge(0, i, graph[0][i]));
	}
	visited_count = n - 1;
	
	Edge e;
	while (!pq.empty()) {
		e = pq.top();
		pq.pop();
		if (visited[e.y]) {
			continue;
		}
		min_cost += e.cost;
		visited[e.y] = true;
		--visited_count;
		if (visited_count == 0) {
			break;
		}
		
		for (i = 0; i < n; ++i) {
			if (i == e.y || graph[e.y][i] == INFINITY || visited[i]) {
				continue;
			}
			pq.push(Edge(e.y, i, graph[e.y][i]));
		}
	}
	
	while (!pq.empty()) {
		pq.pop();
	}
	
	return min_cost;
}

int main()
{
	vector<vector<int> > graph;
	int n;
	int nk;
	int i, j;
	int tmp, tmp_dist;
	int min_cost;
	
	while (cin >> n && n > 0) {
		graph.resize(n);
		for (i = 0; i < n; ++i) {
			graph[i].resize(n, INFINITY);
		}
		
		for (i = 0; i < n; ++i) {
			cin >> nk;
			for (j = 0; j < nk; ++j) {
				cin >> tmp >> tmp_dist;
				graph[i][tmp] = graph[tmp][i] = tmp_dist;
			}
		}
		
		min_cost = primsAlgorithm(graph);
		
		cout << "The weighted sum of minimum spanning tree is " << min_cost << "." << endl;
		
		for (i = 0; i < n; ++i) {
			graph[i].clear();
		}
		graph.clear();
	}
	
	return 0;
}