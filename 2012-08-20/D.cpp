#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 300000;

int n, weight[N], firstEdge[N], edgeCount, to[N << 1], color[N << 1], nextEdge[N << 1], parentColor[N];

void addEdge(int u, int v, int w) {
    to[edgeCount] = v;
    color[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

int parent[N], orderSize, order[N];

long long down[N], up[N];

void dfs(int p, int u) {
    order[orderSize ++] = u;
    parent[u] = p;
    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        int v = to[iter];
        if (v != p) {
            parentColor[v] = color[iter];
            dfs(u, v);
        }
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d", weight + i);
        }
        edgeCount = 0;
        fill(firstEdge, firstEdge + n, -1);
        for (int i = 0; i < n - 1; ++ i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            a --, b --;
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        orderSize = 0;
        memset(parentColor, 0, sizeof(parentColor));
        dfs(-1, 0);
        for (int i = n - 1; i >= 0; -- i) {
            int u = order[i];
            down[u] = 1;
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                int v = to[iter];
                if (v != parent[u] && color[iter] != parentColor[u]) {
                    down[u] += down[v];
                }
            }
        }
        up[0] = 0;
        for (int i = 0; i < n; ++ i) {
            int u = order[i];
            vector <pair <int, int> > children;
            long long total = 0;
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                int v = to[iter];
                if (v != parent[u]) {
                    children.push_back(make_pair(color[iter], v));
                    total += down[v];
                }
            }
            sort(children.begin(), children.end());
            for (int low = 0; low < (int)children.size(); ++ low) {
                int high = low;
                while (high < (int)children.size() && children[low].first == children[high].first) {
                    high ++;
                }
                long long extra = 0;
                for (int i = low; i < high; ++ i) {
                    extra += down[children[i].second];
                }
                for (int i = low; i < high; ++ i) {
                    up[children[i].second] = total - extra;
                    if (parentColor[u] != parentColor[children[i].second]) {
                        up[children[i].second] += up[u];
                    }
                    up[children[i].second] ++;
                }
                low = high - 1;
            }
        }
//for (int i = 0; i < n; ++ i) {
//    printf("%d: %lld %lld\n", 1 + i, up[i], down[i]);
//}
        long long result = 0;
        for (int i = 0; i < n; ++ i) {
            long long times = 0;
            vector <pair <int, long long> > paths;
            long long total = 0;
            for (int iter = firstEdge[i]; iter != -1; iter = nextEdge[iter]) {
                int v = to[iter];
                int c = color[iter];
                if (v == parent[i]) {
                    paths.push_back(make_pair(c, up[i]));
                } else {
                    paths.push_back(make_pair(c, down[v]));
                }
                total += paths.back().second;
            }
            sort(paths.begin(), paths.end());
            for (int low = 0; low < (int)paths.size(); ++ low) {
                int high = low;
                while (high < (int)paths.size() && paths[low].first == paths[high].first) {
                    high ++;
                }
                long long extra = 0;
                for (int i = low; i < high; ++ i) {
                    extra += paths[i].second;
                }
                times += extra * (total - extra);
                low = high - 1;
            }
            times /= 2;
            times += total;
//printf("%d + %lld %lld\n", i + 1, total, times);
            result += weight[i] * times;
        }
        cout << result << endl;
    }
    return 0;
}
