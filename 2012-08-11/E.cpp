#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

static const double EPSILON = 1e-9;
int signum(double x) { return x < -EPSILON? -1: x > EPSILON; }

struct Point {
    double x, y;

    Point(double x = 0, double y = 0): x(x), y(y) {}

    Point &operator +=(const Point &o) { return x += o.x, y += o.y, *this; }
    Point &operator -=(const Point &o) { return x -= o.x, y -= o.y, *this; }
    Point &operator *=(double k) { return x *= k, y *= k, *this; }
    Point &operator /=(double k) { return x /= k, y /= k, *this; }

    bool on(const Point &, const Point &) const;
};

bool operator ==(const Point &a, const Point &b) {
    return signum(a.x - b.x) == 0 && signum(a.y - b.y) == 0;
}

bool operator <(const Point &a, const Point &b) {
    if (signum(a.x - b.x) == 0) {
        return signum(a.y - b.y) < 0;
    }
    return signum(a.x - b.x) < 0;
}

Point operator +(Point a, const Point &b) { return a += b; }
Point operator -(Point a, const Point &b) { return a -= b; }
Point operator *(Point a, double k) { return a *= k; }
Point operator *(double k, Point a) { return a *= k; }
Point operator /(Point a, double k) { return a /= k; }

double det(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

istream &operator >>(istream &in, Point &p) { return in >> p.x >> p.y; }

bool Point::on(const Point &a, const Point &b) const {
    Point p = *this;
    return signum(det(p - a, p - b)) == 0 && signum(dot(p - a, p - b)) <= 0;
}

const int N = 20;

int n;
Point segments[N][2], newSegment[N][2];
bool graph[N * N][N * N], visit[N];

Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    double s_1 = det(c - a, b - a);
    double s_2 = det(d - a, b - a);
    return (c * s_2 - d * s_1) / (s_2 - s_1);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 2; ++ j) {
            cin >> segments[i][j];
        }
    }
    int newN = 0;
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < n; ++ i) {
        if (!visit[i]) {
            Point a = segments[i][0];
            Point b = segments[i][1];
            Point normal = b - a;
            if (signum(dot(normal, a) - dot(normal, b)) > 0) {
                swap(a, b);
            }
            visit[i] = true;
            while (true) {
                bool found = false;
                for (int j = 0; j < n; ++ j) {
                    if (!visit[j] && signum(det(normal, segments[j][1] - segments[j][0])) == 0) {
                        if (segments[j][0].on(a, b) || segments[j][1].on(a, b)) {
                            found = true;
                            visit[j] = true;
                            for (int k = 0; k < 2; ++ k) {
                                if (signum(dot(normal, segments[j][k]) - dot(normal, a)) < 0) {
                                    a = segments[j][k];
                                }
                                if (signum(dot(normal, segments[j][k]) - dot(normal, b)) > 0) {
                                    b = segments[j][k];
                                }
                            }
                        }
                    }
                }
                if (!found) {
                    break;
                }
            }
            segments[newN][0] = a;
            segments[newN ++][1] = b;
        }
    }
    vector <Point> points;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            if (signum(det(segments[i][1] - segments[i][0], segments[j][1] - segments[j][0])) != 0) {
                points.push_back(intersect(segments[i][0], segments[i][1], segments[j][0], segments[j][1]));
            }
        }
    }
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    int m = points.size();
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < i; ++ j) {
            bool found = false;
            for (int k = 0; k < n && !found; ++ k) {
                found |= points[i].on(segments[k][0], segments[k][1]) 
                    && points[j].on(segments[k][0], segments[k][1]);
            }
            graph[i][j] = graph[j][i] = found;
        }
    }
    int result = 0;
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < i; ++ j) {
            if (graph[i][j]) {
                for (int k = 0; k < j; ++ k) {
                    if (graph[i][k] && graph[j][k] && signum(det(points[i] - points[k], points[j] - points[k])) != 0) {
                        result ++;
                    }
                }
            }
        }
    }
    printf("%d\n", result);
    return 0;
}
