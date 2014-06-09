// Divide-and-conquer solution for Closest Pair of Points problem.
// This piece of code is also accepted on Zhejiang University Online Judge
// Problem ID 2107.
// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=1107
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

struct Point {
	double x;
	double y;
	Point(double _x = 0.0, double _y = 0.0): x(_x), y(_y) {}
};

bool comparatorX(const Point &a, const Point &b)
{
	if (a.x == b.x) {
		return a.y < b.y;
	} else {
		return a.x < b.x;
	}
}

bool comparatorY(const Point &a, const Point &b)
{
	if (a.y == b.y) {
		return a.x < b.x;
	} else {
		return a.y < b.y;
	}
}

double dist(const Point &a, const Point &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double closestPairOfPointsRecursive(const vector<Point> &points, int left, 
	int right)
{
	if (right - left + 1 == 2) {
		return dist(points[left], points[left + 1]);
	} else if (right - left + 1 == 3) {
		return min(dist(points[left], points[left + 1]), 
			min(dist(points[left + 1], points[left + 2]), 
			dist(points[left], points[left + 2])));
	}
	
	int mid = left + (right - left) / 2;
	double delta = min(closestPairOfPointsRecursive(points, left, mid), 
		closestPairOfPointsRecursive(points, mid + 1, right));
	vector<Point> p;

	int i, j;
	i = mid;
	while (i >= left && points[i].x > points[mid].x - delta) {
		p.push_back(points[i]);
		--i;
	}
	
	i = mid + 1;
	while (i <= right && points[i].x < points[mid].x + delta) {
		p.push_back(points[i]);
		++i;
	}

	int np;
	double result = delta;

	sort(p.begin(), p.end(), comparatorY);
	np = (int)p.size();
	for (i = 0; i < np; ++i) {
		for (j = i + 1; j < np; ++j) {
			if (p[j].y - p[i].y > result) {
				break;
			}
			result = min(result, dist(p[i], p[j]));
		}
	}
	p.clear();
	
	return result;
}

double closestPairOfPoints(vector<Point> &points)
{
	int n = points.size();
	sort(points.begin(), points.end(), comparatorX);
	return closestPairOfPointsRecursive(points, 0, n - 1);
}

int main()
{
	vector<Point> points;
	int n;
	int i;
	
	while (scanf("%d", &n) == 1 && n > 0) {
		points.resize(n);
		for (i = 0; i < n; ++i) {
			scanf("%lf%lf", &points[i].x, &points[i].y);
		}
		// printf("%.2f\n", closestPairOfPoints(points) / 2.0);
		printf("%.2f\n", closestPairOfPoints(points));
	}
	
	return 0;
}