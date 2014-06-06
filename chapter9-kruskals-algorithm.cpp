// My implementation for Prim's Algorithm, for minimum spanning tree problem.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INFINITY = 1000000000;

struct Edge {
	int x;
	int y;
	int cost;
	Edge(int _x = 0, int _y = 0, int _cost = 0): x(_x), y(_y), cost(_cost) {};
};

bool comparator(const Edge &e1, const Edge &e2) {
	return e1.cost < e2.cost;
}

int findRoot(vector<int> &dj, int x)
{
	int r, k;
	
	r = x;
	while (r != dj[r]) {
		r = dj[r];
	}
	
	// Path compression speeds up the disjoint set.
	k = x;
	while (x != r) {
		x = dj[x];
		dj[k] = r;
		k = x;
	}
	
	return r;
}

int kruskalsAlgorithm(const vector<vector<int> > &graph)
{
	// Kruskal's Algorithm for weighted undirected graph.
	int n;
	n = (int)graph.size();
	if (n < 2) {
		return 0;
	}
	
	// Disjoint set
	vector<int> dj;
	vector<Edge> edges;
	int rx, ry;
	int i, j;
	
	for (i = 0; i < n; ++i) {
		for (j = i + 1; j < n; ++j) {
			if (graph[i][j] == INFINITY) {
				continue;
			}
			edges.push_back(Edge(i, j, graph[i][j]));
		}
	}
	sort(edges.begin(), edges.end(), comparator);

	dj.resize(n);
	for (i = 0; i < n; ++i) {
		dj[i] = i;
	}
	
	int edge_count = n - 1;
	int min_cost = 0;
	int ec = (int)edges.size();
	for (i = 0; i < ec; ++i) {
		rx = findRoot(dj, edges[i].x);
		ry = findRoot(dj, edges[i].y);
		if (rx == ry) {
			continue;
		}
		dj[rx] = ry;
		findRoot(dj, edges[i].x);
		
		min_cost += edges[i].cost;
		--edge_count;
		if (edge_count == 0) {
			break;
		}
	}
	edges.clear();
	
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
		
		min_cost = kruskalsAlgorithm(graph);
		
		cout << "The weighted sum of minimum spanning tree is " << min_cost << "." << endl;
		
		for (i = 0; i < n; ++i) {
			graph[i].clear();
		}
		graph.clear();
	}
	
	return 0;
}