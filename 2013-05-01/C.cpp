#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

int signum(int x) {
    return x < 0 ? -1 : x > 0;
}

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}

    Point rotate() const {
        return Point(-y, x);
    }

    Point &operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
};

bool operator <(const Point &a, const Point &b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool operator ==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

long long dot(const Point &a, const Point &b) {
    return (long long)a.x * b.x + (long long)a.y * b.y;
}

Point operator -(Point a, const Point &b) {
    return a -= b;
}

const int N = 100000;

int n;
Point polygon[N];

bool by_angle(const std::pair <Point, int> &a, const std::pair <Point, int> &b) {
    if (det(a.first, b.first) == 0) {
        if (signum(a.first.y) == signum(b.first.y)) {
            return a.second < b.second;
        }
        return signum(a.first.y) < signum(b.first.y);
    }
    return det(a.first, b.first) > 0;
}

Point reduce(Point p) {
    int g = std::__gcd(p.x, p.y);
    p.x /= g;
    p.y /= g;
    if (p.x < 0) {
        p.x *= -1;
        p.y *= -1;
    }
    return p;
}

std::map <Point, std::vector <int> > edges;
std::map <Point, int> memory;

std::vector <std::pair <Point, int> > angles;
std::vector <int> sum;

int init = 0;

void deal(Point a, Point b) {
    if (a.x < 0 && b.x < 0) {
        return;
    }
    if (a.x < 0) {
        init ++;
    } else {
        angles.push_back(std::make_pair(a, 1));
    }
    if (b.x < 0) {
    } else {
        angles.push_back(std::make_pair(b, -1));
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &polygon[i].x, &polygon[i].y);
    }
    for (int i = 0; i < n; ++ i) {
        Point p = reduce(polygon[(i + 1) % n] - polygon[i]);
        edges[reduce(p.rotate())].push_back(i);
    }
    for (int i = 0; i < n; ++ i) {
        Point a = polygon[(i + n - 1) % n] - polygon[i];
        Point b = polygon[(i + 1) % n] - polygon[i];
        if (det(a, b) < 0) {
            std::swap(a, b);
        }
        a = a.rotate();
        b = b.rotate().rotate().rotate();
        for (int _ = 0; _ < 2; ++ _) {
            deal(b, a);
            a = a.rotate().rotate();
            b = b.rotate().rotate();
        }
    }
    std::sort(angles.begin(), angles.end(), by_angle);

    sum.push_back(0);
    for (int i = 0; i < (int)angles.size(); ++ i) {
        sum.push_back(sum.back() + angles[i].second);
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        Point p;
        scanf("%d%d", &p.x, &p.y);
        p = reduce(p);
        if (memory.find(p) == memory.end()) {
            foreach (iter, edges[p]) {
                int id = *iter;
                int a = signum(dot(p, polygon[(id + n - 1) % n] - polygon[id]));
                int b = signum(dot(p, polygon[(id + 2) % n] - polygon[(id + 1) % n]));
                memory[p] += a * b > 0;
            }
        } 
        int counter = memory[p];
        counter += init + sum[std::lower_bound(angles.begin(), angles.end(), std::make_pair(p, 0), by_angle) - angles.begin()];
        puts(counter <= 2 ? "YES" : "NO");
    }
    return 0;
}
