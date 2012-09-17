#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    Point& operator +=(const Point &o) { x += o.x, y += o.y; return *this; }
    Point& operator -=(const Point &o) { x -= o.x, y -= o.y; return *this; }
    Point& operator *=(double k) { x *= k, y *= k; return *this; }
    Point& operator /=(double k) { x /= k, y /= k; return *this; }

    bool on(const Point&, const Point&) const;

    double norm() const { return sqrt(x * x + y * y); }
    double arg() const { return atan2(y, x); }
};

Point operator +(Point a, const Point &b) { return a += b; }
Point operator -(Point a, const Point &b) { return a -= b; }
Point operator *(Point a, double k) { return a *= k; }
Point operator *(double k, Point a) { return a *= k; }
Point operator /(Point a, double k) { return a /= k; }

double det(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

const double EPS = 1e-8;

int signum(double x) { return x < -EPS? -1: x > EPS; }

bool Point::on(const Point &a, const Point &b) const {
    Point p = *this;
    double len=(a-p).norm();
    if (signum(len)==0) return true;
    return signum(det(b - p, a - p)/len) == 0 && signum(dot(b - p, a - p)) <= 0;
}

Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    double s_1 = det(b - a, c - a);
    double s_2 = det(b - a, d - a);
    return (s_2 * c - s_1 * d) / (s_2 - s_1);
}

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y;
}

bool operator==(const Point &a, const Point &b) { return signum(a.x - b.x) == 0 && signum(a.y - b.y) == 0; }
bool operator<(const Point &a, const Point &b) {
    if (signum(a.x - b.x) == 0) {
        return signum(a.y - b.y) < 0;
    }
    return signum(a.x - b.x) < 0;
}

const int N = 100;

int n;
Point end[N];
vector <Point> points;

const int V = N * N;
const int E = 6 * V;

int edgeCount, firstEdge[V], to[E], nextEdge[E];

set <pair <int, int> > edges;

void addEdge(int u, int v) {
    if (edges.find(make_pair(u, v)) == edges.end()) {
        edges.insert(make_pair(u, v));
        to[edgeCount] = v;
        nextEdge[edgeCount] = firstEdge[u];
        firstEdge[u] = edgeCount ++;
    }
}

int next[E];
bool visit[E];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> end[i];
        points.push_back(end[i]);
    }
    for (int i = 0; i + 1 < n; ++ i) {
        for (int j = i + 1; j + 1 < n; ++ j) {
            if (signum(det(end[i + 1] - end[i], end[j + 1] - end[j])/(end[i+1]-end[i]).norm()) != 0) {
                points.push_back(intersect(end[i], end[i + 1], end[j], end[j + 1]));
            }
        }
    }
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i + 1 < n; ++ i) {
        vector <pair <double, int> > events;
        for (int k = 0; k < (int)points.size(); ++ k) {
            if (points[k].on(end[i], end[i + 1])) {
                events.push_back(make_pair((points[k] - end[i]).norm(), k));
            }
        }
        sort(events.begin(), events.end());
        for (int k = 0; k + 1 < (int)events.size(); ++ k) {
            addEdge(events[k].second, events[k + 1].second);
            addEdge(events[k + 1].second, events[k].second);
        }
    }
    for (int i = 0; i < (int)points.size(); ++ i) {
        vector <pair <double, int> > events;
        for (int iter = firstEdge[i]; iter != -1; iter = nextEdge[iter]) {
            events.push_back(make_pair((points[to[iter]] - points[i]).arg(), iter));
        }
        sort(events.begin(), events.end());
        for (int k = 0; k < (int)events.size(); ++ k) {
            next[events[(k + 1) % (int)events.size()].second ^ 1] = events[k].second;
        }
    }
    double result = 0;
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < edgeCount; ++ i) {
        if (!visit[i]) {
            double ret = 0;
            int p = i;
            while (!visit[p]) {
                visit[p] = true;
                ret += det(points[to[p ^ 1]], points[to[p]]);
                p = next[p];
            }
            if (p == i && signum(ret) > 0) {
                result += ret;
            }
        }
    }
    printf("%.8f\n", result / 2.0);
    return 0;
}
