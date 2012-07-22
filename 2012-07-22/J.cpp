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

const int MOD = 10007;

int inv[MOD];

struct Polynomial
{
    vector<int> coeff;

    Polynomial(const vector<int> coeff) : coeff(coeff) {}

    Polynomial operator+(const Polynomial &o) const {
        vector<int> ncoeff = coeff;
        if (ncoeff.size() < o.coeff.size()) {
            ncoeff.resize(o.coeff.size());
        }
        for (int i = 0; i < o.coeff.size(); i++) {
            ncoeff[i] += o.coeff[i];
            ncoeff[i] %= MOD;
        }
        return Polynomial(ncoeff);
    }

    Polynomial operator*(const Polynomial &o) const {
        vector<int> ncoeff(max(0, (int)coeff.size() + (int)o.coeff.size() - 1));
        for (int i = 0; i < coeff.size(); i++) {
            for (int j = 0; j < o.coeff.size(); j++) {
                ncoeff[i + j] += coeff[i] * o.coeff[j] % MOD;
                ncoeff[i + j] %= MOD;
            }
        }
        return Polynomial(ncoeff);
    }

    Polynomial operator*(int scale) const {
        vector<int> ncoeff = coeff;
        scale %= MOD;
        for (int i = 0; i < ncoeff.size(); i++) {
            ncoeff[i] *= scale;
            ncoeff[i] %= MOD;
        }
        return Polynomial(ncoeff);
    }
};

int bruteForce(int n)
{
    int a[6];
    int ret = 0;
    for (a[0] = 1; a[0] <= n; a[0] ++) {
        for (a[1] = 1; a[1] <= n; a[1] ++) {
            for (a[2] = 1; a[2] <= n; a[2] ++) {
                for (a[3] = 1; a[3] <= n; a[3] ++) {
                    for (a[4] = 1; a[4] <= n; a[4] ++) {
                        a[5] = a[0];
                        int mul = 1;
                        for (int i = 0; i < 5; i++) {
                            mul *= abs(a[i] - a[i+1]);
                            mul %= MOD;
                        }
                        ret += mul;
                        ret %= MOD;
                    }
                }
            }
        }
    }
    return ret;
}

void solve()
{
    for (int i = 1; i < MOD; i++)
        for (int j = 1; j < MOD; j++)
            if (i * j % MOD == 1)
                inv[i] = j;
    vector<int> x, y;
    for (int i = 3; i <= 20; i++) {
        x.push_back(i);
        y.push_back(bruteForce(i));
    }
    int n = x.size();
    Polynomial ret(vector<int>(0));
    for (int i = 0; i < n; i++) {
printf("%d %d\n", x[i], y[i]);
        Polynomial mul(vector<int>(1, 1));
        for (int j = 0; j < n; j++) {
            if (j != i) {
                Polynomial term(vector<int>(0));
                term.coeff.push_back((MOD-x[j]) % MOD);
                term.coeff.push_back(1.0);
                term = term * (inv[((x[i] - x[j]) % MOD + MOD) % MOD]);
                mul = mul * term;
            }
        }
        mul = mul * y[i];
        ret = ret + mul;
    }
    for (int i = 0; i < ret.coeff.size(); i++) {
        printf("%d\n", ret.coeff[i]);
    }
}
/*
 * 0
 * 0
 * 1652
 * 0
 * 6080
 * 0
 * 5995
 * 0
 * 9226
 * 0
 * 7068
 */

int main()
{
    int n;
    while (cin >> n && n) {
        n %= MOD;
        long long ret = 0;
        ret = (ret * n * n + 7068) % MOD;
        ret = (ret * n * n + 9226) % MOD;
        ret = (ret * n * n + 5995) % MOD;
        ret = (ret * n * n + 6080) % MOD;
        ret = (ret * n * n + 1652) % MOD;
        ret = (ret * n * n + 0) % MOD;
        cout << ret << endl;
    }
}
