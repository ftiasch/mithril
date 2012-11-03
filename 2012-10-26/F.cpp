#include <cassert>
#include <cstdio>
#include <set>
using namespace std;

struct Point {
    int x, y, z;

    Point() {}

    Point(int x, int y, int z) : x(x), y(y), z(z) {}
};

bool operator < (const Point &a, const Point &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    if (a.y != b.y) {
        return a.y < b.y;
    }
    return a.z < b.z;
}

int main() {
    int f;
    scanf("%d", &f);
    set <Point> points;
    for (int i = 0; i < f; ++ i) {
        for (int j = 0; j < 3; ++ j) {
            Point p;
            scanf("%d%d%d", &p.x, &p.y, &p.z);
            points.insert(p);
        }
    }
    assert(f % 2 == 0);
    printf("%d\n", (2 - ((int)points.size() - 3 * f / 2 + f)) / 2);
    return 0;
}
