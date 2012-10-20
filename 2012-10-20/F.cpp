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

struct Point {
    int x, y;

    Point(){}
    Point(int x, int y) : x(x), y(y) {}

    bool operator<(const Point &o) const {
        return x < o.x || x == o.x && y < o.y;
    }

    bool operator==(const Point &o) const {
        return x == o.x && y == o.y;
    }

    double distTo(const Point &o) const {
        return hypot(x - o.x, y - o.y);
    }

    Point operator-(const Point &o) const {
        return Point(x - o.x, y - o.y);
    }
    
};

const int maxn = 402;
const double eps = 1e-11;

int n, m;
Point pts[maxn];
double dist[maxn][maxn];

vector<int> adj[maxn];

double memo[maxn][maxn];
bool seen[maxn][maxn];

bool byPoint(int a, int b)
{
    return pts[a] < pts[b];
}

double go(int a, int b)
{
    double &ret = memo[a][b];
    if (seen[a][b]) {
        return ret;
    }
    seen[a][b] = true;
    ret = 0;
    for (int i = 0, j = 0; i < adj[a].size() && j < adj[b].size(); ) {
        if (pts[adj[a][i]] - pts[a] == pts[adj[b][j]] - pts[b]) {
            if (pts[adj[a][i]].x > pts[a].x) {
                ret = max(ret, dist[a][adj[a][i]] + go(adj[a][i], adj[b][j]));
            }
            i ++;
            j ++;
        } else if (pts[adj[a][i]] - pts[a] < pts[adj[b][j]] - pts[b]) {
            i ++;
        } else {
            j ++;
        }
    }
    return ret;
}

void construct(int a, int b, vector<int> &ansA, vector<int> &ansB)
{
    double expected = go(a, b);
    ansA.push_back(a);
    ansB.push_back(b);
    for (int i = 0, j = 0; i < adj[a].size() && j < adj[b].size(); ) {
        if (pts[adj[a][i]] - pts[a] == pts[adj[b][j]] - pts[b]) {
            if (pts[adj[a][i]].x > pts[a].x) {
                if (fabs(dist[a][adj[a][i]] + go(adj[a][i], adj[b][j]) - expected) < eps) {
                    construct(adj[a][i], adj[b][j], ansA, ansB);
                    return;
                }
            }
            i ++;
            j ++;
        } else if (pts[adj[a][i]] - pts[a] < pts[adj[b][j]] - pts[b]) {
            i ++;
        } else {
            j ++;
        }
    }
}

double solve(vector<int> &ansA, vector<int> &ansB)
{
    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end(), byPoint);
    }
    memset(seen, false, sizeof(seen));
    double ret = 0;
    vector<int> a, b;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double res = go(i, j);
            if (ret < res) {
                ret = res;
                a.clear(), b.clear();
                construct(i, j, a, b);
                ansA = a, ansB = b;
            }
        }
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &pts[i].x, &pts[i].y);
        adj[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        ai --, bi --;
        adj[ai].push_back(bi);
        adj[bi].push_back(ai);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = pts[i].distTo(pts[j]);
        }
    }
    double ans1, ans2;
    vector<int> ans1a, ans1b, ans2a, ans2b;
    ans1 = solve(ans1a, ans1b);
    for (int i = 0; i < n; i++) {
        swap(pts[i].x, pts[i].y);
    }
    ans2 = solve(ans2a, ans2b);
    if (ans1 < ans2) {
        ans1 = ans2;
        ans1a = ans2a;
        ans1b = ans2b;
    }
    if (ans1a.empty()) {
        puts("0.0");
    } else {
        printf("%.10f\n", ans1);
        printf("%d\n", ans1a.size());
        for (int i = 0; i < ans1a.size(); i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", ans1a[i] + 1);
        }
        puts("");
        for (int i = 0; i < ans1b.size(); i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", ans1b[i] + 1);
        }
        puts("");
    }
}
