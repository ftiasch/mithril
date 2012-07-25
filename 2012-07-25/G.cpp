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

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int N = 4;
const int E = N * N - 4 * 2;

#define INRANGE(X, Y) (0 <= (X) && (X) < 4 && 0 <= (Y) && (Y) < 4)
#define CODE(X, Y) ((X) * 4 + (Y))

const int MAXL = 48;
const int MAXP = 656;
const int MAXS = 19000;

vector<int> maskL;
int maskLabel[1 << 16];

vector<pair<int,int> > nonOverlapL;
int pairLabel[MAXL][MAXL];

int emptyCells[MAXP][E];
int stateLabel[MAXP][E][E];

int states;
vector<int> adj[MAXS];
vector<int> rev[MAXS];

int outdegree[MAXS];

bool win[MAXS];
bool lose[MAXS];

void prepare()
{
    maskL.clear();
    memset(maskLabel, -1, sizeof(maskLabel));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int d2 = 0; d2 < 4; d2++) {
                for (int d3 = 0; d3 < 4; d3++) {
                    if (dx[d2] * dx[d3] + dy[d2] * dy[d3] != 0) {
                        continue;
                    }
                    if (!INRANGE(i + dx[d2] * 1, j + dy[d2] * 1)) {
                        continue;
                    }
                    if (!INRANGE(i + dx[d3] * 2, j + dy[d3] * 2)) {
                        continue;
                    }
                    int mask = 0;
                    mask |= 1 << CODE(i, j);
                    mask |= 1 << CODE(i + dx[d2], j + dy[d2]);
                    mask |= 1 << CODE(i + dx[d3], j + dy[d3]);
                    mask |= 1 << CODE(i + dx[d3] * 2, j + dy[d3] * 2);
                    maskLabel[mask] = maskL.size();
                    maskL.push_back(mask);
                }
            }
        }
    }
    fprintf(stderr, "number of L : %d\n", maskL.size());
    assert(maskL.size() == MAXL);
    nonOverlapL.clear();
    memset(pairLabel, -1, sizeof(pairLabel));
    for (int i = 0; i < maskL.size(); i++) {
        for (int j = 0; j < maskL.size(); j++) {
            if ((maskL[i] & maskL[j]) == 0) {
                pairLabel[i][j] = nonOverlapL.size();
                nonOverlapL.push_back(make_pair(maskL[i], maskL[j]));
            }
        }
    }
    fprintf(stderr, "number of non-overlapping L pairs : %d\n", nonOverlapL.size());
    assert(nonOverlapL.size() == MAXP);
    states = 0;
    memset(stateLabel, -1, sizeof(stateLabel));
    for (int i = 0; i < nonOverlapL.size(); i++) {
        int sz = 0;
        for (int j = 0; j < 16; j++) {
            if (nonOverlapL[i].first >> j & 1 || nonOverlapL[i].second >> j & 1) {
                continue;
            }
            emptyCells[i][sz++] = j;
        }
        for (int e1 = 0; e1 < E; e1 ++) {
            for (int e2 = 0; e2 < e1; e2++) {
                stateLabel[i][e1][e2] = states ++;
            }
        }
    }
    fprintf(stderr, "number of states : %d\n", states);
    for (int i = 0; i < states; i++) {
        adj[i].clear();
        rev[i].clear();
    }
    for (int i = 0; i < nonOverlapL.size(); i++) {
        int myMask = nonOverlapL[i].first;
        int yourMask = nonOverlapL[i].second;
        for (int e1 = 0; e1 < E; e1 ++) {
            for (int e2 = 0; e2 < e1; e2++) {
#define MASK_CODE(M1, M2) (pairLabel[maskLabel[M1]][maskLabel[M2]])
                for (int j = 0; j < maskL.size(); j++) {
                    int cell1 = emptyCells[i][e1], cell2 = emptyCells[i][e2];
                    int myNewMask = maskL[j];
                    if (myNewMask == myMask || myNewMask & yourMask) {
                        continue;
                    }
                    if (myNewMask >> cell1 & 1 || myNewMask >> cell2 & 1) {
                        continue;
                    }
                    int code = MASK_CODE(yourMask, myNewMask);
                    cell1 = find(emptyCells[code], emptyCells[code] + E, cell1) - emptyCells[code];
                    cell2 = find(emptyCells[code], emptyCells[code] + E, cell2) - emptyCells[code];
                    adj[stateLabel[i][e1][e2]].push_back(stateLabel[code][max(cell1, cell2)][min(cell1, cell2)]);
                    for (int cell = 0; cell < E; cell++) {
                        if (cell != cell1 && cell != cell2) {
                            adj[stateLabel[i][e1][e2]].push_back(stateLabel[code][max(cell, cell2)][min(cell, cell2)]);
                            adj[stateLabel[i][e1][e2]].push_back(stateLabel[code][max(cell1, cell)][min(cell1, cell)]);
                        }
                    }
                }
            }
        }
    }
    int transfers = 0;
    for (int i = 0; i < states; i++) {
        transfers += adj[i].size();
        for (int j = 0; j < adj[i].size(); j++) {
            rev[adj[i][j]].push_back(i);
        }
    }
    fprintf(stderr, "number of ways to transfer states : %d\n", transfers);
    queue<int> Q;
    int ending = 0;
    for (int i = 0; i < states; i++) {
        outdegree[i] = adj[i].size();
        win[i] = lose[i] = false;
        if (outdegree[i] == 0) {
            ending ++;
            lose[i] = true;
            Q.push(i);
        }
    }
    fprintf(stderr, "ending losing states : %d\n", ending);
    int wins = 0, loses = 0;
    while (!Q.empty()) {
        int p = Q.front();
        Q.pop();
        if (win[p]) {
            wins ++;
        } else if (lose[p]) {
            loses ++;
        }
        for (int i = 0; i < rev[p].size(); i++) {
            int q = rev[p][i];
            if (win[q] || lose[q]) {
                continue;
            }
            if (lose[p]) {
                win[q] = true;
                Q.push(q);
            } else if (--outdegree[q] == 0) {
                lose[q] = true;
                Q.push(q);
            }
        }
    }
    fprintf(stderr, "winning states : %d\n", wins);
    fprintf(stderr, "losing states : %d\n", loses);
    fprintf(stderr, "draw states : %d\n", states - wins - loses);
}

