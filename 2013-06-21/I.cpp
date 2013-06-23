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

const int maxn = 100011;

int len[2], a[2][maxn];

int cnt[maxn];
set<pair<int,int> > S;
int side = -1;

void add(int x, int delta)
{
    int val = a[side ^ 1][x];
    S.erase(make_pair(cnt[val], val));
    cnt[val] += delta;
    S.insert(make_pair(cnt[val], val));
}

int main()
{
    for (int i = 0; i < 2; i++) {
        scanf("%d", &len[i]);
        for (int j = 0; j < len[i]; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 0) {
                side = i;
            }
        }
    }
    if (side >= 0) {
        int L = 0, R = 0;
        for (int i = 0; i < len[side]; i++) {
            if (a[side][i] == 0) {
                int nL, nR;
                if (len[side] <= len[side ^ 1]) {
                    nL = i;
                    nR = len[side ^ 1] - (len[side] - i);
                } else {
                    nL = max(0, len[side ^ 1] - (len[side] - i));
                    nR = min(len[side ^ 1], i);
                }
                nR ++;
                assert(L <= nL);
                assert(R <= nR);
                while (R < nR) {
                    add(R++, 1);
                }
                while (L < nL) {
                    add(L++, -1);
                }
                if (S.empty()) {
                    a[side][i] = 4423;
                } else {
                    a[side][i] = (--S.end()) -> second;
                }
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < len[i]; j++) {
            if (j) {
                putchar(' ');
            }
            printf("%d", a[i][j]);
        }
        puts("");
    }
}
