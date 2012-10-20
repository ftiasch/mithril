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

const int maxn = 64;

int alphaSize, times, prefixLen;

char mapping[26][27];

char aprev[maxn], anext[maxn];

map<string, int> M;

int main()
{
    scanf("%d%d%d", &alphaSize, &times, &prefixLen);
    scanf("%s", aprev);
    for (int i = 0; i < alphaSize; i++) {
        scanf("%s", mapping[i]);
    }
    for (int i = 0; i <= times; i++) {
        if (i == times || M.count(aprev) && (times - i) % (i - M[aprev]) == 0) {
            putchar(prefixLen > strlen(aprev) ? '-' : aprev[prefixLen - 1]);
            puts("");
            return 0;
        }
        M[aprev] = i;
        int sz = 0;
        for (int i = 0; aprev[i] && sz < prefixLen; i++) {
            int ch = aprev[i] - 'A';
            for (int j = 0; mapping[ch][j] && sz < prefixLen; j++) {
                anext[sz++] = mapping[ch][j];
            }
        }
        anext[sz] = '\0';
        strcpy(aprev, anext);
    }
}
