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

int A, B;

const int OVER_VISA = 1;
const int OVER_NVISA = 2;
const int LOOP = 4;

int memo[256][26][2][27];

vector<vector<int> > adj[26];

int go(int stamp, int pos, int visA, int cycleRoot)
{
    if (pos == B) {
        return 0;
    }
    if (pos == A) {
        visA = 1;
    }
    int &ret = memo[stamp & 255][pos][visA][cycleRoot];
    if (~ret) {
        return ret;
    }
    ret = 0;
    if (visA) {
        ret = go(stamp + 1, pos, visA, pos);
    }
    FOR (it, adj[pos]) {
        int nVisA = visA;
        bool valid = true;
        FOR (jt, *it) {
            int res = go(stamp + 1, *jt, nVisA, cycleRoot);
            if (nVisA && *jt == cycleRoot) {
                ret |= LOOP;
            }
            if (res & LOOP) {
                ret |= LOOP;
            }
            if ((res & (OVER_VISA | OVER_NVISA)) == 0) {
                valid = false;
                break;
            }
            if (res & OVER_VISA) {
                nVisA = 1;
            }
        }
        if (valid) {
            if (nVisA) {
                ret |= OVER_VISA;
            } else {
                ret |= OVER_NVISA;
            }
        }
    }
    return ret;
}

char readToken()
{
    static char buf[1024];
    scanf("%s", buf);
    return *buf;
}

int main()
{
    int start = readToken() - 'A';
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int lhs = readToken() - 'A';
        readToken();
        static char buf[1 << 10];
        gets(buf);
        istringstream ssin(buf);
        vector<int> rhs;
        for (string s; ssin >> s;) {
            char ch = s[0];
            if (isupper(ch)) {
                rhs.push_back(ch - 'A');
            }
        }
        adj[lhs].push_back(rhs);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        A = readToken() - 'A';
        B = readToken() - 'A';
        memset(memo, -1, sizeof(memo));
        int res = go(0, start, 0, 26);
        puts(res & 5 ? "NO" : "YES");
    }
}
