// My implementation for selection sort.
#include <iostream>
#include <vector>
using namespace std;

static inline int leftChild(int n)
{
	return n * 2 + 1;
}

static inline int rightChild(int n)
{
	return n * 2 + 2;
}

static inline void swap(int &x, int &y)
{
	int tmp;
	
	tmp = x;
	x = y;
	y = tmp;
}

static inline int max(const int &x, const int &y)
{
	return x > y ? x : y;
}

static void percolateDown(vector<int> &v, int i, int n)
{
	if (n <= 1 || i < 0 || i >= n) {
		return;
	}
	int max_val;

	while (leftChild(i) < n) {
		if (leftChild(i) == n - 1) {
			max_val = v[leftChild(i)];
		} else {
			max_val = max(v[leftChild(i)], v[rightChild(i)]);
		}
		if (v[i] < max_val) {
			if (max_val == v[leftChild(i)]) {
				swap(v[i], v[leftChild(i)]);
				i = leftChild(i);
			} else {
				swap(v[i], v[rightChild(i)]);
				i = rightChild(i);
			}
		} else {
			break;
		}
	}
}

void heapSort(vector<int> &v)
{
	int n;
	int i;
	
	n = (int)v.size();
	for (i = (n - 1) / 2; i >= 0; --i) {
		percolateDown(v, i, n);
	}
	
	int val;
	for (i = 0; i < n - 1; ++i) {
		val = v[0];
		v[0] = v[n - 1 - i];
		percolateDown(v, 0, n - 1 - i);
		v[n - 1 - i] = val;
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
		heapSort(v);
		for (i = 0; i < n; ++i) {
			cout << v[i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}