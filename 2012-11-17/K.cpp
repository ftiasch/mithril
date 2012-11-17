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

const int maxn = 50000;

int n;
int cnt[500], p[maxn], w[maxn];

int perm[500][100];
int perm2[500];

bool cmp(int a, int b)
{
    return (long long)w[a] * p[b] > (long long)w[b] * p[a];
}

int main()
{
    freopen("student.in", "r", stdin);
    freopen("student.out", "w", stdout);
    scanf("%d", &n);
    int N = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", cnt + i);
        for (int j = 0; j < cnt[i]; j++) {
            perm[i][j] = N + j;
        }
        perm2[i] = i;
        N += cnt[i];
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", p + i);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", w + i);
    }
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        sort(perm[i], perm[i] + cnt[i], cmp);
        int sumP = 0, sumW = 0;
        for (int j = 0; j < cnt[i]; j++) {
            sumP += p[perm[i][j]];
            ret += (long long)sumP * w[perm[i][j]];
            sumW += w[perm[i][j]];
        }
        p[i] = sumP;
        w[i] = sumW;
    }
    sort(perm2, perm2 + n, cmp);
    int sumP = 0;
    for (int i = 0; i < n; i++) {
        int pi = perm2[i];
        ret += (long long)sumP * w[pi];
        sumP += p[pi];
    }
    cout << ret << endl;
    bool first = true;
    for (int i = 0; i < n; i++) {
        int p = perm2[i];
        for (int j = 0; j < cnt[p]; j++) {
            int q = perm[p][j];
            if (first) {
                first = false;
            } else {
                putchar(' ');
            }
            printf("%d", q + 1);
        }
    }
    puts("");
}
