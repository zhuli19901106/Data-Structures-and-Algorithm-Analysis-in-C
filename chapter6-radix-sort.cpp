// My implementation for radix sort.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void radixSort(vector<int> &v)
{
	int n, i, j, k;
	int max_val;
	vector<vector<int> > rad;
	
	n = (int)v.size();
	if (n <= 1) {
		return;
	}
	
	// This algorithm works for negative integers.
	max_val = abs(v[0]);
	for (i = 1; i < n; ++i) {
		max_val = max(abs(v[i]), max_val);
	}
	
	int exp = 1;
	while (max_val / exp >= 10) {
		exp *= 10;
	}
	
	rad.resize(19);
	int iexp = 1;
	while (true) {
		for (i = 0; i < n; ++i) {
			rad[v[i] / iexp % 10 + 9].push_back(v[i]);
		}
		
		k = 0;
		for (i = 0; i < 19; ++i) {
			int n2 = (int)rad[i].size();
			for (j = 0; j < n2; ++j) {
				v[k++] = rad[i][j];
			}
			rad[i].clear();
		}
		
		if (iexp == exp) {
			break;
		} else {
			iexp *= 10;
		}
	}
	rad.clear();
}

int main()
{
	vector<int> v;
	int n, i;
	
	while (cin >> n && n > 0) {
		v.resize(n);
		for (i = 0; i < n; ++i) {
			cin >> v[i];
		}
		radixSort(v);
		for (i = 0; i < n; ++i) {
			cout << v[i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}