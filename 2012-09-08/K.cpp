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

const int maxn = 15;

int n;
int a[maxn];
int sum[1 << maxn];
int usum[1 << maxn], sums;
set<int> sets[1 << maxn];

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
        }
        sums = 0;
        for (int msk = 0; msk < 1 << n; msk ++) {
            sum[msk] = 0;
            for (int i = 0; i < n; i++) {
                if (msk >> i & 1) {
                    sum[msk] += a[i];
                }
            }
            usum[msk] = sum[msk];
        }
        sums = 1 << n;
        sort(usum, usum + sums);
        sums = unique(usum, usum + sums) - usum;
        for (int i = 0; i < sums; i++) {
            sets[i].clear();
        }
        for (int i = 0; i < 1 << n; i++) {
            sum[i] = lower_bound(usum, usum + sums, sum[i]) - usum;
        }
        int ans = 0;
        for (int msk = 0; msk < 1 << n; msk += 2) {
            for (int i = msk; i > 0; i = i - 1 & msk) {
                int A = sum[(1 << n) - 1 ^ msk], B = sum[msk ^ i], C = sum[i];
                if (A > B) {
                    swap(A, B);
                }
                if (B > C) {
                    swap(B, C);
                }
                if (A > B) {
                    swap(A, B);
                }
                if (A == 0 || usum[A] + usum[B] <= usum[C]) {
                    continue;
                }
                if (sets[A].insert(B).second) {
                    ans ++;
                }
            }
        }
        printf("%d\n", ans);
    }
}
