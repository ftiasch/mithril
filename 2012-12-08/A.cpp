#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 8;
const int maxp = 20;
const int maxd = 70;
const int MOD = 1000000009;

int n, P;
long long lo[maxn], hi[maxn];

int bound[maxn][maxd];

int flag[maxd][maxn][maxp][1 << maxn], flags;
int memo[maxd][maxn][maxp][1 << maxn];
int digits;

int go(int col, int row, int sum, int ls)
{
    if (row == n) {
        row = 0;
        sum = 0;
        if (++col == digits) {
            return 1;
        }
    }
    int &ret = memo[col][row][sum][ls];
    if (flag[col][row][sum][ls] == flags) {
        return ret;
    }
    flag[col][row][sum][ls] = flags;
    ret = 0;
    for (int i = 0; sum + i < P; i++) {
        if (ls >> row & 1 || i <= bound[row][col]) {
            ret += go(col, row + 1, sum + i, i < bound[row][col] ? ls | 1 << row : ls);
            if (ret >= MOD) {
                ret -= MOD;
            }
        }
    }
    return ret;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        scanf("%d%d", &n, &P);
        for (int i = 0; i < n; i++) {
            cin >> lo[i];
        }
        long long maxv = 0;
        for (int i = 0; i < n; i++) {
            cin >> hi[i];
            if (lo[i] > hi[i]) {
                swap(lo[i], hi[i]);
            }
            if (maxv < hi[i]) {
                maxv = hi[i];
            }
        }
        digits = 2;
        for (long long tmp = maxv; tmp; tmp /= P) {
            digits ++;
        }
        int ans = 0;
        for (int mask = 0; mask < 1 << n; ++mask) {
            int sign = 1;
            for (int i = 0; i < n; i++) {
                long long b = mask >> i & 1 ? lo[i] - 1 : hi[i];
                if (b < 0) {
                    sign = 0;
                    break;
                } else if (mask >> i & 1) {
                    sign *= -1;
                }
                for (int j = digits - 1; j >= 0; j--) {
                    bound[i][j] = b % P;
                    b /= P;
                }
            }
            if (sign != 0) {
                flags ++;
                ans = (ans + sign * go(0, 0, 0, 0)) % MOD;
            }
        }
        ans = (ans + MOD) % MOD;
        printf("Case %d: %d\n", cas, ans);
    }
}
