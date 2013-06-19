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

long long solve1(int a, long long lo, long long hi, bool canNeg = false)
{
    if (a == 0) {
        return lo <= 0 && 0 <= hi ? 1 : 0;
    }
    if (a < 0) {
        return solve1(-a, -hi, -lo, canNeg);
    }
    if (!canNeg) {
        lo = max(0LL, lo);
    }
    if (lo % a) {
        lo += a - (lo % a + a) % a;
    }
    if (hi % a) {
        hi -= (hi % a + a) % a;
    }
    return lo <= hi ? (hi - lo) / a + 1 : 0;
}

const int maxn = 10000;

int dist[maxn];
bool inQ[maxn];

long long solve(int a, int b, long long lo, long long hi)
{
    if (a == 0) {
        return solve1(b, lo, hi);
    }
    if (b == 0) {
        return solve1(a, lo, hi);
    }
    if (a == b) {
        return solve1(a, lo, hi);
    }
    if (a < 0 && b > 0 || a > 0 && b < 0) {
        return solve1(__gcd(a, b), lo, hi, true);
    }
    if (a < 0) {
        return solve(-a, -b, -hi, -lo);
    }
    if (a < b) {
        swap(a, b);
    }
    memset(dist, -1, sizeof(dist));
    memset(inQ, false, sizeof(inQ));
    dist[0] = 0;
    inQ[0] = true;
    queue<int> Q;
    Q.push(0);
    while (!Q.empty()) {
        int p = Q.front();
        Q.pop();
        inQ[p] = false;
        int q = p + b;
        int ndist = dist[p];
        if (q >= a) {
            q -= a;
            ndist ++;
        }
        if (dist[q] < 0 || ndist < dist[q]) {
            dist[q] = ndist;
            if (!inQ[q]) {
                inQ[q] = true;
                Q.push(q);
            }
        }
    }
    long long ret = 0;
    for (int i = 0; i < a; i++) {
        if (dist[i] < 0) {
            continue;
        }
        long long leastValue = (long long)a * dist[i] + i;
        if (leastValue < lo) {
            leastValue += (lo - leastValue + a - 1) / a * a;
        }
        if (leastValue <= hi) {
            ret += (hi - leastValue) / a + 1;
        }
    }
    return ret;
}

int main()
{
    int a, b;
    long long lo, hi;
    while (cin >> a >> b >> lo >> hi) {
        cout << solve(a, b, lo, hi) << endl;
    }
}
