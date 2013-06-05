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

const int maxn = 100000;

int n, k, nk;
int offsetK, offsetNK[maxn + 1];

void add(int l, int r, int delta)
{
    l = ((l - offsetK) % k + k) % k;
    r = ((r - offsetK) % k + k) % k;
    (offsetNK[l] += delta) %= nk;
    (offsetNK[r] -= delta) %= nk;
    if (l >= r) {
        (offsetNK[k] -= delta) %= nk;
        (offsetNK[0] += delta) %= nk;
    }
}

int q;
int type[maxn], len[maxn];

int input[maxn], output[maxn];

int main()
{
    scanf("%d%d%d", &n, &k, &q);
    nk = n / k;
    offsetK = 0;
    memset(offsetNK, 0, sizeof(offsetNK));
    for (int i = 0; i < q; i ++) {
        scanf("%d%d", type + i, len + i);
    }
    for (int i = q - 1; i >= 0; i--) {
        int offset;
        if (type[i] == 1) {
            offset = ((-len[i]) % k + k) % k;
            offsetK = ((offsetK + offset) % k + k) % k;
        } else {
            offset = ((-len[i]) % n + n) % n;
            int mid = k - offset % k, delta = offset / k;
            add(0, mid, delta);
            if (mid != k) {
                add(mid, k, delta + 1);
            }
            offsetK = ((offsetK + offset % k) % k + k) % k;
        }
    }
    for (int i = 0; i < k; i++) {
        (offsetNK[i + 1] += offsetNK[i]) %= nk;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", output + i);
    }
    for (int i = 0; i < k; i++) {
        int offset = (i + offsetK) % k - i + offsetNK[i] * k;
        offset = (offset % n + n) % n;
        for (int j = i; j < n; j += k) {
            input[(j + offset) % n] = output[j];
        }
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", input[i]);
    }
    puts("");
}
