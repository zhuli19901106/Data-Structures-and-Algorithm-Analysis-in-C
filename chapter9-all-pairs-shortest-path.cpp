// A simple illustration for all pairs shortest path using Floyd Algorithm.
#include <iostream>
#include <vector>
using namespace std;

const int INFINITY = 1000000000;

void floydAlgorithm(const vector<vector<int> > &graph, 
	vector<vector<int> > &dist)
{
	int n;
	int i, j, k;
	
	n = (int)graph.size();
	dist.resize(n);
	for (i = 0; i < n; ++i) {
		dist[i].resize(n, INFINITY);
	}
	
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			dist[i][j] = graph[i][j];
		}
	}
	
	for (k = 0; k < n; ++k) {
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (dist[i][k] + dist[k][j] >= dist[i][j]) {
					continue;
				}
				dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
}

int main()
{
	vector<vector<int> > graph;
	vector<vector<int> > dist;
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
		
		floydAlgorithm(graph, dist);
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				cout << "[" << i << "][" << j << "]: ";
				if (dist[i][j] < INFINITY) {
					cout << dist[i][j] << endl;
				} else {
					cout << "Unreachable" << endl;
				}
			}
		}
		
		for (i = 0; i < n; ++i) {
			graph[i].clear();
		}
		graph.clear();
		
		for (i = 0; i < n; ++i) {
			dist[i].clear();
		}
		dist.clear();
	}
	
	return 0;
}