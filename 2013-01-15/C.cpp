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

struct Point
{
    int x, y;

    Point(){}

    Point(int x, int y) : x(x), y(y) {}
};

inline int det(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - x2 * y1;
}

inline int det(const Point &a, const Point &b, const Point &c)
{
    return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

inline int dot(int x1, int y1, int x2, int y2)
{
    return x1 * x2 + y1 * y2;
}

inline int dot(const Point &a, const Point &b, const Point &c)
{
    return dot(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

const int maxn = 300;

int n;
Point pts[maxn];

unsigned long long seed[maxn];
bool vis[maxn][maxn];

Point from, to;

bool byDotProduct(int a, int b)
{
    return dot(from, to, pts[a]) < dot(from, to, pts[b]);
}

int main()
{
    scanf("%d", &n);
    unsigned long long all = 0;
    for (int i = 0; i < n; i++) {
        seed[i] = rand();
        seed[i] = seed[i] << 32 | rand();
        all ^= seed[i];
        scanf("%d%d", &pts[i].x, &pts[i].y);
    }
    set<unsigned long long> S;
    S.insert(0);
    S.insert(all);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vis[i][j]) {
                continue;
            }
            from = pts[i];
            to = pts[j];
            unsigned long long L = 0, R = 0, M = 0;
            vector<int> on;
            for (int k = 0; k < n; k++) {
                int num = det(from, to, pts[k]);
                if (num < 0) {
                    L ^= seed[k];
                } else if (num > 0) {
                    R ^= seed[k];
                } else {
                    M ^= seed[k];
                    for (int l = 0; l < on.size(); l++) {
                        vis[on[l]][k] = true;
                        vis[k][on[l]] = true;
                    }
                    on.push_back(k);
                }
            }
            sort(on.begin(), on.end(), byDotProduct);
            unsigned long long now = L;
            for (int k = 0; k < on.size(); k++) {
                S.insert(now);
                S.insert(now ^ M);
                S.insert(now ^ all);
                S.insert(now ^ M ^ all);
                now ^= seed[on[k]];
            }
        }
    }
    printf("%d\n", S.size() - 2);
}
