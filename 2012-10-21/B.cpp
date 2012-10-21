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

const int maxn = 201;

const int inf = 1000000000;

int memo[maxn][21][21][21][21];

int n, A, B;
int billy[maxn], willy[maxn], all[maxn];

int go(int pos, int a1, int b1, int a2, int b2)
{
    b1 = max(b1, 0);
    b2 = max(b2, 0);
    if (a1 == 0) {
        b1 = 0;
    } else if (b1 == 0) {
        a1 = 0;
    }
    if (a2 == 0) {
        b2 = 0;
    } else if (b2 == 0) {
        a2 = 0;
    }
    if (a1 > a2 || a1 == a2 && b1 > b2) {
        swap(a1, a2);
        swap(b1, b2);
    }
    int &ret = memo[pos][a1][b1][a2][b2];
    if (~ret) {
        return ret;
    }
    if (pos == n) {
        return ret = 0;
    }
    ret = inf;
    if (a1 < A || b1 < B) {
        ret = min(ret, go(pos, A, B, a2, b2) + 1);
    }
    if (a2 < A || b2 < B) {
        ret = min(ret, go(pos, a1, b1, A, B) + 1);
    }
    if (all[pos] == 0) {
        ret = min(ret, go(pos + 1, a1, b1 - 1, a2, b2 - 1));
    } else if (all[pos] == 2) {
        if (a1 >= 1 && a2 >= 1) {
            ret = min(ret, go(pos + 1, a1 - 1, b1 - 1, a2 - 1, b2 - 1));
        }
    } else {
        if (a1 >= 1) {
            ret = min(ret, go(pos + 1, a1 - 1, b1 - 1, a2, b2 - 1));
        }
        if (a2 >= 1) {
            ret = min(ret, go(pos + 1, a1, b1 - 1, a2 - 1, b2 - 1));
        }
    }
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &A, &B);
    for (int i = 0; i < n; i++) {
        scanf("%d", billy + i);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", willy + i);
    }
    int minv = 1 << 30;
    for (int it = 0; it < 8; ++it) {
        int ret = 0;
        for (int i = 0; i < n; i++) {
            all[i] = billy[i] + willy[i];
        }
        for (int i = 0; i < n; i++) {
            if (all[i] >= 2) {
                vector<int> pos;
                for (int j = i; j < i + B; j++) {
                    if (all[j] == 2) {
                        pos.push_back(j);
                    }
                }
                if (pos.size() >= A) {
                    if (it > 1) {
                        random_shuffle(pos.begin() + 1, pos.end());
                    } else if (it == 1) {
                        reverse(pos.begin() + 1, pos.end());
                    }
                    for (int j = 0; j < pos.size() && j < A; j++) {
                        all[pos[j]] --;
                    }
                    ret ++;
                }
            }
        }
        memset(memo, -1, sizeof(memo));
        minv = min(minv, ret + go(0, 0, 0, 0, 0));
    }
    printf("%d\n", minv);
    return 0;
}
