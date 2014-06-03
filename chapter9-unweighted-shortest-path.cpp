// A simple illustration for unweighted shortest path. Graph represented by adjacency matrix.
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void unweightedShortestPath(const vector<vector<bool> > &graph, 
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
			if (!graph[i][j] || reachable[j]) {
				continue;
			}
			dist[j] = dist[i] + 1;
			reachable[j] = true;
			q.push(j);
		}
	}
}

int main()
{
	vector<vector<bool> > graph;
	vector<int> dist;
	vector<bool> reachable;
	int n;
	int nk;
	int i, j;
	int tmp;
	
	while (cin >> n && n > 0) {
		graph.resize(n);
		for (i = 0; i < n; ++i) {
			graph[i].resize(n, false);
		}
		
		for (i = 0; i < n; ++i) {
			cin >> nk;
			for (j = 0; j < nk; ++j) {
				cin >> tmp;
				graph[i][tmp] = true;
			}
		}
		
		unweightedShortestPath(graph, dist, reachable);
		
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