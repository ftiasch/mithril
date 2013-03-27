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

const int HAPPY = 5;
const int maxn = 200 << 20;

int nextBit[5][2];
int direct[5][2];
int nextState[5][2];

unsigned mem[maxn / 32 * 2 + 100];

int main()
{
    for (int state = 0; state < 5; state++) {
        for (int bit = 0; bit < 2; bit++) {
            char buf[10];
            scanf("%s", buf);
            nextBit[state][bit] = string("01").find(buf[0]);
            direct[state][bit] = string("LR").find(buf[1]);
            nextState[state][bit] = string("ABCDEH").find(buf[2]);
        }
    }
    int ptr = maxn + 3;
    int state = 0;
    for (int step = 0; step < maxn; step++) {
        int bit = mem[ptr >> 5] >> (ptr & 31) & 1;
        mem[ptr >> 5] &= ~(1 << (ptr & 31));
//printf("%d %d %d\n", ptr, state, bit);
        mem[ptr >> 5] |= nextBit[state][bit] << (ptr & 31);
        ptr += direct[state][bit] ? 1 : -1;
        state = nextState[state][bit];
        
        if (state == HAPPY) {
            puts("happy beaver");
            return 0;
        }
    }
    puts("unhappy beaver");
}
