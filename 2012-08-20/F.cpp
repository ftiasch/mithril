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
    int x, y;

    int dist2() const {
        return x * x + y * y;
    }

    int dist2(const Point &o) const {
        return (x - o.x) * (x - o.x) + (y - o.y) * (y - o.y);
    }
};

const int maxn = 300;
const int MOD = 10007;

int n, R;
Point pts[maxn], pts2[maxn];
bool conn[maxn][maxn];

bool cmp(int a, int b)
{
    int ret = pts2[a].x * pts2[b].y - pts2[b].x * pts2[a].y;
    if (ret == 0) {
        return pts2[a].dist2() < pts2[b].dist2();
    }
    return ret < 0;
}

bool equal(int a, int b)
{
    int ret = pts2[a].x * pts2[b].y - pts2[b].x * pts2[a].y;
    return ret == 0;
}

int parent[maxn];

int findRoot(int p)
{
    return ~parent[p] ? parent[p] = findRoot(parent[p]) : p;
}

bool mergeComp(int a, int b)
{
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) {
        return false;
    }
    parent[a] = b;
    return true;
}

int ma[maxn][maxn];

int inv[MOD];

int main()
{
    inv[1] = 1;
    for (int i = 2; i < MOD; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d", &n, &R);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pts[i].x, &pts[i].y);
        }
        memset(conn, false, sizeof(conn));
        memset(parent, -1, sizeof(parent));
        int comps = n;
        for (int i = 0; i < n; i++) {
            vector<int> lower, upper;
            for (int j = 0; j < n; j++) {
                if (i == j || pts[i].dist2(pts[j]) > R * R) {
                    continue;
                }
                pts2[j].x = pts[j].x - pts[i].x;
                pts2[j].y = pts[j].y - pts[i].y;
                if (pts2[j].x > 0 || pts2[j].x == 0 && pts2[j].y > 0) {
                    upper.push_back(j);
                } else {
                    lower.push_back(j);
                }
            }
            sort(lower.begin(), lower.end(), cmp);
            sort(upper.begin(), upper.end(), cmp);
            for (int j = 0; j < lower.size(); j++) {
                if (j == 0 || !equal(lower[j - 1], lower[j])) {
                    conn[i][lower[j]] = true;
                }
            }
            for (int j = 0; j < upper.size(); j++) {
                if (j == 0 || !equal(upper[j - 1], upper[j])) {
                    conn[i][upper[j]] = true;
                }
            }
            for (int j = 0; j < n; j++) {
                if (conn[i][j] && mergeComp(i, j)) {
                    comps --;
                }
            }
        }
        if (comps == 1) {
            memset(ma, 0, sizeof(ma));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (conn[i][j]) {
                        ma[i][i] ++;
                        ma[i][j] --;
                    }
                }
            }
            n --;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    ma[i][j] = (ma[i][j] % MOD + MOD) % MOD;
                }
            }
            int det = 1;
            for (int i = 0; i < n; i++) {
                int r = i;
                while (r < n && ma[r][i] == 0) {
                    r ++;
                }
                if (r == n) {
                    det = 0;
                    break;
                }
                if (r != i) {
                    det = (MOD - det) % MOD;
                    for (int j = 0; j < n; j++) {
                        swap(ma[i][j], ma[r][j]);
                    }
                }
                det = det * ma[i][i] % MOD;
                for (int j = n - 1; j >= i; j--) {
                    ma[i][j] = ma[i][j] * inv[ma[i][i]] % MOD;
                }
                for (int j = i + 1; j < n; j++) {
                    for (int k = n - 1; k >= i; k --) {
                        ma[j][k] = (ma[j][k] + MOD - ma[j][i] * ma[i][k] % MOD) % MOD;
                    }
                }
            }
            printf("%d\n", det);
        } else {
            printf("%d\n", -1);
        }
    }
}
