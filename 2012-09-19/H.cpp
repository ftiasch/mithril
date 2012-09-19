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

const int maxn = 100000;

int n, k;
int faceUp[maxn], faceDown[maxn];
int faceUpP[maxn], nextPos[maxn];

int firstCard[maxn], whichCard[maxn], length[maxn];
int card[maxn], cards;

int main()
{
    freopen("kids.in", "r", stdin);
    freopen("kids.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", faceUp + i, faceDown + i);
        faceUp[i] --;
        faceDown[i] --;
        faceUpP[faceUp[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        nextPos[i] = faceUpP[faceDown[i]];
    }
    cards = 0;
    memset(firstCard, -1, sizeof(firstCard));
    for (int i = 0; i < n; i++) {
        if (firstCard[i] < 0) {
            int p = i;
            int rec = cards;
            length[rec] = 0;
            while (firstCard[p] < 0) {
                firstCard[p] = rec;
                whichCard[p] = cards - rec;
                length[rec] ++;
                card[cards++] = p;
                p = nextPos[p];
            }
        }
    }
    for (int i = 0; i < k; i++) {
        int num, times;
        scanf("%d%d", &num, &times);
        num --;
        int pos = firstCard[num];
        int res = card[pos + (whichCard[num] + times) % length[pos]];
        printf("%d\n", res + 1);
    }
}
