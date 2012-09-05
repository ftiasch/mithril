#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;

ULL addMod(ULL a, ULL b, ULL mod) {
    a += b;
    if (a >= mod) {
        a -= mod;
    }
    return a;
}

ULL multiplyMod(ULL a, ULL b, ULL mod) {
    if (a < b) {
        return multiplyMod(b, a, mod);
    }
    ULL result = 0;
    while (b > 0) {
        if ((b & 1) == 1) {
            result = addMod(result, a, mod);
        }
        a = addMod(a, a, mod);
        b >>= 1;
    }
    return result;
}

ULL powMod(ULL a, ULL n, ULL mod) {
    ULL result = 1;
    while (n > 0) {
        if ((n & 1) == 1) {
            result = multiplyMod(result, a, mod);
        }
        a = multiplyMod(a, a, mod);
        n >>= 1;
    }
    return result;
}

bool primeTest(ULL n, ULL b) {
    ULL m = n - 1;
    int counter = 0;
    while ((m & 1) == 0) {
        m >>= 1;
        counter ++;
    }
    ULL ret = powMod(b, m, n);
    if (ret == 1 || ret == n - 1) {
        return true;
    }
    counter --;
    while (counter >= 0) {
        ret = multiplyMod(ret, ret, n);
        if (ret == n - 1) {
            return true;
        }
        counter --;
    }
    return false;
}

const int BASIC[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

bool isPrime(ULL n) {
    if (n < 2) {
        return false;
    }
    if (n < 4) {
        return true;
    }
    if (n == 3215031751LL) {
        return false;
    }
    for (int i = 0; i < 12 && BASIC[i] < n; ++ i) {
        if (!primeTest(n, BASIC[i])) {
            return false;
        }
    }
    return true;
}

ULL gcd(ULL a, ULL b) {
    return b == 0? a: gcd(b, a % b);
}

ULL abs(ULL a, ULL b) {
    return a < b? b - a: a - b;
}

ULL pollardRho(ULL n, ULL seed) {
    ULL x, y;
    x = y = rand() % (n - 1) + 1;
    ULL head = 1;
    ULL tail = 2;
    while (true) {
        x = multiplyMod(x, x, n);
        x = addMod(x, seed, n);
        if (x == y) {
            return n;
        }
        ULL d = gcd(abs(x, y), n);
        if (1 < d && d < n) {
            return d;
        }
        head ++;
        if (head == tail) {
            y = x;
            tail <<= 1;
        }
    }
}

vector <ULL> divisors;

void factorize(ULL n) {
    if (n > 1) {
        if (isPrime(n)) {
            divisors.push_back(n);
        } else {
            ULL d = n;
            while (d >= n) {
                d = pollardRho(n, rand() % (n - 1) + 1);
            }
            factorize(n / d);
            factorize(d);
        }
    }
}

int main() {
    int testCount;
    cin >> testCount;
    while (testCount > 0) {
        testCount --;
        ULL n;
        cin >> n;
        divisors.clear();
        factorize(n);
        sort(divisors.begin(), divisors.end());
        vector <ULL> anotherDivisors(divisors);
        int size = unique(anotherDivisors.begin(), anotherDivisors.end()) - anotherDivisors.begin();
        ULL sum = 0;
        for (int i = 0; i < (int)divisors.size(); ++ i) {
            int j = i;
            ULL product = 1;
            while (j < (int)divisors.size() && divisors[i] == divisors[j]) {
                product *= divisors[j ++];
            }
            sum += product;
            i = j - 1;
        }
        if (size == 1) {
            sum /= divisors.front();
        }
        cout << size << " " << sum << endl;
    }
    return 0;
}
