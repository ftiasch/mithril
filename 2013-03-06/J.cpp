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

const int BASE = 1000000;

struct BigInt
{
    vector<int> digits;

    BigInt(int num = 0) : digits(1, num) {
        normalize();
    }

    BigInt &normalize() {
        int carry = 0;
        for (int i = 0; i < digits.size() || carry; i++) {
            if (i == digits.size()) {
                digits.push_back(0);
            }
            digits[i] += carry;
            carry = digits[i] / BASE;
            digits[i] %= BASE;
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    BigInt &operator+=(const BigInt &o) {
        if (digits.size() < o.digits.size()) {
            digits.resize(o.digits.size(), 0);
        }
        for (int i = 0; i < o.digits.size(); i++) {
            digits[i] += o.digits[i];
        }
        return normalize();
    }

    BigInt &operator*=(int val) {
        for (int i = 0; i < digits.size(); i++) {
            digits[i] *= val;
        }
        return normalize();
    }

    BigInt operator*(int val) const {
        BigInt cp = *this;
        return cp *= val;
    }

    void print() const {
        printf("%d", digits.back());
        for (int i = (int)digits.size() - 2; i >= 0; i--) {
            printf("%06d", digits[i]);
        }
        puts("");
    }
};

const int maxn = 11111;

char digits[maxn];
int n;

BigInt memo[maxn][2][2];
bool seen[maxn][2][2];

int ways[20];

BigInt go(int pos, int leftCarry, int rightCarry)
{
    BigInt &ret = memo[pos][leftCarry][rightCarry];
    if (seen[pos][leftCarry][rightCarry]) {
        return ret;
    }
    seen[pos][leftCarry][rightCarry] = true;
    if (pos + pos == n) {
        return ret = leftCarry == rightCarry ? 1 : 0;
    } else if (pos + pos + 1 == n) {
        int cnt = 0;
        for (int i = 0; i < 10; i++) {
            if (pos == 0 && i == 0) {
                continue;
            }
            int sum = i * 2 + rightCarry;
            if (sum == leftCarry * 10 + (digits[pos] - '0')) {
                cnt ++;
            }
        }
        return ret = cnt;
    }
    ret = 0;
    for (int s = 0; s <= 18; s++) {
        int ws = ways[s] - (pos == 0 && s <= 9 ? 1 : 0);
        int leftNum = s, rightNum = s + rightCarry;
        int nLeftCarry = leftNum % 10 == (digits[pos] - '0') ? 0 : 1;
        if (leftNum + nLeftCarry != leftCarry * 10 + (digits[pos] -'0')) {
            continue;
        }
        if (rightNum % 10 != (digits[n - 1 - pos] - '0')) {
            continue;
        }
        int nRightCarry = rightNum / 10;
        ret += go(pos + 1, nLeftCarry, nRightCarry) * ws;
    }
    return ret;
}

int main()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            ways[i + j] ++;
        }
    }
    while (scanf("%s", digits) == 1 && strcmp(digits, "0") != 0) {
        n = strlen(digits);
        memset(seen, 0, sizeof(seen[0]) * (n + 10) / 2);
        BigInt ans = go(0, 0, 0);
        if (n > 1 && digits[0] == '1') {
            memmove(digits, digits + 1, n);
            n --;
            memset(seen, 0, sizeof(seen[0]) * (n + 10) / 2);
            ans += go(0, 1, 0);
        }
        ans.print();
    }
}
