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

const int FACES = 6;
const int DICES = 8;
const int SCORE = 40;

bool seen[1 << FACES][DICES][SCORE + 1];
double memo[1 << FACES][DICES][SCORE + 1];

double fact[DICES + 1], ifact[DICES + 1];

void prepare()
{
    fact[0] = ifact[0] = 1;
    for (int i = 1; i <= DICES; i++) {
        fact[i] = fact[i - 1] * i;
        ifact[i] = ifact[i - 1] / i;
    }
}

double go(int mask, int dices, int leftScore)
{
    leftScore = max(0, leftScore);
    double &ret = memo[mask][dices][leftScore];
    if (seen[mask][dices][leftScore]) {
        return ret;
    }
    seen[mask][dices][leftScore] = true;
    ret = 0;
    if (mask & 1) {
        // give up if worm exists
        if (leftScore == 0) {
            return ret = 1;
        }
    }
    if (dices > 0) {
        int c[6];
#define cw c[0]
#define c1 c[1]
#define c2 c[2]
#define c3 c[3]
#define c4 c[4]
#define c5 c[5]
        double sum = 0;
        for (cw = 0; cw <= dices; cw++) {
            for (c1 = 0; cw + c1 <= dices; c1++) {
                for (c2 = 0; cw + c1 + c2 <= dices; c2++) {
                    for (c3 = 0; cw + c1 + c2 + c3 <= dices; c3++) {
                        for (c4 = 0; cw + c1 + c2 + c3 + c4 <= dices; c4++) {
                            c5 = dices - cw - c1 - c2 - c3 - c4;
                            double prob = fact[dices];
                            for (int i = 0; i < 6; i++) {
                                prob *= ifact[c[i]];
                            }
                            double maxv = 0;
                            for (int i = 0; i < 6; i++) {
                                if (c[i] > 0 && ~mask >> i & 1) {
                                    maxv = max(maxv, go(mask | 1 << i, dices - c[i], leftScore - (i == 0 ? 5 : i) * c[i]));
                                }
                            }
                            sum += maxv * prob;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < dices; i++) {
            sum /= 6;
        }
        ret = max(ret, sum);
    }
    return ret;
}

int main()
{
    prepare();
    memset(seen, false, sizeof(seen));
    int tests, n;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d", &n);
        printf("%.20f\n", go(0, DICES, n));
    }
}
