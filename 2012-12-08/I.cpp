#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

const int maxn = 51;
const int inf = 1000000000;

int flag[maxn][maxn][maxn * maxn];
int flags;

int memo[maxn][maxn][maxn * maxn];

struct Point {
    int x, y;

    bool operator<(const Point o) const {
        return y * o.x > o.y * x;
    }
};

Point pts[maxn];
int n, k;

int go(int dep, int used, int h)
{
    int &ret = memo[dep][used][h];
    if (flag[dep][used][h] == flags) {
        return ret;
    }
    flag[dep][used][h] = flags;
    if (dep == n) {
        if (used == k) {
            return ret = 0;
        }
        return ret = -inf;
    }
    ret = go(dep + 1, used, h);
    if (used < k) {
        int ans = go(dep + 1, used + 1, h + pts[dep].y);
        ans += pts[dep].x * pts[dep].y;
        ans += h * pts[dep].x * 2;
        if (ret < ans) {
            ret = ans;
        }
    }
    return ret;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pts[i].x, &pts[i].y);
        }
        std::sort(pts, pts + n);
        flags ++;
        printf("Case %d: %d\n", cas, go(0, 0, 0));
    }
}
