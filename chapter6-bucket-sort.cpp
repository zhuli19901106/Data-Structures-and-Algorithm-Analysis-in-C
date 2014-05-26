// My implementation for radix sort.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void bucketSort(vector<int> &v)
{
	const int BUCKET_SIZE = 1000;
	const int BUCKET_NUM = 1000;
	vector<int> buckets[BUCKET_NUM];
	
	int n, i, j, k;
	
	n = (int)v.size();
	for (i = 0; i < n; ++i) {
		buckets[v[i] / BUCKET_SIZE % BUCKET_NUM].push_back(v[i]);
	}
	
	k = 0;
	for (i = 0; i < BUCKET_NUM; ++i) {
		if (buckets[i].size() > 1) {
			sort(buckets[i].begin(), buckets[i].end());
		}
		for (j = 0; j < (int)buckets[i].size(); ++j) {
			v[k++] = buckets[i][j];
		}
		buckets[i].clear();
	}
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
		bucketSort(v);
		for (i = 0; i < n; ++i) {
			cout << v[i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}