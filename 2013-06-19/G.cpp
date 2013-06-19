#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>

#define FOR(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

namespace Hopcroft
{
    const int maxn = 100000 + 5;
    
    int cx[maxn], cy[maxn] , mk[maxn], q[maxn], src[maxn], pre[maxn];
    int shift, n;
    
    inline void init(int nodes, int shifts) {
        shift = shifts;
        n = nodes;
    }
    
    inline int maxMatch() {
        memset(mk, -1, sizeof(mk));
        memset(cx, -1, sizeof(cx));
        memset(cy, -1, sizeof(cy));
        
        int limits = n - 1 + shift;
        while (limits >= shift) {
            int s = 0;
            for (;s * s <= limits + shift - 1; ++ s);
            for (int i = 0; i <= limits - shift; ++ i) {
                if (cx[i] != -1) {
                    continue;
                }
                int x = i + shift;
                int y = s * s - x - shift;
                if (y >= 0 && y < n && cy[y] == -1) {
                    cx[i] = y;
                    cy[y] = i;
                }
            }
            int last = limits;
            limits = s * s - limits - 1;
            if (limits >= last) {
                break;
            }
        }
        for (int p = 1, fl = 1, h, tail; fl; ++ p) {
            fl = h = tail = 0;
            for (int i = 0; i < n; ++ i) {
                if (cx[i] == -1) {
                    q[++ tail] = i;
                    pre[i] = -1;
                    src[i] = i;
                }
            }
            for (h = 1; h <= tail; ++ h) {
                int u = q[h];
                if (cx[src[u]] != -1) {
                    continue;
                }
                for (int s = 0; s * s - u - shift < n + shift; ++ s) {
                    int v = s * s - u - shift - shift;
//printf("%d %d %d\n", (u + shift) + (v + shift), u, v);
                    if (v >= 0 && mk[v] != p) {
                        mk[v] = p;
                        q[++ tail] = cy[v];
                        if (cy[v] >= 0) {
                            pre[cy[v]] = u;
                            src[cy[v]] = src[u];
                            continue;
                        }
                        int d, e, t;
                        for (-- tail, fl = 1, d = u, e = v; d != -1; t = cx[d], cx[d] = e, cy[e] = d, e = t, d = pre[d]);
                        break;
                    }
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++ i) {
            res += cx[i] != -1;
        }
        return res;
    }
};

bool isSqr[200001];

int main()
{
    for (int i = 0; i * i <= 200000; ++ i) {
        isSqr[i * i] = true;
    }
    int a, b;
    scanf("%d%d", &a, &b);
    Hopcroft::init(b - a + 1, a);
    
    int maxi = Hopcroft::maxMatch();
    if (maxi < b - a + 1) {
        puts("-1");
    } else {
        for (int i = a; i <= b; ++ i) {
            printf("%d ", Hopcroft::cx[i - a] + a);
            assert(isSqr[i + Hopcroft::cx[i - a] + a]);
        }
        puts("");
    }
    return 0;
}

