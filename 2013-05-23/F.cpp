#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int iter = 40;
const double EPS = 1e-8;

inline int signum(double x)
{
    if (x < -EPS) {
        return -1;
    }
    return x > EPS;
}

struct Point
{
    double x, y;
    Point(){}
    Point(double x, double y):x(x), y(y){
    }
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    void show() {
        printf("(%.3f, %.3f)", x, y);
    }
    double norm() {
        return sqrt(x * x + y * y);
    }
};

bool operator <(const Point &a, const Point &b)
{
    return signum(a.x - b.x) < 0 || signum(a.x - b.x) == 0 && signum(a.y - b.y) < 0;
}

Point operator +(const Point &a, const Point &b)
{
    return Point(a.x + b.x, a.y + b.y);
}

Point operator -(const Point &a, const Point &b)
{
    return Point(a.x - b.x, a.y - b.y);
}

Point operator *(const Point &a, const double &b)
{
    return Point(a.x * b, a.y * b);
}

Point operator /(const Point &a, const double &b)
{
    return Point(a.x / b, a.y / b);
}

double det(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

bool cross(Point a, Point b, Point c, Point d, Point &x)
{
    double s1 = det(c - a, b - a);
    double s2 = det(d - a, b - a);
    if (signum(s1 - s2) == 0) {
        return false;
    }
    x = (c * s2 - d * s1) / (s2 - s1);
    return true;
}

bool pointInSegment(Point o, Point a, Point b)
{
    //return signum(det(o - a, b - a)) == 0 && signum(dot(o - a, o - b)) <= 0;
    Point dir = b - a;
    double length = dir.norm();
    if (signum(length) == 0) {
        return signum((o - a).norm()) == 0;
    }
    if (signum(det(o - a, dir) / length) != 0) {
        return false;
    }
    Point l = o - a, r = o - b;
    if (signum(l.norm()) == 0 || signum(r.norm()) == 0) {
        return true;
    }
    return signum(dot(l, r) / l.norm()) <= 0;
}

bool pointInPoly(Point cp, Point a[], int n)
{
    int wn = 0;
    for (int i = 0; i < n; ++ i) {
        if (pointInSegment(cp, a[i], a[i + 1])) {
            return true;
        }
        int k = signum(det(a[i + 1] - a[i], cp - a[i]));
        int d1 = signum(a[i].y - cp.y);
        int d2 = signum(a[i + 1].y - cp.y);
        if (k > 0 && d1 <= 0 && d2 > 0) {
            ++ wn;
        }
        if (k < 0 && d2 <=0 && d1 > 0) {
            -- wn;
        }
    }
    return wn != 0;
}

bool SegmentCrossPoly(Point s, Point t, Point a[], int n)
{
    vector<Point> event;
    event.push_back(s);
    event.push_back(t);
    for (int i = 0; i < n; ++ i) {
        Point x;
        if (cross(s, t, a[i], a[i + 1], x) && pointInSegment(x, a[i], a[i + 1]) && pointInSegment(x, s, t)) {
            event.push_back(x);
        }
        if (pointInSegment(a[i], s, t)) {
            event.push_back(a[i]);
        }
    }
    sort(event.begin(), event.end());
    for (int i = 1; i < event.size(); ++ i) {
        Point x = (event[i - 1] + event[i]) / 2;
        if (!pointInPoly(x, a, n)) {
//x.show();
            return true;
        }
    }
    return false;
}

const int maxn = 100;

Point poly[maxn + 1];

int main()
{
    for (int test = 1, n; scanf("%d", &n) == 1 && n; ++ test) {
        for (int i = 0; i < n; ++ i) {
            poly[i].read();
        }
        poly[n] = poly[0];
        double answer = 0;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < i; ++ j) {
                if (!SegmentCrossPoly(poly[i], poly[j], poly, n)) {
                    Point dir = poly[i] - poly[j];
                    double length = dir.norm();
                    double maxi = dir.norm(), mini = 0;
                    dir = dir / length;
                    
                    double left = -1e4, right = 1e4;
                    for (int k = 0; k < n ;++ k) {
                        Point inter;
                        if (cross(poly[k], poly[k + 1], poly[i], poly[j], inter)) {
                            if (pointInSegment(inter, poly[k], poly[k + 1])) {
                                double project = dot(dir, inter - poly[j]);
                                if (project > length + EPS) {
                                    right = min(right, project);
                                } else if (project < -EPS){
                                    left = max(left, project);
                                }
                            }
                        }
                    }
                    
                    Point x = poly[j] + dir * left;
                    if (left > -1e4 && pointInPoly((x + poly[j]) / 2, poly, n)) {
                        mini = left;
                    }
                    x = poly[j] + dir * right;
                    if (right < 1e4 && pointInPoly((x + poly[i]) / 2, poly, n)) {
                        maxi = right;
                    }
                    
                    answer = max(answer, maxi - mini);
                }
            }
        }
        printf("Case %d: %.10f\n", test, answer);
    }
    return 0;
}

