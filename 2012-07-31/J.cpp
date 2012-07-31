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

const int maxn = 123456;

int n;
vector<int> adj[maxn];

unsigned long long hash[maxn];
int len[maxn];

unsigned long long p4423[1 << 20];

int main()
{
    p4423[0] = 1;
    for (int i = 1; i < 1 << 20; i++) {
        p4423[i] = p4423[i - 1] * 4423;
    }
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int ai;
        scanf("%d", &ai);
        ai--;
        adj[ai].push_back(i);
    }
    for (int i = n - 1; i >= 0; i --) {
        vector<pair<unsigned long long,int> > hs;
        for (int j = 0; j < adj[i].size(); j++) {
            int k = adj[i][j];
            hs.push_back(make_pair(hash[k], len[k]));
        }
        sort(hs.begin(), hs.end());
        hash[i] = 1;
        len[i] = 1;
        for (int j = 0; j < hs.size(); j++) {
            hash[i] = hash[i] * p4423[hs[j].second] + hs[j].first;
            len[i] += hs[j].second;
        }
        hash[i] = hash[i] * 4423 + 3137;
        len[i] ++;
    }
    vector<pair<unsigned long long,int> > S;
    for (int i = 0; i < n; i++) {
        S.push_back(make_pair(hash[i], i));
    }
    sort(S.begin(), S.end());
    vector<int> ans(n);
    for (int i = 0; i < S.size(); ) {
        int ni = i;
        while (ni < S.size() && S[ni].first == S[i].first) {
            ans[S[ni].second] = S[i].second;
            ni ++;
        }
        i = ni;
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", ans[i] + 1);
    }
    puts("");
}
