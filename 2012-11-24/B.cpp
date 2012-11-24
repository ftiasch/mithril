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

const int maxn = 100001;
const long long INF = 1LL << 40;

char str[maxn];

vector<pair<int,int> > grammar[maxn];

int len, n, prefixACount;

long long countTimes[maxn][26];

long long mul(long long a, long long b)
{
    if (b == 0) {
        return 0;
    }
    if (a > INF / b) {
        return INF;
    }
    return a * b;
}

void addCount(long long *count, long long times, long long *count2)
{
    for (int i = 0; i < 26; i++) {
        count[i] = min(INF, count[i] + mul(times, count2[i]));
    }
}

void calcTimes(int p)
{
    memset(countTimes[p], 0, sizeof(countTimes[p]));
    FOR (it, grammar[p]) {
        if (it->first == 0) {
            if (countTimes[p][it->second] < INF) {
                countTimes[p][it->second] ++;
            }
        } else {
            calcTimes(it->second);
            addCount(countTimes[p], it->first, countTimes[it->second]);
        }
    }
}

void go(int p, int left, long long *count)
{
    FOR (it, grammar[p]) {
        if (it->first == 0) {
            if (count[it->second] < INF) {
                count[it->second] ++;
            }
            if (it->second == 0 && --left == 0) {
                return;
            }
        } else {
            long long timesA = countTimes[it->second][0];
            if (timesA == 0) {
                addCount(count, it->first, countTimes[it->second]);
            } else {
                long long bot = min((long long)it->first, left / timesA);
                if (bot * timesA == left) {
                    bot --;
                }
                addCount(count, bot, countTimes[it->second]);
                left -= timesA * bot;
                if (bot < it->first) {
                    go(it->second, left, count);
                    return;
                }
            }
        }
    }
}

int main()
{
    freopen("az.in", "r", stdin);
    freopen("az.out", "w", stdout);
    scanf("%s%d", str, &prefixACount);
    len = strlen(str);
    n = 0;
    vector<int> st;
    st.push_back(n ++);
    for (int i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            int times = 0;
            while (isdigit(str[i])) {
                times = times * 10 + str[i++] - '0';
            }
            assert(str[i] == '(');
            grammar[st.back()].push_back(make_pair(times, n));
            st.push_back(n ++);
        } else if (str[i] == ')') {
            st.pop_back();
        } else {
            assert(islower(str[i]));
            grammar[st.back()].push_back(make_pair(0, str[i] - 'a'));
        }
    }
    assert(st.size() == 1 && st[0] == 0);
    calcTimes(0);
    static long long count[26];
    memset(count, 0, sizeof(count));
    go(0, prefixACount, count);
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            if (count[i] > 1000000LL * 1000000LL) {
                count[i] = -1;
            }
            cout << (char)('a' + i) << " " << count[i] << endl;
        }
    }
}
