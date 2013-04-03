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

struct State {
    int len;
    unsigned long long seq, validPrefix;

    State() : len(0), seq(0), validPrefix(0) {}

    bool append(bool bit) {
        len ++;
        seq <<= 1;
        if (bit) {
            seq ++;
        }
        validPrefix <<= 1;
        validPrefix ++;
        unsigned long long nValidPrefix = validPrefix;
        for (int i = 1; i * 2 <= len; i++) {
            int mask = (1ULL << i) - 1;
            if ((seq & mask) == (seq >> i & mask)) {
                nValidPrefix &= ~(1ULL << i + i - 1);
            }
        }
        bool valid = true;
        for (int i = 1, cnt = 0; i <= len; i++) {
            if (nValidPrefix >> len - i & 1) {
                cnt ++;
            }
            if (cnt * 2 < i) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            len --;
            seq >>= 1;
            validPrefix >>= 1;
            return false;
        }
        validPrefix = nValidPrefix;
        return true;
    }

    void print() {
        for (int i = len - 1; i >= 0; i--) {
            putchar (seq >> i & 1 ? '1' : '0');
        }
        puts("");
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    queue<State> Q;
    Q.push(State());
    vector<State> ans;
    while (!Q.empty()) {
        State p = Q.front();
        Q.pop();
        if (p.len == n) {
            ans.push_back(p);
        } else {
            State q = p;
            if (q.append(false)) {
                Q.push(q);
            }
            q = p;
            if (q.append(true)) {
                Q.push(q);
            }
        }
    }
    printf("%d\n", ans.size());
    FOR (it, ans) {
        it->print();
    }
}
