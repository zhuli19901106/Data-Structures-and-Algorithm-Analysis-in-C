// Ordering matrix multiplication, a typical dynamic programming problem.
//	Description:
//		You have a list of matrices M1, M2, ..., Mn to multiply.
//		Each with dimension (X1, Y1), (X2, Y2), ..., (Xn, Yn)
//		Of course, Yi == X(i + 1)
//		You can arrange the order of matrix multiplications, 
//			to achieve minimal number of multiplications.
//		For example: A * B * C can be A * (B * C) or (A * B) * C, 
//			they might require different number of multiplications.
#include <iostream>
#include <vector>
using namespace std;

const int INF = 1000000000;

int orderingMatrixMultiplication(const vector<int> &dimension)
{
	int n = (int)dimension.size() - 1;
	vector<vector<int> > dp;
	
	dp.resize(n, vector<int>(n, INF));
	
	int i, j, k;
	
	for (i = 0; i < n; ++i) {
		dp[i][i] = 0;
	}
	
	for (i = 1; i < n; ++i) {
		for (j = 0; j + i < n; ++j) {
			for (k = j; k < j + i; ++k) {
				dp[j][j + i] = min(dp[j][j + i], dp[j][k] + dp[k + 1][j + i]
					+ dimension[j] * dimension[k + 1] * dimension[j + i + 1]);
			}
		}
	}
	
	int result = dp[0][n - 1];
	dp.clear();
	
	return result;
}

int main()
{
	int i;
	int n;
	vector<int> v;
	
	while (cin >> n && n > 0) {
		v.resize(n + 1);
		for (i = 0; i < n + 1; ++i) {
			cin >> v[i];
		}
		cout << orderingMatrixMultiplication(v) << endl;
	}
	
	return 0;
}