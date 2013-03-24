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

const int maxn = 2222;

int n;
int a[maxn];
bool flag[maxn];

int opt[maxn], prev[maxn];

void move(int u, int v)
{
    if (u == v) {
        return;
    }
    int au = a[u];
    bool flagu = flag[u];
    if (u < v) {
        printf("L %d %d\n", u + 2, v + 1);
        for (int i = u; i < v; i++) {
            a[i] = a[i + 1];
            flag[i] = flag[i + 1];
        }
    } else {
        printf("R %d %d\n", v + 1, u);
        for (int i = u; i > v; i--) {
            a[i] = a[i - 1];
            flag[i] = flag[i - 1];
        }
    }
    a[v] = au;
    flag[v] = flagu;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < n; i++) {
        opt[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (a[j] <= a[i] && opt[i] < opt[j] + 1) {
                opt[i] = opt[j] + 1;
                prev[i] = j;
            }
        }
    }
    int lis = 0, ptr = -1;
    for (int i = 0; i < n; i++) {
        if (opt[i] > lis) {
            lis = opt[i];
            ptr = i;
        }
    }
    while (ptr >= 0) {
        flag[ptr] = true;
        ptr = prev[ptr];
    }
    printf("%d\n", n - lis);
    while (lis++ < n) {
        int pos = 0;
        while (flag[pos]) {
            pos ++;
        }
        int insPos = n;
        for (int i = 0; i < n; i++) {
            if (flag[i] && a[i] >= a[pos]) {
                insPos = i;
                break;
            }
        }
        flag[pos] = true;
        if (pos < insPos) {
            move(pos, insPos - 1);
        } else {
            move(pos, insPos);
        }
    }
}
