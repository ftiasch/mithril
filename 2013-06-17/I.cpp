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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int massP = 9705276;
const int massQ = 12805858;
const int inf = 1000000000;

long long extgcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        long long g = extgcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}

bool solve(long long n, long long &x, long long &y)
{
    // massP * x + massQ * y == n
    // 0 <= x, y <= 400
    long long g = extgcd(massP, massQ, x, y);
    if (n % g != 0) {
        return true;
    }
    x *= n / g;
    y *= n / g;
    long long deltaX = massQ / g, deltaY = massP / g;
    long long minX = (x % deltaX + deltaX) % deltaX;
    long long minY = (y % deltaY + deltaY) % deltaY;
    if (minX * massP + minY * massQ > n) {
        return false;
    }
    assert(minX * massP + minY * massQ == n); // claim unique solution
    x = minX;
    y = minY;
    return true;
}

long long readInt()
{
    static char str[100];
    scanf("%s", str);
    long long ans = 0;
    char *ptr = str;
    while (isdigit(*ptr)) {
        ans = ans * 10 + *ptr++ - '0';
    }
    if (*ptr != '.') {
        return ans * 100000;
    }
    ptr ++;
    for (int i = 0; i < 5; i++) {
        if (isdigit(*ptr)) {
            ans = ans * 10 + *ptr ++ - '0';
        } else {
            ans = ans * 10;
        }
    }
    return ans;
}

int sampleCount;
long long sample[100000];

int n, m, n2, m2;

int cnt[404][404];

int memo[202][402][402];

int go(int sum, int x1, int x2)
{
    int &ret = memo[sum][x1][x2];
    if (~ret) {
        return ret;
    }
    if (sum * 2 == n + m) {
        return ret = x1 == x2 ? 0 : -inf;
    }
    if (sum * 2 + 1 == n + m) {
        return ret = x1 == x2 || x1 + 1 == x2 ? 0 : -inf;
    }
    ret = -inf;
    int y1 = sum - x1, y2 = (n + m - sum) - x2;
    for (int p = 0; p < 2; p++) {
        for (int q = 0; q < 2; q ++) {
            int nx1 = x1 + p, ny1 = y1 + (1 - p);
            int nx2 = x2 - q, ny2 = y2 - (1 - q);
            if (nx1 >= 0 && nx1 <= n && ny1 >= 0 && ny1 <= m) {
                if (nx2 >= 0 && nx2 <= n && ny2 >= 0 && ny2 <= m) {
                    ret = max(ret, go(sum + 1, nx1, nx2) + cnt[nx1][ny1] + (nx1 + nx2 == n ? 0 : cnt[n - nx2][m - ny2]));
                }
            }
        }
    }
    return ret;
}

void construct(int sum, int x1, int x2, string &left, string &right)
{
    if (sum * 2 == n + m) {
        return;
    }
    if (sum * 2 + 1 == n + m) {
        if (x1 + 1 == x2) {
            left += 'P';
        } else {
            left += 'Q';
        }
        return;
    }
    int res = go(sum, x1, x2);
    int y1 = sum - x1, y2 = (n + m - sum) - x2;
    for (int p = 0; p < 2; p++) {
        for (int q = 0; q < 2; q ++) {
            int nx1 = x1 + p, ny1 = y1 + (1 - p);
            int nx2 = x2 - q, ny2 = y2 - (1 - q);
            if (nx1 >= 0 && nx1 <= n && ny1 >= 0 && ny1 <= m) {
                if (nx2 >= 0 && nx2 <= n && ny2 >= 0 && ny2 <= m) {
                    if (res == go(sum + 1, nx1, nx2) + cnt[nx1][ny1] + (nx1 + nx2 == n ? 0 : cnt[n - nx2][m - ny2])) {
                        left += p ? 'P' : 'Q';
                        right += q ? 'P' : 'Q';
                        construct(sum + 1, nx1, nx2, left, right);
                        return;
                    }
                }
            }
        }
    }
    assert(false);
}

int main()
{
    freopen("identification.in", "r", stdin);
    freopen("identification.out", "w", stdout);
    scanf("%d", &sampleCount);
    for (int i = 0; i < sampleCount; i++) {
        sample[i] = readInt();
    }
    sort(sample, sample + sampleCount);
    for (int i = sampleCount - 1; i >= 0; i--) {
        long long x, y;
        bool res = solve(sample[i], x, y);
        if (i + 1 == sampleCount) {
            assert(res);
            n = x;
            m = y;
            assert(n + m <= 400);
        } else if (res) {
            if (0 <= x && x <= n && 0 <= y && y <= m) {
                if ((x + y) * 2 > n + m) {
                    x = n - x;
                    y = m - y;
                }
                cnt[x][y] ++;
            }
        }
    }
    memset(memo, -1, sizeof(memo));
    string l, r;
    construct(0, 0, n, l, r);
    reverse(r.begin(), r.end());
    string ans = l + r;
    int cntP = 0, cntQ = 0;
    FOR (it, ans) {
        if (*it == 'P') {
            cntP ++;
        } else {
            cntQ ++;
        }
    }
    assert(cntP == n && cntQ == m);
    cout << ans << endl;
}
