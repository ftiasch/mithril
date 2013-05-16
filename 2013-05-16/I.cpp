#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
using namespace std;

const int maxn = 100;

int f[maxn][maxn];

inline int dfs(int n, int k)
{
    if (n == 2) {
        return n + 1 - k;
    }
    int &res = f[n][k];
    if (res != -1) {
        return res;
    }
    res = k;
    for (int miss = n; miss >= 1; -- miss) {
        if (res != miss) {
            int pos = res;
            if (miss < res) {
                -- pos;
            }
            pos = dfs(n - 1, pos);
            if (pos >= miss) {
                ++ pos;
            }
            res = pos;
        }
    }
    return res;
}

int main()
{
    memset(f, -1, sizeof(f));
/*    for (int n = 10; n <= 99; ++ n) {
        for (int k = 1; k <= n; ++ k) {
            assert(dfs(n, k) == k);
//            printf("%d ", dfs(n, k));
        }
        puts("");
    }*/
    long long n, k, res;
    cin >> n >> k;
    if (n < 10) {
        res = dfs(n, k);
    } else {
        res = k;
    }
    cout << res << endl;
    return 0;
}

