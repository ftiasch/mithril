#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

const int EPS = 1e-9;

int signum(int x) { return x < 0 ? -1 : x > 0; }

struct Point {
    int x, y;

    Point(int x = 0.0, int y = 0.0) : x(x), y(y) { }
    Point &operator +=(const Point &o) { x += o.x, y += o.y; return *this; }
    Point &operator -=(const Point &o) { x -= o.x, y -= o.y; return *this; }

    bool on(const Point&, const Point &) const;
};

istream &operator >>(istream &in, Point &p) { return in >> p.x >> p.y; }


Point operator +(Point a, const Point &b) { return a += b; }
Point operator -(Point a, const Point &b) { return a -= b; }

int det(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }

bool Point::on(const Point &a, const Point &b) const {
    Point p = *this;
    return signum(det(p - a, p - b)) == 0;
}

bool has_intersection(const Point &a, const Point &b, const Point &c, const Point &d) {
    Point p = b - a;
    Point q = d - c;
    return signum(det(p, q)) != 0;
}

const int N = 100;

int w, n;
pair <Point, Point> lines[N];
vector <Point> intersections;

#define SIZE(v) (int)(v).size()
#define UNIQUE(v) sort((v).begin(), (v).end()); (v).erase(unique((v).begin(), (v).end()), (v).end())
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

bool useful[N];

int main() {
    cin >> w >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> lines[i].first >> lines[i].second;
    }
    memset(useful, 0, sizeof(useful));
    int useful_count = 0;
    for (int i = 0; i < n; ++ i) {
        Point a = lines[i].first;
        Point b = lines[i].second;
        useful[i] = true;
        for (int j = 0; j < i; ++ j) {
            Point c = lines[j].first;
            Point d = lines[j].second;
            if (a.on(c, d) && b.on(c, d)) {
                useful[i] = false;
            }
        }
        useful_count += useful[i];
    }
    bool all = true;
    {
        Point a = lines[0].first;
        Point b = lines[0].second;
        for (int i = 1; i < n; ++ i) {
            if (useful[i]) {
                Point c = lines[i].first;
                Point d = lines[i].second;
                all &= !has_intersection(a, b, c, d);
            }
        }
    }
    int unbounded = all ? useful_count + 1 : 2 * useful_count;
    int answer = 0;
    while (unbounded < w) {
        if (all) {
            unbounded <<= 1;
            all = false;
        } else {
            unbounded += 2;
        }
        answer ++;
    }
    printf("%d\n", answer);
    return 0;
}
