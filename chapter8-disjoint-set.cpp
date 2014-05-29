// My implementation for  disjoint set.
#include <vector>
using namespace std;

int findRoot(const vector<int> &dj, int x)
{
	int k, r;
	
	r = x;
	while (r != dj[r]) {
		r = dj[r];
	}
	
	k = x;
	while (k != r) {
		x = dj[x];
		dj[k] = r;
		k = x;
	}
	
	return r;
}

void unionSet(vector<int> &dj, int x, int y)
{
	int n = (int)dj.size();
	
	if (x == y) {
		return;
	}
	
	dj[x] = y;
	findRoot(x);
}

int main()
{
	return 0;
}