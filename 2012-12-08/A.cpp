#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 8;
const int maxp = 20;
const int maxd = 50;
const int MOD = 1000000009;

int n, P;
long long lo[maxn], hi[maxn];

int bound[maxn][maxd];

int memo2[maxn + 10][maxp];

int go2(int num, int sum)
{
    int &ret = memo2[num][sum];
    if (~ret) {
        return ret;
    }
    if (num == 0) {
        return ret = sum == 0 ? 1 : 0;
    }
    ret = 0;
    for (int i = 0; i <= sum && i < P; i++) {
        ret += go2(num - 1, sum - i);
        if (ret >= MOD) {
            ret -= MOD;
        }
    }
    return ret;
}

int flag[maxd][maxn][maxp][1 << maxn], flags;
int memo[maxd][maxn][maxp][1 << maxn];
int digits;

int go(int col, int row, int sum, int ls)
{
    int &ret = memo[col][row][sum][ls];
    if (flag[col][row][sum][ls] == flags) {
        return ret;
    }
    flag[col][row][sum][ls] = flags;
    while (row < n && ls >> row & 1) {
        row ++;
    }
    if (row == n) {
        if (col + 1 == digits) {
            return ret = 1;
        }
        int cntbit = __builtin_popcount(ls);
        ret = 0;
        for (int sum = 0; sum < P; sum++) {
            ret += (long long)go2(cntbit, sum) * go(col + 1, 0, sum, ls) % MOD;
            if (ret >= MOD) {
                ret -= MOD;
            }
        }
        return ret;
    }
    ret = 0;
    for (int i = 0; sum + i < P && i < bound[row][col]; i++) {
        ret += go(col, row + 1, sum + i, ls | 1 << row);
        if (ret >= MOD) {
            ret -= MOD;
        }
    }
    if (sum + bound[row][col] < P) {
        ret += go(col, row + 1, sum + bound[row][col], ls);
        if (ret >= MOD) {
            ret -= MOD;
        }
    }
    return ret;
}

int main()
{
    int T;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cin >> n >> P;
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
        memset(memo2, -1, sizeof(memo2));
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
