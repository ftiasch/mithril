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

const int maxn = 1024;

char str[maxn];

int times[26];
double pow_neg2[maxn];

int main()
{
    freopen("random-strings.in", "r", stdin);
    freopen("random-strings.out", "w", stdout);
    pow_neg2[0] = 1;
    for (int i = 1; i < maxn; i++) {
        pow_neg2[i] = pow_neg2[i - 1] * 0.5;
    }
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        scanf("%s", str);
        double prob1 = 0, prob2 = 0;
        memset(times, 0, sizeof(times));
        int n = strlen(str);
        for (int i = 0; i < n; i ++) {
            int ch = str[i] - 'a';
            int minv = *min_element(times, times + 26);
            double sum = 0;
            for (int j = 0; j < 26; j++) {
                times[j] -= minv;
                sum += pow_neg2[times[j]];
            }
            // prob1 *= 1 / 26
            prob1 -= log(26.0);
            // prob2 *= weight[ch] / sum
            // weight[ch] = 2^{-times[ch]}
            prob2 += (-times[ch]) * log(2.0) - log(sum);
            times[ch] ++;
        }
        if (prob1 > prob2) {
            puts("FIRST");
        } else {
            puts("SECOND");
        }
    }
}
