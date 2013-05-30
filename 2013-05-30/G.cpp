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

const int maxn = 1 << 10;

int n, m;
int size[5];
int id[maxn], fst[maxn], lst[maxn];

int main()
{
    int cas = 0;
    while (scanf("%d%d", &n, &m) == 2 && n) {
        vector<int> perm;
        for (int i = 0; i < n; i++) {
            scanf("%d", size + i);
            perm.push_back(i);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", id + i, fst + i, lst + i);
            id[i] --;
            fst[i] --;
        }
        int ans = 1 << 30;
        do {
            map<pair<int,int>,int> buffer;
            int bufferSize = 0, maxBufferSize = 0;
            int processed = 0;
            FOR (it, perm) {
                int sz = size[*it], ptr = 0;
                while (ptr < sz) {
                    while (!buffer.count(make_pair(*it, ptr))) {
                        assert(processed < m);
                        buffer[make_pair(id[processed], fst[processed])] = lst[processed] - fst[processed];
                        bufferSize += lst[processed] - fst[processed];
                        processed++;
                    }
                    int nptr = ptr + buffer[make_pair(*it, ptr)];
                    bufferSize -= nptr - ptr;
                    maxBufferSize = max(maxBufferSize, bufferSize);
                    buffer.erase(make_pair(*it, ptr));
                    ptr = nptr;
                }
            }
            ans = min(ans, maxBufferSize);
        } while (next_permutation(perm.begin(), perm.end()));
        printf("Case %d: %d\n\n", ++cas, ans);
    }
    return 0;
}
