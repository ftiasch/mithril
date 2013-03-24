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

const int maxn = 50;
const int maxm = 60;

int n, edges, f, m, q;
bool isFinish[maxn];
int next[maxn][2];

long long memo[maxm + 1][maxn];

long long go(int step, int pos)
{
    long long &ret = memo[step][pos];
    if (~ret) {
        return ret;
    }
    if (step == m) {
        return ret = isFinish[pos] ? 1 : 0;
    }
    ret = 0;
    for (int i = 0; i < 2; i++) {
        if (next[pos][i] >= 0) {
            ret += go(step + 1, next[pos][i]);
        }
    }
    return ret;
}

string query(long long year)
{
    string ret = "";
    int ptr = 0;
    for (int i = 0; i < m; i++) {
        bool found = false;
        for (int j = 0; j < 2; j++) {
            if (next[ptr][j] >= 0) {
                long long amount = go(i + 1, next[ptr][j]);
                if (year <= amount) {
                    found = true;
                    ptr = next[ptr][j];
                    ret += (char)('0' + j);
                    break;
                } else {
                    year -= amount;
                }
            }
        }
        assert(found);
    }
    assert(year == 1);
    return ret;
}

long long query(const string &s)
{
    long long ret = 0;
    int ptr = 0;
    for (int i = 0; i < m; i++) {
        int ch = s[i] - '0';
        for (int j = 0; j <= ch; j++) {
            if (next[ptr][j] >= 0) {
                if (j < ch) {
                    ret += go(i + 1, next[ptr][j]);
                } else if (j == ch) {
                    ptr = next[ptr][j];
                }
            }
        }
    }
    return ret + 1;
}

int main()
{
    scanf("%d%d%d%d%d", &n, &edges, &f, &m, &q);
    memset(next, -1, sizeof(next));
    for (int i = 0; i < edges; i++) {
        int ai, bi, ci;
        scanf("%d%d%d", &ai, &bi, &ci);
        ai --, bi --;
        next[ai][ci] = bi;
    }
    memset(isFinish, false, sizeof(isFinish));
    for (int i = 0; i < f; i++) {
        int fi;
        scanf("%d", &fi);
        fi --;
        isFinish[fi] = true;
    }
    memset(memo, -1, sizeof(memo));
    while (q --) {
        static char buf[1024];
        scanf("%s", buf);
        if (*buf == '?') {
            long long k;
            scanf("%lld", &k);
            puts(query(k).c_str());
        } else if (*buf == '!') {
            scanf("%s", buf);
            printf("%lld\n", query(string(buf)));
        } else if (*buf == '<') {
            scanf("%s", buf);
            puts(query(query(string(buf)) - 1).c_str());
        } else if (*buf == '>') {
            scanf("%s", buf);
            puts(query(query(string(buf)) + 1).c_str());
        } else {
            assert(false);
        }
    }

}
