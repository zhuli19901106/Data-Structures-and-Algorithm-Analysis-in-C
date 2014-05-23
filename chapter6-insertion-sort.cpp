// My implementation for insertion sort.
#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int> &v)
{
	int i, j, n;
	int val;
	
	n = (int)v.size();
	if (n <= 1) {
		return;
	}
	
	for (i = 1; i < n; ++i) {
		val = v[i];
		for (j = i - 1; j >= 0 && v[j] > val; --j) {
			v[j + 1] = v[j];
		}
		v[j + 1] = val;
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
		insertionSort(v);
		for (i = 0; i < n; ++i) {
			cout << v[i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}