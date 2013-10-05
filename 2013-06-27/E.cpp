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
#include <climits>
#include <hash_map>
using namespace std;
using namespace __gnu_cxx;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int PLUS = 0;
const int MINUS = 1;
const int MUL = 2;

struct Expr
{
    vector<int> nums;
    vector<int> opers;

    Expr() : nums(1, 0), opers(0) {}

    Expr(const vector<int> &nums, const vector<int> &opers) : nums(nums), opers(opers) {}

    unsigned operator()(const Expr &e) const {
        unsigned ret = 0;
        FOR (it, e.nums) {
            ret = ret * 4423 + *it;
        }
        FOR (it, e.opers) {
            ret = ret * 4423 + *it;
        }
        return ret;
    }

    bool operator==(const Expr &e) const {
        return nums == e.nums && opers == e.opers;
    }
    void read() {
        int n;
        scanf("%d", &n);
        nums.resize(n + 1);
        opers.resize(n);
        for (int i = 0; i <= n; i++) {
            scanf("%d", &nums[i]);
            if (i < n) {
                static char buf[10];
                scanf("%s", buf);
                if (*buf == '+') {
                    opers[i] = PLUS;
                } else if (*buf == '-') {
                    opers[i] = MINUS;
                } else {
                    opers[i] = MUL;
                }
            }
        }
    }

    Expr apply(int pos) const {
        int res = 0;
        if (opers[pos] == PLUS) {
            res = nums[pos] + nums[pos + 1];
        } else if (opers[pos] == MINUS) {
            res = nums[pos] - nums[pos + 1];
        } else {
            res = nums[pos] * nums[pos + 1];
        }
        vector<int> nnum, noper;
        for (int i = 0; i < nums.size(); i++) {
            if (i == pos) {
                continue;
            }
            nnum.push_back(i == pos + 1 ? res : nums[i]);
        }
        for (int i = 0; i < opers.size(); i++) {
            if (i == pos) {
                continue;
            }
            noper.push_back(opers[i]);
        }
        return Expr(nnum, noper);
    }
};

hash_map<Expr, int, Expr> M;

int go(const Expr &expr, bool maxi, int *rec)
{
    if (expr.opers.empty()) {
        return expr.nums[0];
    }
    if (expr.opers.size() >= 5) {
        if (M.count(expr)) {
            return M[expr];
        }
    }
    int ret = maxi ? INT_MIN : INT_MAX;
    for (int pos = 0; pos < expr.opers.size(); pos ++) {
        int res = go(expr.apply(pos), !maxi, NULL);
        if (maxi) {
            if (ret < res) {
                ret = res;
                if (rec) {
                    *rec = pos;
                }
            }
        } else {
            if (ret > res) {
                ret = res;
                if (rec) {
                    *rec = pos;
                }
            }
        }
    }
    if (expr.opers.size() >= 5) {
        M[expr] = ret;
    }
    return ret;
}

int main()
{
    int tests;
    scanf("%d", &tests);
    for (int cas = 1; cas <= tests; ++cas) {
        Expr expr;
        expr.read();
        int pos1, res1, pos2, res2;
        M.clear();
        res1 = go(expr, true, &pos1);
        M.clear();
        res2 = go(expr, false, &pos2);
        printf("Case %d:\n", cas);
        printf("Player 1 (%d%c%d) leads to %d\n", expr.nums[pos1], "+-*"[expr.opers[pos1]], expr.nums[pos1 + 1], res1);
        printf("Player 2 (%d%c%d) leads to %d\n", expr.nums[pos2], "+-*"[expr.opers[pos2]], expr.nums[pos2 + 1], res2);
        if (res1 > -res2) {
            puts("Player 1 wins");
        } else if (res1 < -res2) {
            puts("Player 2 wins");
        } else {
            puts("Tie");
        }
    }
}
