// My implementation for shell sort.
#include <iostream>
#include <vector>
using namespace std;

void shellSort(vector<int> &v)
{
	int n, i, j;
	int tmp;
	int increment;
	
	n = (int)v.size();
	for (increment = n / 2; increment > 0; increment /= 2) {
		for (i = increment; i < n; ++i) {
			tmp = v[i];
			for (j = i; j >= increment && v[j - increment] > tmp; j -= increment) {
				v[j] = v[j - increment];
			}
			v[j] = tmp;
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
		shellSort(v);
		for (i = 0; i < n; ++i) {
			cout << v[i] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}