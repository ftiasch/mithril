#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn = 55;

int f[maxn][maxn], n, k, d, g;

inline bool check(int ans)
{
    int s = d + g;
    memset(f, -1, sizeof(f));
    f[n][k] = ans;
    for (int i = n - 1; i >= 0; -- i) {
        for (int j = 0; j <= i && j <= k; ++ j) {
            if (n - i + j < k) {
                continue;
            }
            f[i][j] = 0;
            while (f[i][j] <= s) {
                int right = min(s - f[i][j], f[i][j]);
                if (f[i + 1][j] != -1) {
                    right = min(f[i][j] - f[i + 1][j], right);
                }
                int left = 0;
                if (f[i + 1][j + 1] != -1) {
                    left = max(left, f[i + 1][j + 1] - f[i][j]);
                }
                if (left <= right) {
                    break;
                }
                ++ f[i][j];
            }
        }
    }
    
    return f[0][0] <= d;
}

int main()
{
    scanf("%d%d%d%d", &d, &g, &n, &k);
    int l = 0, r = d + g + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    printf("%d\n", l);
    return 0;
}

