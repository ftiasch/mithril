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

const int maxn = 1000;
const int MOD = 1000000007;

char str[maxn];
int len;

int cntI[maxn], cntO[maxn], cntQ[maxn];

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        scanf("%s", str);
        len = strlen(str);
        for (int i = 0; i < len; i++) {
            cntI[i + 1] = cntI[i];
            cntO[i + 1] = cntO[i];
            cntQ[i + 1] = cntQ[i];
            if (str[i] == 'R') {
                cntI[i + 1] ++;
            } else if (str[i] == 'G') {
                cntO[i + 1] ++;
            } else {
                cntQ[i + 1] ++;
            }
        }
        int ans = 1;
        for (int i = 0; i < cntQ[len]; i++) {
            ans = ans * 2 % MOD;
        }
        // no I
        if (cntI[len] == 0) {
            ans --;
        }
        // one I
        for (int i = 0; i < len; i++) {
            if (cntI[i] != 0) {
                continue;
            }
            if (cntO[i + 1] - cntO[i] != 0) {
                continue;
            }
            if (cntI[len] - cntI[i + 1] == 0) {
                ans --;
            }
            // multiple I
            for (int j = i + 1; j < len; j += 2) {
                int delta = j - i;
                for (int k = i + delta; k < len; k += delta) {
                    if (cntI[k] - cntI[k - delta + 1] != 0) {
                        break;
                    }
                    if (cntO[k + 1] - cntO[k] != 0) {
                        break;
                    }
                    if (cntI[len] - cntI[k + 1] == 0) {
                        ans --;
                    }
                }
            }
        }
        ans %= MOD;
        ans += MOD;
        ans %= MOD;
        printf("%d\n", ans);
    }
}
