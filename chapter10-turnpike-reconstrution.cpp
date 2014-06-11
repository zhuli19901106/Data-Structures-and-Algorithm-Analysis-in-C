// Turnpike reconstruction problem.
//	Description:
//		Given n * (n - 1) / 2 distances, find out if you can determine the 
//			relative coordinates of n points.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int myabs(int x)
{
	return x > 0 ? x : -x;
}

bool turnpikeReconstruction(int idx, vector<int> &x, map<int, int> &dist_set, 
	const int far)
{
	if (idx == 0) {
		return true;
	}
	
	int cur_n;
	int cur_far;
	int i;
	map<int, int>::iterator it;
	
	cur_n = (int)x.size();
	cur_far = dist_set.rbegin()->first;
	for (i = 0; i < cur_n; ++i) {
		it = dist_set.find(myabs(cur_far - x[i]));
		if (it == dist_set.end() || it->second == 0) {
			break;
		}
		--it->second;
		if (it->second == 0) {
			dist_set.erase(it);
		}
	}
	if (i == cur_n) {
		x.push_back(cur_far);
		if (turnpikeReconstruction(idx - 1, x, dist_set, far)) {
			return true;
		}
		x.pop_back();
	}
	cur_n = i;
	for (i = 0; i < cur_n; ++i) {
		++dist_set[myabs(cur_far - x[i])];
	}
	
	cur_n = (int)x.size();
	cur_far = dist_set.rbegin()->first;
	for (i = 0; i < cur_n; ++i) {
		it = dist_set.find(myabs(far - cur_far - x[i]));
		if (it == dist_set.end() || it->second == 0) {
			break;
		}
		--it->second;
		if (it->second == 0) {
			dist_set.erase(it);
		}
	}
	if (i == cur_n) {
		x.push_back(far - cur_far);
		if (turnpikeReconstruction(idx - 1, x, dist_set, far)) {
			return true;
		}
		x.pop_back();
	}
	cur_n = i;
	for (i = 0; i < cur_n; ++i) {
		++dist_set[myabs(far - cur_far - x[i])];
	}
	
	return false;
}

int main()
{
	int i;
	int n, n2;
	vector<int> x;
	int dist;
	map<int, int> dist_set;
	int far;
	
	while (cin >> n2 && n2 > 0) {
		for (i = 0; i < n2; ++i) {
			cin >> dist;
			++dist_set[dist];
		}
		n = (int)sqrt(n2 * 2.0) + 1;
		far = dist_set.rbegin()->first;
		--dist_set[far];
		if (dist_set.rbegin()->second == 0) {
			dist_set.erase(far);
		}
		
		x.push_back(0);
		x.push_back(far);
		if (!turnpikeReconstruction(n - 2, x, dist_set, far)) {
			cout << "No solution." << endl;
		} else {
			sort(x.begin(), x.end());
			for (i = 0; i < n; ++i) {
				cout << x[i] << ' ';
			}
			cout << endl;
		}
		
		x.clear();
		dist_set.clear();
	}
	
	return 0;
}