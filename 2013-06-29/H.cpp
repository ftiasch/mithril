#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cassert>
using namespace std;

#define FOR(i, a) for(__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++ i)

const int maxn = 200;

int n, m;
bool d[maxn][maxn]; // a is 0, a + n is 1
int op[10000][3];

inline void add(int a, int b) // a implies b
{
    if (d[a][b]) {
        return;
    }
    vector<int> upper, down;
    for (int i = 0; i < n + n; ++ i) {
        if (d[i][a]) {
            upper.push_back(i);
        }
        if (d[b][i]) {
            down.push_back(i);
        }
    }
    FOR (u, upper) {
        FOR (v, down) {
            d[*u][*v] = true;
        }
    }
}

inline bool reach(int s, int t, int a1, int b1, int a2, int b2)
{
    if (d[s][t]) {
        return true;
    }
    if (a1 != -1 && d[s][a1] && d[b1][t]) {
        return true;
    }
    if (a2 != -1 && d[s][a2] && d[b2][t]) {
        return true;
    }
    if (a1 != -1 && a2 != -1) {
        if (d[s][a1] && d[b1][a2] && d[b2][t]) {
            return true;
        }
        if (d[s][a2] && d[b2][a1] && d[b1][t]) {
            return true;
        }
    }
    return false;
}

inline bool verify(int a1 = -1, int b1 = -1, int a2 = -1, int b2 = -1)
{
    for (int i = 0; i < n; ++ i) {
        if (reach(i, i + n, a1, b1, a2, b2) && reach(i + n, i, a1, b1, a2, b2)) {
            return false;
        }
    }
    return true;
}

bool allForEach = true;

inline bool check(int s, int a, int b)
{
    //case: foreach
    if (s == 1) { // a \subset b
        add(a + n, b + n);
        add(b, a);
        return allForEach || verify();
    } else if (s == 2) { // a = b
        add(a + n, b + n);
        add(b, a);
        swap(a, b);
        add(a + n, b + n);
        add(b, a);
        return allForEach || verify();
    } else if (s == 4){ // a intersect b = empty
        add(a + n, b);
        add(b + n, a);
        return allForEach || verify();
    }
    allForEach = false;
    //case: exist
    if (s == 3) { // a \neq b
        return verify(a + n, a, b, b + n) || verify(a, a + n, b + n, b);
    }
    if (s == 5) { // a intersect b != empty
        return verify(a, a + n, b, b + n);
    }
    assert(false);
}

int main()
{
    for (;scanf("%d%d", &n, &m) == 2 && n;) {
        for (int i = 0; i < m; ++ i) {
            for (int j = 0; j < 3; ++ j) {
                scanf("%d", &op[i][j]);
            }
        }
        int l = 0, r = m + 1;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            allForEach = true;
            memset(d, false, sizeof(d));
            for (int i = 0; i < 2 * n; ++ i) {
                d[i][i] = true;
            }
            bool valid = true;
            for (int i = 0; i < mid && valid; ++ i) {
                if (op[i][0] == 1 || op[i][0] == 2 || op[i][0] == 4) {
                    int s = op[i][0], a = op[i][1], b = op[i][2];
                    -- a; -- b;
                    valid &= check(s, a, b);
                }
            }
            for (int i = 0; i < mid && valid; ++ i) {
                if (op[i][0] == 3 || op[i][0] == 5) {
                    int s = op[i][0], a = op[i][1], b = op[i][2];
                    -- a; -- b;
                    valid &= check(s, a, b);
                }
            }
            if (valid) {
                l = mid;
            } else {
                r = mid;
            }
        }
        printf("%d\n", l);
    }
    return 0;
}

