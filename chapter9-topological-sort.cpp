// A simple illustration for topological sort. Graph represented by adjacency matrix.
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void topologicalSort(const vector<vector<bool> > &graph, vector<int> &order)
{
	int n;
	int i, j;
	vector<int> indegree;
	queue<int> q;
	
	n = (int)graph.size();
	indegree.resize(n, 0);
	
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			if (graph[i][j]) {
				++indegree[j];
			}
		}
	}
	
	for (i = 0; i < n; ++i) {
		if (indegree[i] == 0) {
			q.push(i);
			break;
		}
	}
	
	while (!q.empty()) {
		i = q.front();
		q.pop();
		order.push_back(i);
		for (j = 0; j < n; ++j) {
			if (graph[i][j] && (--indegree[j] == 0)) {
				q.push(j);
			}
		}
	}
	
	indegree.clear();
}

int main()
{
	vector<vector<bool> > graph;
	vector<int> order;
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
		
		topologicalSort(graph, order);
		
		if ((int)order.size() == n) {
			for (i = 0; i < n; ++i) {
				cout << order[i] << ' ';
			}
			cout << endl;
		} else {
			cout << "The graph has a cycle." << endl;
		}
		
		for (i = 0; i < n; ++i) {
			graph[i].clear();
		}
		graph.clear();
		order.clear();
	}
	
	return 0;
}