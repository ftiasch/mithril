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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const double LIMIT = 3.0001 * 3.0001;

unsigned rndUnsigned()
{
    return ((unsigned)rand() & 65535) << 16 | ((unsigned)rand() & 65535);
}

double rndDouble()
{
    return (rndUnsigned() + (double)5000.0) / ((double)65536.0 * 65536.0 + 10000.0);
}

struct Point {
    double x, y;

    bool check(const Point &o) {
        return (x - o.x) * (x - o.x) + (y - o.y) * (y - o.y) >= LIMIT;
    }

    void read() {
        scanf("%lf%lf", &x, &y);
    }

    void print() {
        printf("%.20f %.20f\n", x, y);
    }

    void random() {
        x = 9.0 * rndDouble();
        y = 9.0 * rndDouble();
    }
};

Point pts[4], ans;

int main()
{
    for (int i = 0; i < 4; i++) {
        pts[i].read();
    }
    while (true) {
        ans.random();
        bool valid = true;
        for (int i = 0; i < 4; i++) {
            if (!ans.check(pts[i])) {
                valid = false;
                break;
            }
        }
        if (valid) {
            puts("Possible");
            ans.print();
            return 0;
        }
    }
}
