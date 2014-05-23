// My implementation for merge sort.
#include <iostream>
#include <vector>
using namespace std;

void mergeSortRecursive(vector<int> &v, vector<int> &temp, int left, int right)
{
	if (right - left < 1) {
		return;
	}
	int mid = left + (right - left) / 2;
	mergeSortRecursive(v, temp, left, mid);
	mergeSortRecursive(v, temp, mid + 1, right);
	
	int i, j, k;
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right) {
		if (v[i] < v[j]) {
			temp[k++] = v[i++];
		} else {
			temp[k++] = v[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = v[i++];
	}
	while (j <= right) {
		temp[k++] = v[j++];
	}
	for (i = left; i <= right; ++i) {
		v[i] = temp[i];
	}
}

void mergeSort(vector<int> &v)
{
	int n;
	vector<int> temp;

	n = (int)v.size();
	temp.resize(n);
	mergeSortRecursive(v, temp, 0, n - 1);
	temp.clear();
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
		mergeSort(v);
		for (i = 0; i < n; ++i) {
			cout << v[i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}