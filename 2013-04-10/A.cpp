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

const int DIGITS = 1 << 10;
const int MAXP = 1 << 16;

int vars;
char inputs[26][DIGITS];
char expression[1 << 20];


int evaluate(int mod)
{
    static int inputMod[26];
    for (int i = 0; i < vars; i++) {
        long long val = 0;
        for (const char *ptr = inputs[i]; *ptr; ptr++) {
            val = (val * 10 + *ptr - '0') % mod;
        }
        inputMod[i] = val;
    }
    static int stack[128];
    int sz = 0;
    for (const char *ptr = expression; *ptr; ptr++) {
        if (isupper(*ptr)) {
            stack[sz++] = inputMod[*ptr - 'A'];
        } else {
            int rhs = stack[--sz];
            int lhs = stack[--sz];
            if (*ptr == '+') {
                stack[sz++] = lhs + rhs >= mod ? lhs + rhs - mod : lhs + rhs;
            } else if (*ptr == '-') {
                stack[sz++] = lhs < rhs ? lhs + mod - rhs : lhs - rhs;
            } else if (*ptr == '*') {
                stack[sz++] = (long long)lhs * rhs % mod;
            }
        }
    }
    return stack[sz - 1];
}

bool isPrime[1 << 16];
vector<int> primes;

bool checkPrime(int a)
{
    FOR (it, primes) {
        if (*it * *it > a) {
            break;
        }
        if (a % *it == 0) {
            return false;
        }
    }
    return a >= 2;
}

int mods;
int m[DIGITS], a[DIGITS];

void prepare()
{
    memset(isPrime, true, sizeof(isPrime));
    for (int p = 2; p < MAXP; p++) {
        if (isPrime[p]) {
            primes.push_back(p);
            for (int i = p * 2; i < MAXP; i += p) {
                isPrime[i] = false;
            }
        }
    }
    double len10 = 0;
    mods = 0;
    for (int ptr = 100000 * 10000; len10 < DIGITS; ptr++) {
        while (!checkPrime(ptr)) {
            ptr ++;
        }
        m[mods ++] = ptr;
        len10 += log10((double)ptr);
    }
}

const int BASE = 10000 * 10000;

struct Integer
{
    vector<long long> digits;

    Integer(long long val = 0) : digits(1, val) {
        normalize();
    }

    Integer &normalize() {
        long long carry = 0;
        for (int i = 0; i < digits.size() || carry; i++) {
            if (i == digits.size()) {
                digits.push_back(0);
            }
            digits[i] += carry;
            long long ndigits = digits[i] % BASE;
            if (ndigits < 0) {
                ndigits += BASE;
            }
            carry = (digits[i] - ndigits) / BASE;
            digits[i] = ndigits;
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    Integer &operator+=(const Integer &o) {
        if (digits.size() < o.digits.size()) {
            digits.resize(o.digits.size(), 0);
        }
        for (int i = 0; i < o.digits.size(); i++) {
            digits[i] += o.digits[i];
        }
        return normalize();
    }

    Integer &operator-=(const Integer &o) {
        if (digits.size() < o.digits.size()) {
            digits.resize(o.digits.size(), 0);
        }
        for (int i = 0; i < o.digits.size(); i++) {
            digits[i] -= o.digits[i];
        }
        return normalize();
    }

    Integer &operator*=(int s) {
        for (int i = 0; i < digits.size(); i++) {
            digits[i] *= s;
        }
        return normalize();
    }

    Integer &operator/=(int s) {
        long long carry = 0;
        for (int i = digits.size() - 1; i >= 0; i --) {
            digits[i] += carry * BASE;
            carry = digits[i] % s;
            digits[i] /= s;
        }
        while (digits.size() > 0 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    Integer operator+(const Integer &o) const {
        Integer r = *this;
        return r += o;
    }

    Integer operator-(const Integer &o) const {
        Integer r = *this;
        return r -= o;
    }

    Integer operator*(int s) const {
        Integer r = *this;
        return r *= s;
    }

    Integer operator/(int s) const {
        Integer r = *this;
        return r /= s;
    }

    int operator%(int s) const {
        long long ret = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            ret = (ret * BASE + digits[i]) % s;
        }
        return ret;
    }

    int compareTo(const Integer &o) const {
        if (digits.size() != o.digits.size()) {
            return digits.size() < o.digits.size() ? -1 : 1;
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != o.digits[i]) {
                return digits[i] < o.digits[i] ? -1 : 1;
            }
        }
        return 0;
    }
};

int invMod(int a, int p)
{
    return a <= 1 ? a : (long long)(p - p / a) * invMod(p % a, p) % p;
}

ostream &operator<<(ostream &out, const Integer &o)
{
    out << o.digits.back();
    static char buf[16];
    for (int i = (int)o.digits.size() - 2; i >= 0; i--) {
        sprintf(buf, "%08d", (int)o.digits[i]);
        out << buf;
    }
    return out;
}

int main()
{
    prepare();
    scanf("%d", &vars);
    for (int i = 0; i < vars; i++) {
        scanf("%s", inputs[i]);
    }
    scanf("%s", expression);
    for (int i = 0; i < mods; i++) {
        a[i] = evaluate(m[i]);
    }
    Integer M = 1;
    for (int i = 0; i < mods; i++) {
        M *= m[i];
    }
    Integer ret = 0;
    for (int i = 0; i < mods; i++) {
        Integer Mi = M / m[i];
        int inv = invMod(Mi % m[i], m[i]);
        ret += Mi * ((long long)inv * a[i] % m[i]);
        if (ret.compareTo(M) >= 0) {
            ret -= M;
        }
    }
    cout << ret << endl;
}
