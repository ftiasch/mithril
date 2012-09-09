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

int getCode(char ch)
{
    if (ch >= 'z') {
        ch --;
    }
    if (ch >= 's') {
        ch --;
    }
    return (ch - 'a') / 3 + 2;
}

const int maxn = 10000;

char inputs[maxn][10], word[10];

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%s", inputs[i]);
        }
        map<string,int> M;
        for (int i = 0; i < m; i++) {
            scanf("%s", word);
            int len = strlen(word);
            for (int j = 0; j < len; j++) {
                word[j] = '0' + getCode(word[j]);
            }
            M[word]++;
        }
        for (int i = 0; i < n; i++) {
            printf("%d\n", M[inputs[i]]);
        }
    }
}

