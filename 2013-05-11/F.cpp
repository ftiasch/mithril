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

const int maxn = 111111;

int n, nodes;
int next[maxn][26];
char str[maxn];

int leafCount[maxn];

int enableTab[maxn][2];

int main()
{
    memset(next, -1, sizeof(next));
    nodes = 1;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        int ptr = 0;
        for (int j = 0; str[j]; j++) {
            leafCount[ptr] ++;
            int ch = str[j] - 'a';
            if (next[ptr][ch] < 0) {
                next[ptr][ch] = nodes ++;
            }
            ptr = next[ptr][ch];
        }
        leafCount[ptr] ++;
    }
    for (int i = nodes - 1; i >= 0; i--) {
        int sum = 0;
        for (int j = 0; j < 26; j++) {
            int ch = next[i][j];
            if (ch >= 0) {
                sum += enableTab[ch][0] + leafCount[ch];
            }
        }
        for (int lastTab = 0; lastTab < 2; lastTab ++) {
            enableTab[i][lastTab] = sum;
            for (int j = 0; j < 26; j++) {
                int ch = next[i][j];
                if (ch >= 0) {
                    enableTab[i][lastTab] = min(enableTab[i][lastTab], sum - (enableTab[ch][0] + leafCount[ch]) + enableTab[ch][1] + (lastTab ? 0 : leafCount[ch]));
                }
            }
        }
    }
    printf("%d\n", enableTab[0][0]);
}
