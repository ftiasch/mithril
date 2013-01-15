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
#define ID(a, b) ((a) << 1 | (b))

const int maxn = 222;
const int maxm = 444;
const int maxnodes = maxn * 2;

vector<int> adj[maxnodes], rev[maxnodes];

void addEdge(int a, int b)
{
    adj[a].push_back(b);
    rev[b].push_back(a);
}

int color[maxnodes], colors;
vector<int> order;

void dfs1(int p)
{
    color[p] = 1;
    FOR (q, adj[p]) {
        if (color[*q] == 0) {
            dfs1(*q);
        }
    }
    order.push_back(p);
}

void dfs2(int p)
{
    color[p] = colors;
    FOR (q, rev[p]) {
        if (color[*q] < 0) {
            dfs2(*q);
        }
    }
}

int n, m;
int diagonal[maxn];
int input[maxm][maxn];

int choicesByColumn[maxn][2];
bool conflicts[maxm][maxm];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", diagonal + i);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &input[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        vector<int> choices;
        for (int j = 0; j < m; j++) {
            if (diagonal[i] == input[j][i]) {
                choices.push_back(j);
            }
        }
        assert(choices.size() <= 2);
        if (choices.empty()) {
            puts("NO");
            return 0;
        }
        choicesByColumn[i][0] = choices[0];
        if (choices.size() == 2) {
            choicesByColumn[i][1] = choices[1];
        } else {
            choicesByColumn[i][1] = 0;
            addEdge(ID(i, 1), ID(i, 0));
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            bool valid = true;
            for (int k = 0; k < n; k++) {
                if (input[i][k] == input[j][k]) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                conflicts[i][j] = true;
            }
        }
    }
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if ((i >> 1) == (j >> 1)) {
                continue;
            }
            int a = choicesByColumn[i >> 1][i & 1];
            int b = choicesByColumn[j >> 1][j & 1];
            if (conflicts[a][b]) {
                addEdge(i, j ^ 1);
                addEdge(j, i ^ 1);
            }
        }
    }
    memset(color, 0, sizeof(color));
    order.clear();
    for (int i = 0; i < 2 * n; i++) {
        if (color[i] == 0) {
            dfs1(i);
        }
    }
    memset(color, -1, sizeof(color));
    colors = 0;
    for (int i = 2 * n - 1; i >= 0; i--) {
        if (color[order[i]] < 0) {
            dfs2(order[i]);
            colors ++;
        }
    }
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (color[ID(i, 0)] == color[ID(i, 1)]) {
            found = true;
        }
    }
    if (found) {
        puts("NO");
        return 0;
    }
    puts("YES");
    for (int i = 0; i < n; i++) {
        int id = color[ID(i, 0)] > color[ID(i, 1)] ? 0 : 1;
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", choicesByColumn[i][id] + 1);
    }
    puts("");
}
