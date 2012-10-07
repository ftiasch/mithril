#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1000 + 1;

int n, perm[N], pos[N];
int nodeCount;
vector <pair <int, int> > edges;

void addEdge(int u, int v) {
    edges.push_back(make_pair(u, v));
}

vector <int> construct(int l, int r) {
    if (l == r) {
        return vector <int>(1, perm[l]);
    }
    int m = (l + r) >> 1;
    vector <int> front = construct(l, m);
    vector <int> back = construct(m + 1, r);
    for (int i = 0; i < (int)front.size(); ++ i) {
        addEdge(pos[front[i]], nodeCount + 1 + i);
    }
    int base = nodeCount + 1 + front.size();
    for (int i = 0; i < (int)back.size(); ++ i) {
        addEdge(base + i, pos[back[i]]);
    }
    for (int i = 0; i + 1 < (int)back.size(); ++ i) {
        addEdge(base + i + 1, base + i);
    }
    for (int i = 0; i < (int)front.size(); ++ i) {
        int j = upper_bound(back.begin(), back.end(), front[i]) - back.begin() - 1;
        if (j >= 0) {
            addEdge(nodeCount + 1 + i, base + j);
        }
    }
    nodeCount += r - l + 1;
    vector <int> all;
    for (int i = l; i <= r; ++ i) {
        all.push_back(perm[i]);
    }
    sort(all.begin(), all.end());
    return all;
}

int main() {
    freopen("small-graph.in", "r", stdin);
    freopen("small-graph.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", perm + i);
        pos[perm[i]] = i;
    }
    nodeCount = n;
    construct(1, n);
    printf("%d %d\n", nodeCount, (int)edges.size());
    for (vector <pair <int, int> > :: iterator iter = edges.begin();
            iter != edges.end(); ++ iter) {
        printf("%d %d\n", iter->first, iter->second);
    }
    return 0;
}
