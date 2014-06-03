// A simple illustration for weighted shortest path. Graph represented by adjacency matrix.
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INFINITY = 1000000000;

void weightedShortestPath(const vector<vector<int> > &graph, 
	vector<int> &dist, vector<bool> &reachable)
{
	// The minimal distances from 0th vertice to others.
	int n;
	int i, j;
	
	n = (int)graph.size();
	dist.resize(n);
	reachable.resize(n);

	if (n < 1) {
		return;
	}
	
	for (i = 0; i < n; ++i) {
		reachable[i] = false;
	}
	
	queue<int> q;
	
	dist[0] = 0;
	reachable[0] = true;
	
	q.push(0);
	while (!q.empty()) {
		i = q.front();
		q.pop();
		for (j = 0; j < n; ++j) {
			if (graph[i][j] == INFINITY || (reachable[j] && 
				dist[i] + graph[i][j] >= dist[j])) {
				continue;
			}
			dist[j] = dist[i] + graph[i][j];
			if (!reachable[j]) {
				q.push(j);
			}
			reachable[j] = true;
		}
	}
}

int main()
{
	vector<vector<int> > graph;
	vector<int> dist;
	vector<bool> reachable;
	int n;
	int nk;
	int i, j;
	int tmp, tmp_dist;
	
	while (cin >> n && n > 0) {
		graph.resize(n);
		for (i = 0; i < n; ++i) {
			graph[i].resize(n, INFINITY);
		}
		
		for (i = 0; i < n; ++i) {
			cin >> nk;
			for (j = 0; j < nk; ++j) {
				cin >> tmp >> tmp_dist;
				graph[i][tmp] = tmp_dist;
			}
		}
		
		weightedShortestPath(graph, dist, reachable);
		
		for (i = 0; i < n; ++i) {
			cout << i << ": ";
			if (reachable[i]) {
				cout << dist[i] << endl;
			} else {
				cout << "Unreachable" << endl;
			}
		}
		
		for (i = 0; i < n; ++i) {
			graph[i].clear();
		}
		graph.clear();
	}
	
	return 0;
}