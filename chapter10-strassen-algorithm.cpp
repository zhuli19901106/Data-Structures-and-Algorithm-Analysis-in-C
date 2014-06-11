// My implementation for Strassen Algorithm. Matrix size is limited to powers of 2 only.
#include <iostream>
#include <vector>
using namespace std;

void getSubmatrix(const vector<vector<int> > &m, vector<vector<int> > &sub, int part)
{
	int n = (int)m.size();
	int i, j;
	int n1 = n / 2;
	
	int top = part / 2 * n1;
	int left = part % 2 * n1;
	for (i = 0; i < n1; ++i) {
		for (j = 0; j < n1; ++j) {
			sub[i][j] = m[top + i][left + j];
		}
	}
}

void addMatrix(const vector<vector<int> > &a, const vector<vector<int> > &b, 
	vector<vector<int> > &c, int n)
{
	int i, j;
	
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void subtractMatrix(const vector<vector<int> > &a, const vector<vector<int> > &b, 
	vector<vector<int> > &c, int n)
{
	int i, j;
	
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			c[i][j] = a[i][j] - b[i][j];
		}
	}
}

void setSubmatrix(const vector<vector<int> > &sub, vector<vector<int> > &m, int part)
{
	int n = (int)m.size();
	int i, j;
	int n1 = n / 2;
	
	int top = part / 2 * n1;
	int left = part % 2 * n1;
	for (i = 0; i < n1; ++i) {
		for (j = 0; j < n1; ++j) {
			m[top + i][left + j] = sub[i][j];
		}
	}
}

void matrixMultiplicationRecursive(const vector<vector<int> > &a, 
	const vector<vector<int> > &b, vector<vector<int> > &c, int n)
{
	if (n == 1) {
		c[0][0] = a[0][0] * b[0][0];
		return;
	}
	
	int i;
	int n1 = n / 2;
	
	vector<vector<int> > aa[4];
	vector<vector<int> > bb[4];
	
	for (i = 0; i < 4; ++i) {
		aa[i].resize(n1, vector<int>(n1));
		bb[i].resize(n1, vector<int>(n1));
	}
	
	for (i = 0; i < 4; ++i) {
		getSubmatrix(a, aa[i], i);
		getSubmatrix(b, bb[i], i);
	}
	
	vector<vector<int> > x, y;
	vector<vector<int> > m[7];
	
	x.resize(n1, vector<int>(n1));
	y.resize(n1, vector<int>(n1));
	for (i = 0; i < 7; ++i) {
		m[i].resize(n1, vector<int>(n1));
	}
	
	subtractMatrix(aa[1], aa[3], x, n1);
	addMatrix(bb[2], bb[3], y, n1);
	matrixMultiplicationRecursive(x, y, m[0], n1);
	
	addMatrix(aa[0], aa[3], x, n1);
	addMatrix(bb[0], bb[3], y, n1);
	matrixMultiplicationRecursive(x, y, m[1], n1);
	
	subtractMatrix(aa[0], aa[2], x, n1);
	addMatrix(bb[0], bb[1], y, n1);
	matrixMultiplicationRecursive(x, y, m[2], n1);
	
	addMatrix(aa[0], aa[1], x, n1);
	matrixMultiplicationRecursive(x, bb[3], m[3], n1);
	
	subtractMatrix(bb[1], bb[3], y, n1);
	matrixMultiplicationRecursive(aa[0], y, m[4], n1);
	
	subtractMatrix(bb[2], bb[0], y, n1);
	matrixMultiplicationRecursive(aa[3], y, m[5], n1);
	
	addMatrix(aa[2], aa[3], x, n1);
	matrixMultiplicationRecursive(x, bb[0], m[6], n1);
	
	addMatrix(m[0], m[1], x, n1);
	subtractMatrix(x, m[3], x, n1);
	addMatrix(x, m[5], x, n1);
	setSubmatrix(x, c, 0);
	
	addMatrix(m[3], m[4], x, n1);
	setSubmatrix(x, c, 1);
	
	addMatrix(m[5], m[6], x, n1);
	setSubmatrix(x, c, 2);
	
	subtractMatrix(m[1], m[2], x, n1);
	addMatrix(x, m[4], x, n1);
	subtractMatrix(x, m[6], x, n1);
	setSubmatrix(x, c, 3);

	for (i = 0; i < 4; ++i) {
		aa[i].clear();
		bb[i].clear();
	}
	for (i = 0; i < 7; ++i) {
		m[i].clear();
	}
	x.clear();
	y.clear();
}

void matrixMultiplication(const vector<vector<int> > &a, 
	const vector<vector<int> > &b, vector<vector<int> > &c)
{
	int n = (int)a.size();
	
	matrixMultiplicationRecursive(a, b, c, n);
}

int main()
{
	int n;
	int i, j;
	vector<vector<int> > a, b, c;
	
	while (cin >> n && n > 0) {
		a.resize(n, vector<int>(n));
		b.resize(n, vector<int>(n));
		c.resize(n, vector<int>(n));
		
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				cin >> a[i][j];
			}
		}

		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				cin >> b[i][j];
			}
		}
		
		matrixMultiplication(a, b, c);

		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				cout << c[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;

		a.clear();
		b.clear();
		c.clear();
	}
	
	return 0;
}