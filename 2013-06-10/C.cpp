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

const int maxn = 111;
const int maxnodes = maxn * maxn;
const int inf = 1000000000;

int trieNodes;
int trieNext[maxnodes][26];
bool trieIsEnd[maxnodes];

int n, m;
char str[maxn], word[maxn];
int nextCh[maxn][26], nextPos[maxn];

int opt[maxn][maxn];

int flag[maxn][maxnodes], flags;
int memo[maxn][maxnodes];

int rightBorder;

int go(int pos, int node)
{
    int &ret = memo[pos][node];
    if (flag[pos][node] == flags) {
        return ret;
    }
    flag[pos][node] = flags;
    ret = inf;
    if (pos > rightBorder) {
        return ret;
    }
    if (pos == rightBorder && node == 0) {
        return ret = 0;
    }
    if (trieIsEnd[node]) {
        ret = min(ret, 1 + go(pos, 0));
    }
    for (int ch = 0; ch < 26; ch++) {
        int nnode = trieNext[node][ch];
        if (nnode >= 0) {
            int npos = nextCh[pos][ch];
            while (npos >= 0 && npos < rightBorder) {
                ret = min(ret, go(npos + 1, nnode) + opt[pos][npos]);
                npos = nextPos[npos];
            }
        }
    }
    return ret;
}

int main()
{
    scanf("%s", str);
    n = strlen(str);
    memset(nextCh[n], -1, sizeof(nextCh[n]));
    for (int i = n - 1; i >= 0; i--) {
        int ch = str[i] - 'a';
        memcpy(nextCh[i], nextCh[i + 1], sizeof(nextCh[i]));
        nextCh[i][ch] = i;
        nextPos[i] = nextCh[i + 1][ch];
    }
    memset(trieNext, -1, sizeof(trieNext));
    memset(trieIsEnd, false, sizeof(trieIsEnd));
    trieNodes = 1;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", word);
        int ptr = 0;
        for (int j = 0; word[j]; j++) {
            int ch = word[j] - 'a';
            if (trieNext[ptr][ch] < 0) {
                trieNext[ptr][ch] = trieNodes ++;
            }
            ptr = trieNext[ptr][ch];
        }
        trieIsEnd[ptr] = true;
    }
    for (rightBorder = 0; rightBorder <= n; rightBorder++) {
        flags ++;
        opt[rightBorder][rightBorder] = 0;
        for (int i = rightBorder - 1; i >= 0; i --) {
            opt[i][rightBorder] = go(i, 0);
        }
    }
    printf("%d\n", opt[0][n]);
}
