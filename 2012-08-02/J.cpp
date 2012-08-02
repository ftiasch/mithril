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

int powmod(int a, int b, int mod)
{
    a %= mod;
    int r = 1;
    while (b) {
        if (b & 1) {
            r = (long long)r * a % mod;
        }
        if (b >>= 1) {
            a = (long long)a * a % mod;
        }
    }
    return r;
}

const int maxn = 512;

int ma[maxn][maxn];

vector<int> eliminate(int n, int p)
{
    int r = 0, c = 0;
    vector<int> cols;
    while (r < n && c < n) {
        int pivot = r;
        while (pivot < n && ma[pivot][c] == 0) {
            pivot ++;
        }
        if (pivot == n) {
            c ++;
            continue;
        }
        for (int i = 0; i <= n; i++) {
            swap(ma[r][i], ma[pivot][i]);
        }
        int inv = powmod(ma[r][c], p - 2, p);
        for (int i = 0; i <= n; i++) {
            ma[r][i] = (long long)ma[r][i] * inv % p;
        }
        for (int i = 0; i < n; i++) {
            if (i != r && ma[i][c] > 0) {
                long long times = ma[i][c];
                for (int j = c; j <= n; j++) {
                    ma[i][j] = ma[i][j] - times * ma[r][j] % p;
                    if (ma[i][j] < 0) {
                        ma[i][j] += p;
                    }
                }
            }
        }
        cols.push_back(c);
        r ++;
        c ++;
    }
    vector<int> ret;
    for (int i = r; i < n; i++) {
        if (ma[i][n] != 0) {
            return ret;
        }
    }
    ret.assign(n, 0);
    for (int i = (int)cols.size() - 1; i >= 0; i--) {
        ret[cols[i]] = ma[i][n];
    }
    return ret;
}

int main()
{
    int n, p;
    scanf("%d%d", &p, &n);
    for (int i = 0; i < n; i++) {
        long long now = 1;
        for (int j = 0; j < n; j++) {
            now = now * (i + 1) % p;
            ma[i][j] = now;
        }
        scanf("%d", &ma[i][n]);
        ma[i][n] %= p;
    }
    vector<int> ans = eliminate(n, p);
    if (ans.empty()) {
        puts("-1");
    } else {
        for (int i = 0; i < ans.size(); i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", ans[i]);
        }
        puts("");
    }
}
