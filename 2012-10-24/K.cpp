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

const int MAXN = 111111;

const int HASHMOD = 999997;
const int STATES = MAXN * 15;

const int BASE = 4423;

bool cmp(const char *a, const char *b)
{
    return strcmp(a, b) < 0;
}

int states;
unsigned long long keys[STATES];
int values[STATES];
int nextPair[STATES];

int firstPair[HASHMOD];

void insertHash(unsigned long long val)
{
    int ptr = val % HASHMOD;
    for (int e = firstPair[ptr]; e != -1; e = nextPair[e]) {
        if (keys[e] == val) {
            values[e] ++;
            return;
        }
    }
    nextPair[states] = firstPair[ptr];
    keys[states] = val;
    values[states] = 1;
    firstPair[ptr] = states ++;
}

int queryHash(unsigned long long val)
{
    int ptr = val % HASHMOD;
    for (int e = firstPair[ptr]; e != -1; e = nextPair[e]) {
        if (keys[e] == val) {
            return values[e];
        }
    }
    return false;
}

int n, m;

char keyvalue[MAXN][4][16];

int main()
{
    memset(firstPair, -1, sizeof(firstPair));
    states = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int tokens;
        scanf("%d", &tokens);
        vector<char*> strs;
        for (int j = 0; j < tokens; j++) {
            scanf("%s", keyvalue[i][j]);
            strs.push_back(keyvalue[i][j]);
        }
        sort(strs.begin(), strs.end(), cmp);
        for (int mask = 1; mask < 1 << tokens; mask++) {
            unsigned long long hash = 0;
            for (int j = 0; j < tokens; j++) {
                if (mask >> j & 1) {
                    char *ptr = strs[j];
                    do {
                        hash = hash * BASE + *ptr;
                    } while (*ptr++);
                }
            }
            insertHash(hash);
        }
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int tokens;
        scanf("%d", &tokens);
        vector<char*> strs;
        for (int j = 0; j < tokens; j++) {
            scanf("%s", keyvalue[i][j]);
            strs.push_back(keyvalue[i][j]);
        }
        sort(strs.begin(), strs.end(), cmp);
        unsigned long long hash = 0;
        for (int j = 0; j < tokens; j++) {
            char *ptr = strs[j];
            do {
                hash = hash * BASE + *ptr;
            } while (*ptr++);
        }
        printf("%d\n", queryHash(hash));
    }
    return 0;
}
