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

const int maxn = 1600;

char input[maxn][maxn];
int n;

unsigned depart[maxn][maxn >> 5], arrive[maxn][maxn >> 5];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", input[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (input[i][j] == '+') {
                depart[i][j >> 5] |= 1U << (j & 31);
                arrive[j][i >> 5] |= 1U << (i & 31);
            }
        }
    }
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (input[j][i] == '+') {
                for (int k = 0; k < (maxn >> 5); k++) {
                    ret += __builtin_popcount(depart[i][k] & arrive[j][k]);
                }
            }
        }
    }
    cout << ret / 3 << endl;
}
