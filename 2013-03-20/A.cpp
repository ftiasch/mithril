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

const int maxn = 1 << 21;

bool isPrime[maxn];

int main()
{
    memset(isPrime, true, sizeof(isPrime));
    isPrime[1] = false;
    for (int i = 2; i * i < maxn; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < maxn; j += i) {
                isPrime[j] = false;
            }
        }
    }
    unsigned long long n, p;
    cin >> p;
    n = p - 1;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    vector<unsigned long long> factors;
    for (int i = 1; i < maxn; i++) {
        if (isPrime[i]) {
            if (n % i == 0) {
                factors.push_back(i);
                while (n % i == 0) {
                    n /= i;
                }
            }
        }
    }
    if (n > 1) {
        unsigned long long sqrtn = (unsigned long long)sqrt((double)n);
        if (sqrtn * sqrtn == n) {
            factors.push_back(sqrtn);
        } else {
            factors.push_back(n);
        }
    }
    n = p - 1;
    FOR (it, factors) {
        n /= *it;
    }
    if (n % 2 == 1) {
        n *= 2;
    }
    cout << n << endl;
}
