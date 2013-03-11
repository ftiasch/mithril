#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int N = 21;

int n, d[N], sum[1 << N];
short need[1 << N], minimal[1 << N];

short solve(int mask) {
    short &ret = need[mask];
    if (ret == -1) {
        ret = 1;
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            if (minimal[sub] == 1 && sum[sub] == 0) {
                ret = std::max(ret, (short)(solve(mask ^ sub) + 1));
            }
        }
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    memset(d, 0, sizeof(d));
    for (int i = 0, x; i < n; ++ i) {
        scanf("%d", &x);
        d[i] += x;
    }
    for (int i = 0, x; i < n; ++ i) {
        scanf("%d", &x);
        d[i] -= x;
    }
    {
        int total = 0;
        for (int i = 0; i < n; ++ i) {
            if (d[i] != 0) {
                d[total ++] = d[i];
            }
        }
        n = total;
    }
    memset(sum, 0, sizeof(sum));
    memset(minimal, 0, sizeof(minimal));
    for (int mask = 1; mask < 1 << n; ++ mask) {
        int i = 0;
        while (~mask >> i & 1) {
            i ++;
        }
        sum[mask] = sum[mask ^ (1 << i)] + d[i];
        minimal[mask] = sum[mask]==0;
        for (int i = 0; i < n; ++ i) {
            if (mask >> i & 1) {
                minimal[mask] += minimal[mask ^ (1 << i)];
            }
        }
        if (minimal[mask] > 1) {
            minimal[mask] = 2;
        }
    }
    if (sum[(1 << n) - 1] == 0) {
        memset(need, -1, sizeof(need));
        need[0] = 0;
        printf("%d\n", n - solve((1 << n) - 1));
    } else {
        puts("-1");
    }
    return 0;
}
