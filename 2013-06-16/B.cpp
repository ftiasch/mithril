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

const double eps = 1e-11;
const double pi = acos(-1.);

int myRound(double a)
{
    int signum = 1;
    if (a < 0) {
        signum = -1;
        a = -a;
    }
    return (int)(a + 0.5 + eps) * signum;
}

struct Point 
{
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
    Point(){}

    Point operator+(const Point &o) const {
        return Point(x + o.x, y + o.y);
    }

    Point operator-(const Point &o) const {
        return Point(x - o.x, y - o.y);
    }

    Point rotate(complex<double> ang) const {
        complex<double> ret = complex<double>(x, y) * ang;
        return Point(myRound(ret.real()), myRound(ret.imag()));
    }

    bool operator<(const Point &o) const {
        return x < o.x || x == o.x && y < o.y;
    }

    void read() {
        scanf("%d%d", &x, &y);
    }

    bool isZero() const {
        return x == 0 && y == 0;
    }
};

vector<complex<double> > angles;

void prepare()
{
    for (int x = -10; x <= 10; x++) {
        for (int y = -10; y <= 10; y++) {
            if (abs(x) != 10 && abs(y) != 10) {
                continue;
            }
            if (x < 0 || x == 0 && y < 0) {
                continue;
            }
            complex<double> ang(x, y);
            ang /= abs(ang);
            angles.push_back(ang);
        }
    }
}

Point from[3], to[3], pts[3];

bool doit(int &A, int &C)
{
    if (A < 0) {
        A = -A;
        C = -C;
    }
    if (A != 0) {
        if (C <= 0 || C % A) {
            return true;
        }
        C /= A;
        A = 1;
    } else if (C != 0) {
        return true;
    }
    return false;
}

int solve(int A, int B, int C, int D)
{
    // A * x == C, B * x == D
    if (doit(A, C) || doit(B, D)) {
        return 0;
    }
    if (C == 0 && D == 0) {
        return 2;
    }
    if (C != 0 && D != 0 && C != D) {
        return 0;
    }
    return 1;
}

int main()
{
    int cas = 0;
    prepare();
    while (true) {
        for (int i = 0; i < 3; i++) {
            from[i].read();
        }
        if (from[0].isZero() && from[1].isZero() && from[2].isZero()) {
            break;
        }
        for (int i = 0; i < 3; i++) {
            to[i].read();
        }
        sort(to, to + 3);
        int ways = 0;
        FOR (ang, angles) {
            for (int dx = -1; dx <= 1; dx += 2) {
                for (int dy = -1; dy <= 1; dy += 2) {
                    for (int i = 0; i < 3; i++) {
                        pts[i] = from[i].rotate(*ang);
                        pts[i].x *= dx;
                        pts[i].y *= dy;
                    }
                    sort(pts, pts + 3);
                    Point a = pts[1] - pts[0], b = pts[2] - pts[0];
                    Point c = to[1] - to[0], d = to[2] - to[0];
                    int now = solve(a.x, b.x, c.x, d.x) * solve(a.y, b.y, c.y, d.y);
                    ways += now;
                }
            }
        }
        printf("Case %d: %s\n", ++cas, ways == 0 ? "no solution" : ways == 1 ? "equivalent solutions" : "inconsistent solutions");
    }
}
