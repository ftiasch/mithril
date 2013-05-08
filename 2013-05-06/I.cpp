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

const int inf = 1000000011;

int n, edges;
pair<int,int> edge[1 << 20];

int mapping[50];

int main()
{
    scanf("%d", &n);
    edges = 0;
    for (int i = 0; i < n; i++) {
        int num, len;
        scanf("%d", &num);
        for (int j = 0; j < num; j++) {
            scanf("%d", &len);
            edge[edges++] = make_pair(len, i);
        }
    }
    sort(edge, edge + edges);
    for (int it = 0; it < 30; ++it) {
        while (true) {
            int cnt[3];
            cnt[0] = cnt[1] = cnt[2] = 0;
            for (int i = 0; i < n; i++) {
                cnt[mapping[i] = (unsigned)rand() % 3] ++;
            }
            if (cnt[0] && cnt[1] && cnt[2]) {
                break;
            }
        }
        pair<int,int> *last[3];
        last[0] = last[1] = last[2] = NULL;
        for (int i = 0; i < edges; i++) {
            pair<int,int> *it = &edge[i];
            int c0 = mapping[it->second];
            int c1 = (c0 + 1) % 3, c2 = (c0 + 2) % 3;
            if (last[c1] && last[c2] && last[c1]->first + last[c2]->first > it->first) {
                printf("%d %d %d %d %d %d\n", it->second + 1, it->first, 
                        last[c1]->second + 1, last[c1]->first,
                        last[c2]->second + 1, last[c2]->first);
                return 0;
            }
            last[c0] = it;
        }
    }
    puts("NIE");
}
