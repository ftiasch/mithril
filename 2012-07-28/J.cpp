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

const int maxn = 11;

double A[maxn], B[maxn][maxn], C[maxn];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lf", A + i);
    }
    for (int i = 0; i < m; i++) {
        scanf("%lf", C + i);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%lf", &B[i][j]);
        }
    }
    double ret = 0;
    for (int msk = 0; msk < (1 << n); msk++) {
        double all = 1.0;
        for (int i = 0; i < n; i++) {
            if (msk >> i & 1) {
                all *= A[i];
            } else {
                all *= 1 - A[i];
            }
        }
        double targetNotReachable = 1.0;
        for (int i = 0; i < m; i++) {
            double riNotReachable = 1.0;
            for (int j = 0; j < n; j++) {
                if (msk >> j & 1) {
                    riNotReachable *= 1 - B[j][i];
                }
            }
            targetNotReachable *= 1 - (1 - riNotReachable) * C[i];
        }
        ret += all * (1 - targetNotReachable);
    }
    printf("%.10f\n", ret);
}
