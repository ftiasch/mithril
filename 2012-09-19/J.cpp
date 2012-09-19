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

#include <ext/hash_map>

using namespace __gnu_cxx;

const int maxn = 10000;
const long long INF = 1LL << 60;

int decode(char ch) {
    return isdigit(ch) ? ch - '0' : ch - 'A' + 10;
}

char encode(int digit) {
    return digit < 10 ? digit + '0' : digit - 10 + 'A';
}

int digits[maxn];
int base;
int targetSum;

hash_map<int,long long> memo[maxn + 1][2];

long long go(int pos, int sum, int gt)
{
    if (sum > targetSum || sum + (base - 1) * (maxn - pos) < targetSum) {
        return 0;
    }
    if (memo[pos][gt].count(sum)) {
        return memo[pos][gt][sum];
    }
    long long &ret = memo[pos][gt][sum];
    if (pos == maxn) {
        return ret = gt ? 1 : 0;
    }
    ret = 0;
    for (int i = 0; i < base; i++) {
        if (gt || i >= digits[pos]) {
            ret += go(pos + 1, sum + i, gt || i > digits[pos]);
            if (ret >= INF) {
                return ret = INF;
            }
        }
    }
    return ret;
}

char ans[maxn + 10];

long long times;

bool solve(int pos, int sum, int gt)
{
    if (times > go(pos, sum, gt)) {
        times -= go(pos, sum, gt);
        return false;
    }
    if (pos == maxn) {
        if (gt) {
            for (int i = 0; i < maxn; i++) {
                ans[i] = encode(ans[i]);
            }
            int ptr = 0;
            while (ptr < maxn && ans[ptr] == '0') {
                ptr ++;
            }
            ans[maxn] = '\0';
            puts(ans + ptr);
            return true;
        }
        return false;
    }
    for (int i = 0; i < base; i++) {
        if (gt || i >= digits[pos]) {
            ans[pos] = i;
            if (solve(pos + 1, sum + i, gt || i > digits[pos])) {
                return true;
            }
        }
    }
    return false;
}

char str[maxn + 10];

int main()
{
    freopen("onearmedbandit.in", "r", stdin);
    freopen("onearmedbandit.out", "w", stdout);
    cin >> base >> times;
    scanf("%s", str);
    int len = strlen(str);
    memset(digits, 0, sizeof(digits));
    targetSum = 0;
    for (int i = 0; i < len; i++) {
        digits[maxn - 1 - i] = decode(str[len - 1 - i]);
        targetSum += digits[maxn - 1 - i];
    }
    for (int i = 0; i <= maxn; i++) {
        memo[i][0].clear();
        memo[i][1].clear();
    }
    if (!solve(0, 0, 0)) {
        puts("-1");
    }
}
