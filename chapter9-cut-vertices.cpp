// My implementation for cut vertex detection on undirected graph.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void findCutVertex(const vector<vector<bool> > &graph, int idx, const int n,
	int &counter, vector<int> &num, vector<int> &low, vector<int> &parent,
	vector<bool> &result)
{
	int i;
	
	low[idx] = num[idx] = counter++;
	for (i = 0; i < n; ++i) {
		if (!graph[idx][i]) {
			continue;
		}
		
		if (num[i] < 0) {
			// Unvisited vertex
			parent[i] = idx;
			findCutVertex(graph, i, n, counter, num, low, parent, result);
			if (low[i] >= num[idx]) {
				result[idx] = true;
			}
			low[idx] = min(low[idx], low[i]);
		} else if (parent[idx] != i) {
			// Visited vertex
			low[idx] = min(low[idx], num[i]);
		}
	}
}

void cutVertexDetection(const vector<vector<bool> > &graph, 
	vector<bool> &is_cut_vertex)
{
	// Cut vertex detection for undirected graph.
	int n;
	
	n = (int)graph.size();
	is_cut_vertex.resize(n, false);
	
	if (n == 1) {
		is_cut_vertex[0] = true;
		return;
	}
	
	vector<int> parent;
	vector<int> num;
	vector<int> low;
	int counter;
	
	parent.resize(n, -1);
	num.resize(n, -1);
	low.resize(n, -1);
	counter = 0;
	findCutVertex(graph, 0, n, counter, num, low, parent, is_cut_vertex);

	// The root node must be checked separately.
	counter = 0;
	for (int i = 1; i < n; ++i) {
		if (parent[i] == 0) {
			++counter;
		}
	}
	is_cut_vertex[0] = (counter > 1);
	
	parent.clear();
	num.clear();
	low.clear();
}

int main()
{
	vector<vector<bool> > graph;
	vector<bool> is_cut_vertex;
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
				graph[i][tmp] = graph[tmp][i] = true;
			}
		}
		
		cutVertexDetection(graph, is_cut_vertex);
		cout << "The following vertices are cut vertices:" << endl;
		cout << '{';
		for (i = 0; i < n; ++i) {
			if (is_cut_vertex[i]) {
				cout << i << ' ';
			}
		}
		cout << '}' << endl;
		
		for (i = 0; i < n; ++i) {
			graph[i].clear();
		}
		graph.clear();
		is_cut_vertex.clear();
	}
	
	return 0;
}