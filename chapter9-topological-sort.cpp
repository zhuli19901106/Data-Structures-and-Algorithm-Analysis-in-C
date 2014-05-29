// A simple illustration for topological sort. Graph represented by adjacency matrix.
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
	vector<vector<bool> > graph;
	queue<int> q;
	vector<int> indegree;
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
		
		indegree.resize(n, 0);
		
		for (i = 0; i < n; ++i) {
			cin >> nk;
			for (j = 0; j < nk; ++j) {
				cin >> tmp;
				graph[i][tmp] = true;
				++indegree[tmp];
			}
		}
		
		for (i = 0; i < n; ++i) {
			if (indegree[i] == 0) {
				q.push(i);
				break;
			}
		}
		
		while (!q.empty()) {
			tmp = q.front();
			q.pop();
			order.push_back(tmp);
			for (i = 0; i < n; ++i) {
				if (graph[tmp][i] && (--indegree[i] == 0)) {
					q.push(i);
				}
			}
		}
		
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
		indegree.clear();
		order.clear();
	}
	
	return 0;
}