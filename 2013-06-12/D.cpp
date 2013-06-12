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

const int inf = 1000000000;

int main()
{
    long long n, N;
    cin >> n;
    N = n;
    vector<long long> primeFactors;
    for (long long f = 2; f * f <= n; f++) {
        if (n % f == 0) {
            int cnt = 0;
            while (n % f == 0) {
                n /= f;
                cnt ++;
            }
            N /= f;
            primeFactors.push_back(f);
        }
    }
    if (n > 1) {
        N /= n;
        primeFactors.push_back(n);
    }
    vector<long long> divisors;
    for (long long f = 1; f * f <= N; f ++) {
        if (N % f == 0) {
            divisors.push_back(f);
            if (f * f < N) {
                divisors.push_back(N / f);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    set<long long> S(divisors.begin(), divisors.end());
    S.erase(1);
    FOR (it, primeFactors) {
        S.erase(*it);
    }
    vector<int> opt(divisors.size(), -inf);
    opt[0] = 0;
    FOR (it, S) {
        int ptr = divisors.size();
        for (int i = (int)divisors.size() - 1; i >= 0; i--) {
            while (ptr > 0 && divisors[ptr - 1] > divisors[i] / *it) {
                ptr --;
            }
            if (ptr == 0) {
                break;
            }
            if (*it * divisors[ptr - 1] == divisors[i]) {
                opt[i] = max(opt[i], opt[ptr - 1] + 1);
            }
        }
    }
    int maxi = *max_element(opt.begin(), opt.end());
    cout << maxi + (int)primeFactors.size() << endl;
}
