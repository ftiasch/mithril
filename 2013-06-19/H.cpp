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

#define for(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int maxn = 11111111;

int dest[maxn], nexte[maxn], firste[maxn / 2];
int edges = 0;

void add(int a, int b)
{
    dest[edges] = b;
    nexte[edges] = firste[a];
    firste[a] = edges ++;
}

int n, b;
int pows[1 << 10];

int n;

char ans[maxn + 1];
int ptr = 0;

void dfs(int p)
{
    for (int &e = firste[p]; e != -1; ) {
        int q = dest[e];
        e = nexte[e];
        dfs(q);
    }
    ans[ptr++] = p % b + '0';
}

void dfs2(int p)
{
    vector<int> st;
    st.push_back(p);
    while (!st.empty()) {
        int p = st.back();
        if (firste[p] < 0) {
            st.pop_back();
            ans[ptr++] = p % b + '0';
        } else {
            int &e = firste[p];
            int q = dest[e];
            firste[p] = nexte[e];
            st.push_back(q);
        }
    }
}

int main()
{
    scanf("%d%d", &n, &b);
    if (b == 1) {
        puts("0");
        return 0;
    }
    if (n == 1) {
        for (int i = 0; i < b; i++) {
            putchar('0' + i);
        }
        puts("");
        return 0;
    }
    pows[0] = 1;
    for (int i = 1; i <= n; i++) {
        pows[i] = pows[i - 1] * b;
    }
    n = pows[n - 1];
    memset(firste, -1, sizeof(firste));
    for (int s = 0; s < n; s++) {
        for (int i = 0; i < b; i++) {
            int t = (s * b + i) % n;
            add(s, t);
        }
    }
    dfs2(0);
    ptr --;
    ans[ptr] = 0;
    puts(ans);
}
