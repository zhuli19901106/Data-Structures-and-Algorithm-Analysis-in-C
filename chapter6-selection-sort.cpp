// My implementation for selection sort.
#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int> &v)
{
	int n, i, j;
	int val;

	n = (int)v.size();
	for (i = 0; i < n; ++i) {
		for (j = i + 1; j < n; ++j) {
			if (v[i] > v[j]) {
				val = v[i];
				v[i] = v[j];
				v[j] = val;
			}
		}
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
		selectionSort(v);
		for (i = 0; i < n; ++i) {
			cout << v[i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}