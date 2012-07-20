// Problem J -- Wikipedia
// Author: Bin Jin
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

const int maxn = 1 << 18;

char str[maxn];

int pos[maxn], n, len;
int ans[maxn];

bool vis2in3[maxn], vis3in2[maxn];
int is2[maxn], is3[maxn];

int isOkay[maxn], is2or3[maxn];

int main()
{
    fgets(str, maxn, stdin);
    len = strlen(str);
    n = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '\'') {
            pos[n++] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        is2[i] = i + 2 <= n && pos[i] + 1 == pos[i + 1];
        is3[i] = i + 3 <= n && pos[i] + 1 == pos[i + 1] && pos[i] + 2 == pos[i + 2];
    }
    memset(vis2in3, false, sizeof(vis2in3));
    memset(vis3in2, false, sizeof(vis3in2));
    memset(isOkay, -1, sizeof(isOkay));
    isOkay[0] = 0;
    for (int i = 0; i < n; i++) {
        if (isOkay[i] < 0)
            continue;
        if (is2[i]) {
            int j = i + 2;
            while (j + 2 <= n && !vis3in2[j]) {
                vis3in2[j] = true;
                if (is2[j] && isOkay[j + 2] < 0) {
                    isOkay[j + 2] = i;
                    is2or3[j + 2] = 2;
                }
                if (!is3[j])
                    break;
                j += 3;
                if (!is3[j])
                    break;
                j += 3;
            }
        }
        if (is3[i]) {
            int j = i + 3;
            while (j + 3 <= n && !vis2in3[j]) {
                vis2in3[j] = true;
                if (is3[j] && isOkay[j + 3] < 0) {
                    isOkay[j + 3] = i;
                    is2or3[j + 3] = 3;
                }
                if (!is2[j])
                    break;
                j += 2;
                if (!is2[j])
                    break;
                j += 2;
            }
        }
    }
    if (isOkay[n] < 0) {
        puts("!@#$%");
    } else {
        memset(ans, 0, sizeof(ans));
        int ptr = n;
        while (ptr > 0) {
            int prev = isOkay[ptr];
            int type = is2or3[ptr];
            int lo = prev, hi = ptr;
            ans[lo] = type;
            lo += type, hi -= type;
            ans[hi] = -type;
            type = 2 + 3 - type;
            while (lo < hi) {
                ans[lo] = type;
                lo += type;
                ans[lo] = -type;
                lo += type;
            }
            ptr = prev;
        }
        ptr = 0;
        for (int i = 0; i < len; i++) {
            while (ptr < n && pos[ptr] < i) {
                ptr ++;
            }
            if (ptr < n && pos[ptr] == i) {
                if (ans[ptr] == 2) {
                    printf("<i>");
                } else if (ans[ptr] == -2) {
                    printf("</i>");
                } else if (ans[ptr] == 3) {
                    printf("<b>");
                } else if (ans[ptr] == -3) {
                    printf("</b>");
                }
            } else {
                putchar(str[i]);
            }
        }
        puts("");
    }
}
