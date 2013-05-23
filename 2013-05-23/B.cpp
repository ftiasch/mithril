#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 10000;

int father[maxn];
bool black[maxn];

struct Edge
{
    int a, b, c;
    Edge(int a, int b, int c):a(a), b(b), c(c) {
    }
};

inline bool operator < (const Edge &a, const Edge &b)
{
    return a.c > b.c;
}

inline int find(int x) 
{
    if (x == father[x]) {
        return x;
    }
    return father[x] = find(father[x]);
}

int main()
{
    for (int test = 1, n, t, k;scanf("%d%d%d", &n, &t, &k) == 3 && n; ++ test) {
        for (int i = 0; i < n; ++ i) {
            father[i] = i;
            black[i] = false;
        }
        vector<Edge> edges;
        for (int i = 1; i < n; ++ i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            --a; --b;
            edges.push_back(Edge(a, b, c));
        }
        for (int i = 0; i < t; ++ i) {
            int x;
            scanf("%d", &x);
            -- x;
            black[x] = true;
        }
        sort(edges.begin(), edges.end());
        long long answer = 0;
        for (int i = 0; i < (int)edges.size(); ++ i) {
            int fa = find(edges[i].a), fb= find(edges[i].b);
            if (!black[fa] || !black[fb] || t > k + 1) {
                if (black[fa] && black[fb]) {
                    -- t;
                }
                father[fa] = fb;
                black[fb] |= black[fa];
            } else {
                answer += edges[i].c;
            }
        }
        cout << "Case " << test << ": " << answer << endl;
    }
    return 0;
}

