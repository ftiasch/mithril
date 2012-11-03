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

int compare(int a, int b)
{
    return a < b ? 0 : a == b ? 1 : 2;
}

struct Num
{
    int a, b, c, d, e;

    Num(){}

    Num(int n, int *perm) {
        a = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (perm[i] > perm[j]) {
                    a ++;
                }
            }
        }
        b = 0;
        for (int i = 1; i < n; i++) {
            if (perm[i - 1] > perm[i]) {
                b ++;
            }
        }
        static int lis[128];
        c = 0;
        for (int i = 0; i < n; i++) {
            lis[i] = 1;
            for (int j = 0; j < i; j++) {
                if (perm[j] < perm[i]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
            c = max(c, lis[i]);
        }
        d = 0;
        for (int i = 0; i < n; i++) {
            lis[i] = 1;
            if (i > 0 && perm[i - 1] < perm[i]) {
                lis[i] = max(lis[i], lis[i - 1] + 1);
            }
            d = max(d, lis[i]);
        }
        e = 0;
        for (int i = 0; i < n; i++) {
            if (perm[i] == i) {
                e ++;
            }
        }
    }

    bool operator<(const Num &o) const {
        return memcmp(this, &o, sizeof(Num)) < 0;
    }

    int encode(const Num &o) const {
        int ret = 0;
        ret = ret * 3 + compare(a, o.a);
        ret = ret * 3 + compare(b, o.b);
        ret = ret * 3 + compare(c, o.c);
        ret = ret * 3 + compare(d, o.d);
        ret = ret * 3 + compare(e, o.e);
        return ret;
    }
};

vector<int> expand(const vector<int> &a, int N)
{
    vector<int> ret;
    ret.push_back(a.size() + 1);
    for (int i = 0; i < a.size(); i++) {
        ret.push_back(a[i] + 1);
    }
    ret.push_back(0);
    while (ret.size() < N) {
        ret.push_back(ret.size());
    }
    reverse(ret.begin() + a.size() + 2, ret.end());
    return ret;
}

void print(const vector<int> &a)
{
    for (int i = 0; i < a.size(); i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", a[i] + 1);
    }
    puts("");
}

int main()
{
    freopen("juggle.in", "r", stdin);
    freopen("juggle.out", "w", stdout);
    int N, n, q;
    scanf("%d%d", &q, &N);
    if (N >= 9) {
        n = 7;
    } else {
        n = N;
    }
    static int perm[128];
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    map<Num,vector<int> > M1;
    do {
        bool valid = true;
        if (n < N) {
            bool decreasing = true;
            for (int i = 1; i < n; i++) {
                if (perm[i - 1] < perm[i]) {
                    decreasing = false;
                }
            }
            if (decreasing) {
                valid = false;
            }
        }
        if (valid) {
            M1[Num(n, perm)] = vector<int>(perm, perm + n);
        }
    } while (next_permutation(perm, perm + n));
    map<int, pair<Num, Num> > M2;
    FOR (it, M1) {
        FOR(jt, M1) {
            M2[it->first.encode(jt->first)] = make_pair(it->first, jt->first);
        }
    }
    while (q--) {
        static char input[128];
        scanf("%s", input);
        int encoding = 0;
        for (int i = 0; i < 5; i++) {
            encoding = encoding * 3 + string("<=>").find(input[i]);
        }
        if (!M2.count(encoding)) {
            puts("Not exists");
        } else {
            puts("Exists");
            vector<int> p = M1[M2[encoding].first];
            vector<int> q = M1[M2[encoding].second];
            if (n < N) {
                p = expand(p, N);
                q = expand(q, N);
            }
            print(p);
            print(q);
        }
    }
}
