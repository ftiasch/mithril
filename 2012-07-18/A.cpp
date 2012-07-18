// Problem A -- Casino
// Author: Bin Jin
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

const int maxn = 128;

int n, m, s;
double p[maxn];
int w[maxn];

double prob[maxn];
int wys[maxn];

inline void touch(int pos)
{
    prob[pos] = -1.0;
    for (int i = 0; i < m; i++) {
        double nprob = p[i] * prob[pos + w[i]] + (1 - p[i]) * prob[pos - 1];
        if (nprob > prob[pos]) {
            prob[pos] = nprob;
            wys[pos] = i;
        }
    }
}

double ma[maxn][maxn];

void GE()
{
    for (int i = 0; i < n; i++) {
        int r = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(ma[j][i]) > fabs(ma[r][i])) {
                r = j;
            }
        for (int j = 0; j <= n; j++) {
            swap(ma[r][j], ma[i][j]);
        }
        for (int j = n; j >= i; j--) {
            ma[i][j] /= ma[i][i];
        }
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            for (int k = n; k >= i; k--)
                ma[j][k] -= ma[i][k] * ma[j][i];
        }
    }
}

int main()
{
    while (scanf("%d%d%d", &n, &m, &s) == 3) {
        for (int i = 0; i < m; i++) {
            int pi;
            scanf("%d%d", &pi, &w[i]);
            p[i] = (double)pi / s;
        }
        prob[0] = 0;
        for (int i = n + 1; i < maxn; i++)
            prob[i] = 1.0;
        memset(wys, 0, sizeof(wys));
        for (int it = 0; it < 50; ++it) {
            for (int jt = 0; jt < 1000; ++jt) {
                for (int i = 1; i < n; i++)
                    touch(i);
                for (int i = n; i >= 1; i--)
                    touch(i);
            }
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= n; j++)
                    ma[i-1][j] = 0.0;
                ma[i-1][i-1] += 1.0;
                if (i == 1) {
                    ma[i-1][n] += 0;
                } else {
                    ma[i-1][i-1-1] -= 1-p[wys[i]];
                }
                if (i + w[wys[i]] > n) {
                    ma[i-1][n] += p[wys[i]];
                } else {
                    ma[i-1][i+w[wys[i]]-1] -= p[wys[i]];
                }
            }
            GE();
            for (int i = 1; i <= n; i++)
                prob[i] = ma[i-1][n];
        }
        printf("%.10f\n", prob[n]);
    }
}