int readState()
{
    char buf[10][10];
    for (int i = 0; i < 4; i++) {
        scanf("%s", buf[i]);
    }
    int mask1 = 0, mask2 = 0;
    vector<int> emptys;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int code = CODE(i, j);
            if (buf[i][j] == '#') {
                mask1 |= 1 << code;
            } else if (buf[i][j] == '*') {
                mask2 |= 1 << code;
            } else if (buf[i][j] == 'x') {
                emptys.push_back(code);
            }
        }
    }
    assert(maskLabel[mask1] >= 0);
    assert(maskLabel[mask2] >= 0);
    int code = MASK_CODE(mask1, mask2);
    assert(code >= 0);
    assert(emptys.size() == 2);
    int e1 = find(emptyCells[code], emptyCells[code] + E, emptys[0]) - emptyCells[code];
    int e2 = find(emptyCells[code], emptyCells[code] + E, emptys[1]) - emptyCells[code];
    return stateLabel[code][max(e1, e2)][min(e1, e2)];
}

void printState(int state)
{
    for (int i = 0; i < nonOverlapL.size(); i++) {
        for (int e1 = 0; e1 < E; e1++) {
            for (int e2 = 0; e2 < e1; e2++) {
                if (stateLabel[i][e1][e2] == state) {
                    int mask1 = nonOverlapL[i].first;
                    int mask2 = nonOverlapL[i].second;
                    int emptys = 1 << emptyCells[i][e1] | 1 << emptyCells[i][e2];
                    for (int x = 0; x < 4; x++) {
                        for (int y = 0; y < 4; y++) {
                            int z = CODE(x, y);
                            if (mask1 >> z & 1) {
                                putchar('*');
                            } else if (mask2 >> z & 1) {
                                putchar('#');
                            } else if (emptys >> z & 1) {
                                putchar('x');
                            } else {
                                putchar('.');
                            }
                        }
                        putchar('\n');
                    }
                    return;
                }
            }
        }
    }
    assert(false);
}

int main()
{
    prepare();
    int state = readState();
    if (win[state]) {
        bool found = false;
        for (int i = 0; i < adj[state].size(); i++) {
            int nstate = adj[state][i];
            if (lose[nstate]) {
                printState(nstate);
                found = true;
                break;
            }
        }
        assert(found);
    } else {
        puts("No winning move exists");
        puts(lose[state] ? "Losing" : "Draw");
    }
}
