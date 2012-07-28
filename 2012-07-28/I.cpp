#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

struct Point
{
    double x, y, z;

    inline double dot(const Point &o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    void read() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
};

const int MAXN = 100;
const double EPS = 1e-11;
const double INF = 1e100;

int n, m, qs;
Point a[MAXN], b[MAXN], qi;

inline double nextDouble()
{
    int a = (unsigned)rand() & (1 << 13) - 1;
    const static double inv = 1.0 / (1 << 12);
    return (a - (1 << 12) + 0.5) / inv;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        a[i].read();
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        b[i].read();
    }
    Point dir;
    double middle = 0.0;
    char leftSide = '1', rightSide;
    while (true) {
        dir.x = nextDouble();
        dir.y = nextDouble();
        dir.z = nextDouble();
        if (dir.dot(dir) < 0.01) {
            continue;
        }
        double min1 = INF, max1 = -INF;
        double min2 = INF, max2 = -INF;
        for (int i = 0; i < n; i++) {
            double len = dir.dot(a[i]);
            min1 = min(min1, len);
            max1 = max(max1, len);
        }
        for (int i = 0; i < m; i++) {
            double len = dir.dot(b[i]);
            min2 = min(min2, len);
            max2 = max(max2, len);
        }
        if (max1 <= min2 + EPS) {
            middle = (max1 + min2) / 2;
            leftSide = '1';
            break;
        } else if (max2 <= min1 + EPS) {
            middle = (max2 + min1) / 2;
            leftSide = '2';
            break;
        }
    }
    rightSide = '1' ^ '2' ^ leftSide;
    scanf("%d", &qs);
    while (qs--) {
        qi.read();
        double len = dir.dot(qi);
        putchar(len <= middle ? leftSide : rightSide);
    }
    puts("");
}

