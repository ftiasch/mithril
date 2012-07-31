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

const int H = 0;
const int V = 1;
const int S = 2;

int nextState[20000][3];
int states, initState, finalState;
int badState, expectS;

int main()
{
    int m;
    scanf("%d", &m);
    badState = m << m;
    states = (m << m) + 1;
    initState = finalState = 0;
    nextState[badState][H] = badState;
    nextState[badState][V] = badState;
    nextState[badState][S] = badState;
    for (int row = 0; row < m; row++) {
        int nrow = (row + 1) % m;
        for (int msk = 0; msk < (1 << m); msk++) {
            int state = row << m | msk;
            if (msk >> row & 1) {
                nextState[state][H] = badState;
            } else {
                nextState[state][H] = nrow << m | msk | 1 << row;
            }
            if (nrow == 0 || msk >> row & 1 || msk >> nrow & 1) {
                nextState[state][V] = badState;
            } else {
                nextState[state][V] = nrow << m | msk | 1 << nrow;
            }
            if (~msk >> row & 1) {
                nextState[state][S] = badState;
            } else {
                nextState[state][S] = nrow << m | msk & ~(1 << row);
            }
        }
    }
    printf("%d %d\n", states, initState + 1);
    printf("1 %d\n", finalState + 1);
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < 3; j++) {
            if (j > 0) {
                putchar(' ');
            }
            printf("%d", nextState[i][j] + 1);
        }
        puts("");
    }
}
