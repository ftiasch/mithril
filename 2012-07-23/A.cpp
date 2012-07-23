#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 50;
const double EPS = 1e-9;

int signum(double x) {
    return x < -EPS? -1: x > EPS;
}

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    double norm() const {
        return sqrt(x * x + y * y);
    }
};

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

bool isIntersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    return signum(det(b - a, c - a)) * signum(det(b - a, d - a)) < 0 && signum(det(d - c, a - c)) * signum(det(d - c, b - c)) < 0;
}


bool isCute(const Point &a, const Point &o, const Point &b) {
    return signum(dot(a - o, b - o)) > 0;
}

int n, graph[N][N], mother[N];
vector <pair <int, int> > bridges;
Point p[N];
double r[N];
vector <pair <double, pair <int, int> > > edges;

int find(int i) {
    if (mother[i] != i) {
        mother[i] = find(mother[i]);
    }
    return mother[i];
}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        double x, y;
        scanf("%lf%lf%lf", &x, &y, r + i);
        p[i] = Point(x, y);
    }
    memset(graph, 0, sizeof(graph));
    int m = 0;
    scanf("%d", &m);
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        graph[a][b] = graph[b][a] = true;
        bridges.push_back(make_pair(a, b));
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            bool valid = true;
            for (int k = 0; k < m; ++ k) {
                valid &= !isIntersect(p[i], p[j], p[bridges[k].first], p[bridges[k].second]);
            }
            for (int k = 0; k < n; ++ k) {
                if (k != i && k != j && isCute(p[k], p[i], p[j]) && isCute(p[k], p[j], p[i])) {
                    double d = abs(det(p[i] - p[k], p[j] - p[k]) / (p[i] - p[j]).norm());
                    valid &= signum(d - r[k]) >= 0;
                }
            }
            if (!valid) {
                continue;
            }
//printf("%d -- %d\n", i + 1, j + 1);
            double d = (p[i] - p[j]).norm() - r[i] - r[j];
            if (graph[i][j]) {
                d = 0;
            }
            edges.push_back(make_pair(d, make_pair(i, j)));
        }
    }
    sort(edges.begin(), edges.end());
    for (int i = 0; i < n; ++ i) {
        mother[i] = i;
    }
    double result = 0;
    for (int i = 0; i < (int)edges.size(); ++ i) {
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        if (find(a) != find(b)) {
            mother[find(a)] = find(b);
            result += edges[i].first;
        }
    }
    printf("%.3f\n", result);
    return 0;
}
