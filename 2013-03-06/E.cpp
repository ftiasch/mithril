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

const int N = 31;
const int RULES = 28;
const int MAXC = 31;

const string rules[RULES] = {
    "1 2",
    "3 4 5 6 7",
    "8 9 10 11 12 13",
    "14 15 16 17 18",
    "19 20 21 22 23 24",
    "25 26 27 28 29",
    "30 31",
    
    "3 8",
    "1 4 9 14 19",
    "2 5 10 15 20 25",
    "6 11 16 21 26",
    "7 12 17 22 27 30",
    "13 18 23 28 31",
    "24 29",

    "19 25",
    "8 14 20 26 30",
    "3 9 15 21 27 31",
    "4 10 16 22 28",
    "1 5 11 17 23 29",
    "2 6 12 18 24",
    "7 13",

    "1 2 4 5 6 10 11",
    "3 4 8 9 10 14 15",
    "6 7 11 12 13 17 18",
    "10 11 15 16 17 21 22",
    "14 15 19 20 21 25 26",
    "17 18 22 23 24 28 29",
    "21 22 26 27 28 30 31"
};

bool conflict[N][N];
vector<int> adj[N];

void prepare()
{
    memset(conflict, false, sizeof(conflict));
    for (int i = 0; i < RULES; i++) {
        istringstream ssin(rules[i]);
        vector<int> rule;
        for (int val; ssin >> val; ) {
            rule.push_back(val - 1);
        }
        FOR (it, rule) {
            FOR (jt, rule) {
                conflict[*it][*jt] = true;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && conflict[i][j]) {
                adj[i].push_back(j);
            }
        }
    }
}

int num, colors;

int coloring[N];

int used[N][MAXC];
int empty[N];

bool paint(int pos, int c)
{
    bool ret = true;
    assert(coloring[pos] < 0);
    coloring[pos] = c;
    FOR (it, adj[pos]) {
        if (used[*it][c]++ == 0) {
            if (--empty[*it] == 0) {
                ret = false;
            }
        }
    }
    return ret;
}

void unpaint(int pos)
{
    assert(coloring[pos] >= 0);
    int c = coloring[pos];
    coloring[pos] = -1;
    FOR (it, adj[pos]) {
        if (--used[*it][c] == 0) {
            empty[*it] ++;
        }
    }
}

bool dfs(int dep)
{
    while (dep < N && coloring[dep] >= 0) {
        dep ++;
    }
    if (dep == N) {
        if (--num == 0) {
            puts("Found");
            for (int i = 0; i < N; i++) {
                if (i) {
                    putchar(' ');
                }
                printf("%d", coloring[i] + 1);
            }
            puts("");
            return true;
        }
        return false;
    }
    for (int i = 0; i < colors; i++) {
        if (used[dep][i] != 0) {
            continue;
        }
        if (paint(dep, i) && dfs(dep + 1)) {
            return true;
        }
        unpaint(dep);
    }
    return false;
}

int main()
{
    prepare();
    scanf("%d%d", &colors, &num);
    bool valid = true;
    for (int i = 0; i < N; i++) {
        empty[i] = colors;
    }
    memset(coloring, -1, sizeof(coloring));
    for (int i = 0; i < N; i++) {
        int ci;
        scanf("%d", &ci);
        ci --;
        if (ci >= 0) {
            if (used[i][ci]) {
                valid = false;
                break;
            }
            paint(i, ci);
        }
    }
    if (!valid || !dfs(0)) {
        puts("No way");
    }
}
