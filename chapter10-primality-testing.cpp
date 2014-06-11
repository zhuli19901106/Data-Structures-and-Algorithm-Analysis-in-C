// Primality testing using Fermat's Lesser Theorem.
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int primalityTest(int a, int i, int n)
{
	// a is randomly chosen between (1, n) to test the primality of n.
	int x, y;
	
	if (i == 0) {
		return 1;
	}
	
	x = primalityTest(a, i / 2, n);
	if (x == 0) {
		// x == 0 means n is composite.
		// recursively return false
		return 0;
	}
	
	y = (x * x) % n;
	if (i % 2 != 0) {
		y = (y * a) % n;
	}
	
	return y;
}

bool isPrime(const int n)
{
	if (n < 2) {
		return false;
	} else if (n < 4) {
		return true;
	}
	
	const int NUM_OF_TRIALS = 10;
	int i = 0;
	while (i < NUM_OF_TRIALS) {
		if (primalityTest(2 + rand() % (n - 3), n - 1, n) != 1) {
			return false;
		}
		++i;
	}
	
	return true;
}

int main()
{
	srand((unsigned int)time(nullptr));
	int n;
	
	while (cin>> n && n > 0) {
		cout << (isPrime(n) ? "Yes": "No") << endl;
	}
	
	return 0;
}