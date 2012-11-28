#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1024;
const int PART = 100;
const int LIMIT = 50;
const double PI = acos(-1.0);

const double EPS = 1e-9;

int sign(double x) {
	return x < -EPS ? -1 : x > EPS;
}

struct Point {
	double x, y;

	Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

};

bool operator < (const Point &a, const Point &b) {
	return sign(a.x - b.x) < 0 || sign(a.x - b.x) == 0 && sign(a.y - b.y) < 0;
}

Point operator -(const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

istream &operator >>(istream &in, Point &p) {
	return in >> p.x >> p.y;
}

Point get_polar(double theta) {
	return Point(cos(theta), sin(theta));
}

double det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

int n;
Point points[N];

double get_max(double theta) {
	Point lambda = get_polar(theta);
	double ret = dot(points[0], lambda);
	for (int i = 0; i < n; ++ i) {
		ret = max(ret, dot(points[i], lambda));
	}
	return ret;
}

double get_area(double theta) {
	return abs(get_max(theta) + get_max(theta + PI)) 
		* abs(get_max(theta + PI / 2) + get_max(theta - PI / 2));
}

int stack[N << 1];

bool check(const Point &a, const Point &b, const Point &c) {
	return sign(det(b - a, c - b)) > 0;
}

int main() {
	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 0; i < n; ++ i) {
			cin >> points[i];
		}
		sort(points, points + n);
		int top = 0;
		for (int i = 0; i < n; ++ i) {
			while (top > 1 && !check(points[stack[top - 2]], points[stack[top - 1]], points[i])) {
				top --;
			}
			stack[top ++] = i;
		}
		int last = top;
		for (int i = n - 1; i >= 0; -- i) {
			while (top > last && !check(points[stack[top - 2]], points[stack[top - 1]], points[i])) {
				top --;
			}
			stack[top ++] = i;
		}
		double answer = 1e100;
		for (int i = 0; i + 1 < top; ++ i) {
			Point p = points[stack[i + 1]] - points[stack[i]];
			double a = atan2(p.y, p.x);
			answer = min(answer, get_area(a));
		}
		printf("%.3f\n", answer);
	}
	return 0;
}
