// My first practice on maximum flow problem. This is an implementation using Edmonds-Karp Algorithm.
// A simple illustration for weighted shortest path. Graph represented by adjacency matrix.
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INFINITY = 1000000000;

bool findAugmentPath(const vector<vector<int> > &rg, vector<int> &path, 
	const int start, const int end)
{
	// Find an augment path with BFS.
	queue<int> q;
	vector<int> back_trace;
	int n;
	int i;
	
	n = rg.size();
	back_trace.resize(n, -1);
	
	int tmp;
	
	back_trace[start] = start;
	q.push(start);
	while (!q.empty()) {
		if (back_trace[end] >= 0) {
			// An augment path is found.
			break;
		}
		tmp = q.front();
		q.pop();
		for (i = 0; i < n; ++i) {
			if (rg[tmp][i] == INFINITY) {
				continue;
			}
			if (i == tmp || back_trace[i] >= 0) {
				continue;
			}
			back_trace[i] = tmp;
			q.push(i);
		}
	}
	
	if (q.empty()) {
		return false;
	}
	
	path.clear();
	tmp = end;
	while (tmp != start) {
		path.push_back(tmp);
		tmp = back_trace[tmp];
	}
	path.push_back(tmp);
	reverse(path.begin(), path.end());
	
	while (!q.empty()) {
		q.pop();
	}
	back_trace.clear();
	
	return true;
}

void addFlow(vector<vector<int> > &rg, const vector<int> &path, const int flow)
{
	int i;
	
	for (i = 0; i < (int)path.size() - 1; ++i) {
		if (rg[path[i]][path[i + 1]] == flow) {
			rg[path[i]][path[i + 1]] = INFINITY;
		} else {
			rg[path[i]][path[i + 1]] -= flow;
		}
		
		if (rg[path[i + 1]][path[i]] == INFINITY) {
			rg[path[i + 1]][path[i]] = flow;
		} else {
			rg[path[i + 1]][path[i]] += flow;
		}
	}
}

int maximumFlow(const vector<vector<int> > &graph, int start, int end)
{
	// The residual graph
	vector<vector<int> > rg;
	vector<int> path;
	int flow, maximum_flow;
	int i;
	
	if (graph.size() < 2 || start == end) {
		return 0;
	}
	
	rg = graph;
	maximum_flow = 0;
	while (findAugmentPath(rg, path, start, end)) {
		flow = rg[path[0]][path[1]];
		for (i = 1; i < (int)path.size() - 1; ++i) {
			flow = min(flow, rg[path[i]][path[i + 1]]);
		}
		addFlow(rg, path, flow);
		maximum_flow += flow;
	}
	
	return maximum_flow;
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
	int maximum_flow;
	int start, end;
	
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
		
		cin >> start >> end;
		maximum_flow = maximumFlow(graph, start, end);
		
		cout << "Maximum flow is " << maximum_flow << "." << endl;
		
		for (i = 0; i < n; ++i) {
			graph[i].clear();
		}
		graph.clear();
	}
	
	return 0;
}