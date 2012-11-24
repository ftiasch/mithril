#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 300;
const int M = 1000;

const double INF = 1e100;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    double norm() const {
        return sqrt(x * x + y * y);
    }

    int quadrant() const {
        if (x > 0 && y >= 0) {
            return 0;
        }
        if (y > 0 && x <= 0) {
            return 1;
        }
        if (x < 0 && y <= 0) {
            return 2;
        }
        return 3;
    }

    bool on(const Point &, const Point &) const;
};

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y;
}

Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

int det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

bool operator < (const Point &a, const Point &b) {
    if (a.quadrant() == b.quadrant()) {
        return det(a, b) > 0;
    }
    return a.quadrant() < b.quadrant();
}

int dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

bool Point::on(const Point &a, const Point &b) const {
    Point p = *this;
    return dot(p - a, p - b) <= 0;
}

int n, m;
Point points[N], mines[M];

bool valid[N][N], valid2[N][N];
int next[N][N], head[N][N];

int start;
bool mark[N][N];
double length[N][N], minimum[N][N];

double solve(int i, int j) {
    if (i == j || !valid[i][j] || !valid2[i][j]) {
        return INF;
    }
    if (j == start) {
        return length[i][j];
    }
    if (!mark[i][j]) {
        mark[i][j] = true;
        minimum[i][j] = INF;
        if (head[i][j] != -1) {
            minimum[i][j] = min(minimum[i][j], length[i][j] + solve(j, head[i][j]));
        }
        if (valid[i][next[i][j]]) {
            minimum[i][j] = min(minimum[i][j], solve(i, next[i][j]));
        }
    }
    return minimum[i][j];
}

int main() {
    freopen("mines.in","r",stdin);
    freopen("mines.out","w",stdout);
    
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        cin >> points[i];
    }
    for (int i = 0; i < m; ++ i) {
        cin >> mines[i];
    }
    memset(valid, 0, sizeof(valid));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j) {
                valid[i][j] = true;
                valid2[i][j] = false;
                for (int k = 0; k < m; ++ k) {
                    valid[i][j] &= det(points[j] - points[i], mines[k] - points[i]) >= 0;
                    valid2[i][j] |= det(points[j] - points[i], mines[k] - points[i]) > 0;
                }
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        vector <pair <Point, int > > order;
        for (int j = 0; j < n; ++ j) {
            if (i != j) {
                order.push_back(make_pair(points[j] - points[i], j));
            }
        }
        sort(order.begin(), order.end());
        for (int j = 0; j < n - 1; ++ j) {
            next[i][order[j].second] = order[(j + 1) % (n - 1)].second;
        }
    }
    memset(head, -1, sizeof(head));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j) {
                int &best = head[i][j];
                for (int k = 0; k < n; ++ k) {
                    if (det(points[j] - points[i], points[k] - points[j]) > 0) {
                        if (best == -1 || det(points[best] - points[j], points[k] - points[j]) < 0) {
                            best = k;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            length[i][j] = (points[i] - points[j]).norm();
        }
    }
/*for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < n; ++ j) {
        if (i != j && valid[i][j]) {
            printf("%d -> %d\n", i, j);
        }
    }
}*/
    double answer = INF;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j && valid[i][j] && !valid2[i][j]) {
                bool all = true;
                for (int k = 0; k < m; ++ k) {
                    all &= mines[k].on(points[i], points[j]);
                }
                if (all) {
                    answer = min(answer, length[i][j] * 2);
                }
            }
        }
    }
    for (start = 0; start < n; ++ start) {
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < n; ++ i) {
            answer = min(answer, solve(start, i));
        }
    }
    if (answer < 1e50) {
        printf("%.8f\n", answer);
    } else {
        puts("-1");
    }
    return 0;
}
