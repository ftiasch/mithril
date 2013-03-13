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
const long long MOD = 1000000LL * 1000000LL; // 10^12

bool isPrime(int a)
{
    if (a < 2) {
        return false;
    }
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

int n;
int parent[maxn];
int timestamp[maxn], times;

typedef vector<long long> BigInt;

BigInt &operator+=(BigInt &a, const BigInt &b)
{
    if (a.size() < b.size()) {
        a.resize(b.size(), 0);
    }
    int carry = 0;
    for (int i = 0; i < b.size(); i++) {
        a[i] += b[i] + carry;
        carry = a[i] / MOD;
        a[i] %= MOD;
    }
    for (int i = b.size(); i < a.size() || carry; i++) {
        if (i == a.size()) {
            a.push_back(0);
        }
        a[i] += carry;
        carry = a[i] / MOD;
        a[i] %= MOD;
    }
    return a;
}

BigInt &operator*=(BigInt &a, int b)
{
    if (b == 0) {
        a.assign(1, 0);
        return a;
    }
    assert(b > 0);
    int carry = 0;
    for (int i = 0; i < a.size() || carry; i++) {
        if (i == a.size()) {
            a.push_back(0);
        }
        a[i] = a[i] * b + carry;
        carry = a[i] / MOD;
        a[i] %= MOD;
    }
    return a;
}

BigInt &operator/=(BigInt &a, int b)
{
    assert(b > 0);
    int carry = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        a[i] += carry * MOD;
        carry = a[i] % b;
        a[i] /= b;
    }
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    return a;
}

int operator%(const BigInt &a, int b)
{
    assert(b > 0);
    int r = 0;
    for (int i = (int)a.size() - 1; i >= 0; i --) {
        r = (r * MOD + a[i]) % b;
    }
    return r;
}

int modInv(int a, int p)
{
    return a <= 1 ? a : (long long)(p - p / a) * modInv(p % a, p) % p;
}

void print(const BigInt &a)
{
    printf("%lld", a.back());
    for (int i = (int)a.size() - 2; i >= 0; i--) {
        printf("%.12lld", a[i]);
    }
    puts("");
}

inline int findRoot(int a)
{
    int r = a;
    while (parent[r] >= 0) {
        r = parent[r];
    }
    while (a != r) {
        int tmp = parent[a];
        parent[a] = r;
        a = tmp;
    }
    return r;
}

bool mergeComp(int a, int b)
{
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) {
        return false;
    }
    parent[a] = b;
    return true;
}

bool check(int x, int n)
{
    memset(parent, -1, sizeof(*parent) * n);
    int comps = n;
    for (int i = 2; i < n; i++) {
        if (!isPrime(i)) {
            continue;
        }
        int s = (i - x % i) % i;
        for (; s + i < n; s += i) {
            if (mergeComp(s, s + i)) {
                comps --;
            }
        }
    }
    return comps == 1;
}

int main()
{
    srand(4423);
    scanf("%d", &n);
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    for (int it = 0; it < 10000; ++it) {
        memset(parent, -1, sizeof(*parent) * n);
        int comps = n;
        vector<pair<int,int> > req;
        for (int step = 2; step < n && comps > 1; step++) {
            if (!isPrime(step)) {
                continue;
            }
            int maxHit = 2;
            vector<int> offsets;
            for (int offset = 0; offset < step; offset ++) {
                times ++;
                int hitComps = 0;
                for (int i = offset; i < n; i += step) {
                    int x = findRoot(i);
                    if (timestamp[x] != times) {
                        hitComps ++;
                        timestamp[x] = times;
                    }
                }
                if (hitComps > maxHit) {
                    maxHit = hitComps;
                    offsets.clear();
                    offsets.push_back(offset);
                } else if (hitComps == maxHit) {
                    offsets.push_back(offset);
                }
            }
            if (offsets.empty()) {
                continue;
            }
            int offset = offsets[(unsigned)rand() % offsets.size()];
            for (int i = offset + step; i < n; i += step) {
                if (mergeComp(i, offset)) {
                    comps --;
                }
            }
            int r = (step - offset) % step;
            // % step == r
            req.push_back(make_pair(step, r));
        }
        if (comps > 1) {
            continue;
        }
        BigInt mul(1, 1);
        FOR (it, req) {
            mul *= it->first;
        }
        BigInt sum(1, 0);
        FOR (it, req) {
            BigInt mul2 = mul;
            mul2 /= it->first;
            int inv = modInv(mul2 % it->first, it->first);
            int num = (long long)it->second * inv % it->first;
            mul2 *= num;
            sum += mul2;
        }
        print(sum);
        return 0;
    }
    for (int x = 1; x < 100000; ++x) {
        if (check(x, n)) {
            printf("%d\n", x);
            return 0;
        }
    }
    puts("No solution");
}
