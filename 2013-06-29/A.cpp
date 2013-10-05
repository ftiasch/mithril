#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    Point conj() {
        return Point(x, -y);
    }
};

bool operator <(const Point &a, const Point &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool operator ==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

Point operator *(const Point &a, const Point &b) {
    return Point(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

const int MAX = 20000;

std::vector <Point> points[MAX];

int main() {
    for (int i = 0; i * i < MAX; ++ i) {
        for (int j = 0; i * i + j * j < MAX; ++ j) {
            int norm = i * i + j * j;
            points[norm].push_back(Point(i, j));
            points[norm].push_back(Point(i, -j));
            points[norm].push_back(Point(-i, j));
            points[norm].push_back(Point(-i, -j));
        }
    }
    for (int i = 0; i < MAX; ++ i) {
        std::sort(ALL(points[i]));
        points[i].erase(std::unique(ALL(points[i])), points[i].end());
    }
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        int p, q;
        scanf("%d%d", &p, &q);
        Point A(p, q);
        int norm = p * p + q * q;
        int count = 0;
        for (int i = 1; i <= norm; ++ i) {
            if (norm % i == 0) {
                foreach (iter, points[i]) {
                    Point &B = *iter;
                    Point C = A * (B.conj());
                    if (C.x % i == 0 && C.y % i == 0) {
                        count ++;
                    }
                }
            }
        }
        puts(count == 8 ? "P" : "C");
    }
    return 0;
}
