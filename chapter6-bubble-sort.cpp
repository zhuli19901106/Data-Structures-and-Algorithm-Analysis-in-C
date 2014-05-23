// My implementation for bubble sort.
#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int> &v)
{
	int n, i, j;
	int val;
	
	n = (int)v.size();
	for (i = 0; i < n; ++i) {
		for (j = n - 1; j > i; --j) {
			if (v[j - 1] > v[j]) {
				val = v[j - 1];
				v[j - 1] = v[j];
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
		bubbleSort(v);
		for (i = 0; i < n; ++i) {
			cout << v[i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}