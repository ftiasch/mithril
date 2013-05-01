#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <cctype>
#include <sstream>

using namespace std;

#define FOR(it, a) for (__typeof((a).begin()) it=(a).begin(); it != (a).end(); ++it)

const int maxn = 1 << 21;
//vector<int> adj0[maxn], adj1[maxn];

int dist[maxn];
bool inQ[maxn];

int n, N;

int main()
{
    scanf("%d", &n);
    while (n % 2 == 0) {
        n /= 2;
    }
    N = 1;
    while (N <= n) {
         N *= 2;
    }
    N *= 2;
    /*for (int i = 0; i < N; i++) {
        if (i + n < N) {
            adj0[i + n].push_back(i);
        }
        if (i % 2 == 0) {
            adj0[i / 2].push_back(i);
        } else {
            adj1[i / 2].push_back(i);
        }
    }*/
    memset(dist, -1, sizeof(dist));
    memset(inQ, false, sizeof(inQ));
    dist[0] = 0;
    inQ[0] = true;
    deque<int> Q;
    Q.push_back(0);
    while (!Q.empty()) {
        int p = Q.front();
        inQ[p] = false;
        Q.pop_front();
        if (p >= n) {
            int q = p - n;
            if (dist[q] < 0 || dist[q] > dist[p]) {
                dist[q] = dist[p];
                if (!inQ[q]) {
                    inQ[q] = true;
                    Q.push_front(q);
                }
            }
        }
        if (p * 2 < N) {
            int q = p * 2 + 0;
            if (dist[q] < 0 || dist[q] > dist[p]) {
                dist[q] = dist[p];
                if (!inQ[q]) {
                    inQ[q] = true;
                    Q.push_front(q);
                }
            }
        }
        if (p * 2 + 1 < N) {
            int q = p * 2 + 1;
            if (dist[q] < 0 || dist[q] > dist[p] + 1) {
                dist[q] = dist[p] + 1;
                if (!inQ[q]) {
                    inQ[q] = true;
                    Q.push_back(q);
                }
            }
        }
    }
    printf("%d\n", dist[n]);
}
