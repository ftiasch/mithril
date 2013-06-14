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

const int maxn = 200;
const int maxm = maxn * maxn / 2;
const int limit = 1000000000;
const long long limit2 = limit * 1LL * limit;

long long findA(long long ab, long long ac, long long bc)
{
    while (true) {
        bool changed = false;
        long long g = __gcd(ab, bc);
        if (g > 1) {
            changed = true;
            ab /= g;
            bc /= g;
        }
        g = __gcd(ac, bc);
        if (g > 1) {
            changed = true;
            ac /= g;
            bc /= g;
        }
        if (!changed) {
            break;
        }
    }
    if (bc != 1) {
        return 0;
    }
    if (ab > limit2 / ac) {
        return 0;
    }
    long long a2 = ab * ac;
    long long a = sqrt((double)a2);
    while (a * a < a2) {
        a ++;
    }
    if (a * a == a2) {
        return a;
    }
    return 0;
}

int n, m;
long long a[maxm];

vector<long long> solve(long long x0)
{
    vector<long long> x(1, x0);
    multiset<long long> S(a, a + m);
    for (int i = 1; i < n; i++) {
        long long xi = -1;
        FOR (it, S) {
            if (*it % x0 == 0) {
                xi = *it / x0;
                break;
            }
        }
        if (xi < 2 || xi > limit) {
            return vector<long long>(0);
        }
        FOR (jt, x) {
            multiset<long long>::iterator it = S.find(*jt * xi);
            if (it == S.end()) {
                return vector<long long>(0);
            }
            S.erase(it);
        }
        if (xi <= x.back()) {
            return vector<long long>(0);
        }
        x.push_back(xi);
    }
    return x;
}

int main()
{
    int tests;
    scanf("%d", &tests);
    for (int cas = 1; cas <= tests; ++cas) {
        scanf("%d", &n);
        m = n * (n - 1) / 2;
        for (int i = 0; i < m; i++) {
            scanf("%lld", a + i);
        }
        sort(a, a + m);
        set<long long> possibleX0;
        for (int i = 2; i <= n; i++) {
            long long x0 = findA(a[0], a[1], a[i]);
            if (x0 >= 2 && x0 <= limit) {
                possibleX0.insert(x0);
            }
        }
        printf("Case %d:", cas);
        bool found = false;
        FOR (it, possibleX0) {
            vector<long long> ans = solve(*it);
            if (!ans.empty()) {
                sort(ans.begin(), ans.end());
                FOR (jt, ans) {
                    printf(" %lld", *jt);
                }
                puts("");
                found = true;
                break;
            }
        }
        if (!found) {
            puts(" Impossible");
        }
    }
}
