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

const int maxn = 555;
const int maxm = 2222;

string readString()
{
    char buf[1 << 10];
    scanf("%s", buf);
    return buf;
}

map<string,int> M;

int getSymbol(const string &s)
{
    if (M.count(s)) {
        return M[s];
    }
    int id = M.size();
    return M[s] = id;
}

int n;
string rhs1[maxn];
pair<int,int> rhs2[maxn];

int start;

int m;
string str;

int memo[maxn][maxm];

int go(int pos, int ptr)
{
    int &ret = memo[pos][ptr];
    if (~ret) {
        return ret;
    }
    if (rhs1[pos].size()) {
        int nptr = 0;
        while (ptr < m) {
            while (nptr < rhs1[pos].size() && rhs1[pos][nptr] != str[ptr]) {
                nptr ++;
            }
            if (nptr < rhs1[pos].size()) {
                nptr ++;
                ptr ++;
            } else {
                break;
            }
        }
        return ret = ptr;
    }
    ptr = go(rhs2[pos].first, ptr);
    ptr = go(rhs2[pos].second, ptr);
    return ret = ptr;
}

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        M.clear();
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int lhs = getSymbol(readString());
            readString(); //=
            string rhs = readString();
            if (islower(rhs[0])) {
                rhs1[lhs] = rhs;
            } else {
                rhs1[lhs] = "";
                rhs2[lhs].first = getSymbol(rhs);
                readString(); // +
                rhs2[lhs].second = getSymbol(readString());
            }
        }
        start = getSymbol(readString());
        assert(n == M.size());
        str = readString();
        m = str.size();
        memset(memo, -1, sizeof(memo));
        puts(go(start, 0) == m ? "YES" : "NO");
    }
}
