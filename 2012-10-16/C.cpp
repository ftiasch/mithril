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

const int MOD = 3 << 18 | 1;
const int PRIMITIVE_ROOT = 10;
const int MAXB = 1 << 20;

int modinv(int a)
{
    return a <= 1 ? a : (long long)(MOD - MOD / a) * modinv(MOD % a) % MOD;
}

long long powmod(long long a, int b)
{
    a %= MOD;
    long long r = 1;
    while (b) {
        if (b & 1) {
            r = r * a % MOD;
        }
        if (b >>= 1) {
            a = a * a % MOD;
        }
    }
    return r;
}

void NTT(int P[], int n, int oper)
{
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        long long unit_p0 = powmod(PRIMITIVE_ROOT, (MOD - 1) / m2);
        if (oper < 0) {
            unit_p0 = modinv(unit_p0);
        }
        for (int i = 0; i < n; i += m2) {
            long long unit = 1;
            for (int j = 0; j < m; j++) {
                int &P1 = P[i + j + m], &P2 = P[i + j];
                int t = unit * P1 % MOD;
                P1 = (P2 - t + MOD) % MOD;
                P2 = (P2 + t) % MOD;
                unit = unit * unit_p0 % MOD;
            }
        }
    }
}

vector<int> mul(const vector<int> &a, const vector<int> &b)
{
    vector<int> ret(max(0, (int)a.size() + (int)b.size() - 1), 0);
    static int A[MAXB], B[MAXB], C[MAXB];
    int len = 1;
    while (len < ret.size()) {
        len *= 2;
    }
    for (int i = 0; i < len; i++) {
        A[i] = i < a.size() ? a[i] : 0;
        B[i] = i < b.size() ? b[i] : 0;
    }
    NTT(A, len, 1);
    NTT(B, len, 1);
    for (int i = 0; i < len; i++) {
        C[i] = (long long)A[i] * B[i] % MOD;
    }
    NTT(C, len, -1);
    int inv = modinv(len);
    for (int i = 0; i < ret.size(); i++) {
        ret[i] = (long long)C[i] * inv % MOD;
    }
    return ret;
}

void add(vector<int> &a, const vector<int> &b, int delta = 1)
{
    if (a.size() < b.size()) {
        a.resize(b.size(), 0);
    }
    for (int i = 0; i < b.size(); i++) {
        a[i] = (a[i] + b[i] * delta % MOD + MOD) % MOD;
    }
}

vector<int> all[17];

int main()
{
    int n, h;
    scanf("%d%d", &n, &h);
    h ++;
    all[0].push_back(1);
    all[1].push_back(0);
    all[1].push_back(1);
    for (int i = 2; i <= h; i++) {
        all[i].assign(1, 0);
        add(all[i], mul(all[i - 1], all[i - 1]));
        add(all[i], mul(all[i - 2], all[i - 1]), 2);
        all[i].insert(all[i].begin(), 0);
    }
    printf("%d\n", n >= all[h].size() ? 0 : all[h][n]);
}
