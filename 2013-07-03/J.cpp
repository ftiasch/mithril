#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100;

int n, r;

struct Point {
	double x, y;

	Point() : x(0), y(0) {}
	Point(double x, double y) : x(x), y(y) {}

	double len() const {
		return sqrt(x * x + y * y);
	}
};

Point operator - (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

Point polygon[N];

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

double det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

const double EPS = 1e-9;
const double PI = acos(-1);

double area2(Point pa, Point pb) {
	if (pa.len() < pb.len()) {
		swap(pa, pb);
	}
	if (pb.len() < EPS) {
		return 0;
	}
	double a, b, c, B, C, sinB, cosB, sinC, cosC, S, h, theta;
	a = pb.len();
	b = pa.len();
	c = (pb - pa).len();
	cosB = dot(pb, pb - pa) / a / c;
	sinB = fabs(det(pb, pb - pa) / a / c);
	cosC = dot(pa, pb) / a / b;
	sinC = fabs(det(pa, pb) / a / b);
	B = atan2(sinB, cosB);
	C = atan2(sinC, cosC);
	if (a > r) {
		S = C / 2 * r * r;
		h = a * b * sinC / c;
		if (h < r && B < PI / 2)  {
			S -= acos(h / r) * r * r - h * sqrt(r * r - h * h);
		}
	} else if (b > r) {
		theta = PI - B - asin(sinB / r * a);
		S = .5 * a * r * sin(theta) + (C - theta) / 2 * r * r;
	} else {
		S = .5 * sinC * a * b;
	}
	return S;
}

double signum(double x) {
	return x < -EPS ? -1 : x > EPS;
}

int main() {
	scanf("%d%d", &n, &r);
	for (int i = 0; i < n; ++ i) {
		int x, y;
		scanf("%d%d", &x, &y);
		polygon[i] = Point(x, y);
	}
	double answer = 0;
	for (int i = 0; i < n; ++ i) {
		Point pa = polygon[i];
		Point pb = polygon[(i + 1) % n];
		answer += area2(pa, pb) * signum(det(pa, pb));
	}
	printf("%.10f\n", fabs(answer));
	return 0;
}
