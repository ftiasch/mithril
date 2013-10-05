#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const double EPS = 1e-8;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

struct Point {
    double x, y, z;

    Point() : x(0), y(0), z(0) {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    Point &operator -=(const Point &o) {
        x -= o.x, y -= o.y, z -= o.z;
        return *this;
    }

    double norm2() const;
    double norm() {
        return sqrt(norm2());
    }

    double to(const Point&, const Point&) const;
};

Point operator -(Point a, const Point &b) {
    return a -= b;
}

std::istream &operator >>(std::istream &in, Point &p) {
    return in >> p.x >> p.y >> p.z;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point det(const Point &a, const Point &b) {
    return Point(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

double Point::norm2() const {
    return dot(*this, *this);
}

bool is_cute(const Point &o, const Point &a, const Point &b) {
    return signum(dot(a - o, b - o)) > 0;
}

double Point::to(const Point &a, const Point &b) const {
    const Point &p = *this;
    if (is_cute(a, b, p) && is_cute(b, a, p)) {
        return det(a - p, b - p).norm() / (a - b).norm();
    }
    return std::min((a - p).norm(), (b - p).norm());
}

const int N = 2000;
const int M = 15;

int n, m, r;
Point center[N], lights[M], target;
double radius[N], bright[M];

typedef unsigned long long Unsigned;

Unsigned hideMask[M][(N + 63) >> 6], nowMask[(N + 63) >> 6];

bool check(int i, int j) {
    if (signum((center[i] - lights[j]).norm() - radius[i]) < 0 && signum((center[i] - target).norm() - radius[i]) < 0) {
        return false;
    }
    return signum(center[i].to(target, lights[j]) - radius[i]) < 0;
}

int main() {
    while ((std::cin >> n >> m >> r) && n) {
        for (int i = 0; i < n; ++ i) {
            std::cin >> center[i] >> radius[i];
        }
        for (int i = 0; i < m; ++ i) {
            std::cin >> lights[i] >> bright[i];
        }
        std::cin >> target;
        memset(hideMask, 0, sizeof(hideMask));
        for (int j = 0; j < m; ++ j) {
            for (int i = 0; i < n; ++ i) {
                if (check(i, j)) {
                    hideMask[j][i >> 6] |= 1ULL << (i & 63);
                }
            }
        }
        double answer = 0;
        for (int mask = 0; mask < 1 << m; ++ mask) {
            memset(nowMask, 0, sizeof(nowMask));
            for (int i = 0; i < m; ++ i) {
                if (mask >> i & 1) {
                    for (int j = 0; j <= n - 1 >> 6; ++ j) {
                        nowMask[j] |= hideMask[i][j];
                    }
                }
            }
            int count = 0;
            for (int j = 0; j <= n - 1 >> 6; ++ j) {
                count += __builtin_popcountll(nowMask[j]);
            }
            if (count <= r) {
                double new_answer = 0;
                for (int i = 0; i < m; ++ i) {
                    if (mask >> i & 1) {
                        new_answer += bright[i] / (lights[i] - target).norm2();
                    }
                }
                answer = std::max(answer, new_answer);
            }
        }
        printf("%.10f\n", answer);
    }
    return 0;
}
