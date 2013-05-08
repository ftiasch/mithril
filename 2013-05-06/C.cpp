#include <cstdio>
#include <cstring>
#include <climits>
#include <set>
#include <queue>
#include <utility>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

using std::pair;
using std::make_pair;

const int N = 500000;
const int M = 3 * N;

int n, m, a[M], b[M];
bool mark[M], exists[N];

typedef std::set <pair <int, int> > :: iterator Iterator;

std::set <pair <int, int> > edges[N];

int get_edge(int u, int v) {
    Iterator iter = edges[u].lower_bound(make_pair(v, -1));
    if (iter != edges[u].end() && iter->first == v) {
        return iter->second;
    }
    return -1;
}

void add_edge(int id) {
    int u = a[id];
    int v = b[id];
    edges[u].insert(make_pair(v, id));
    edges[v].insert(make_pair(u, id));
}

void remove_edge(int id) {
    int u = a[id];
    int v = b[id];
    edges[u].erase(make_pair(v, id));
    edges[v].erase(make_pair(u, id));
}

std::queue <int> queue;

void enqueue(int u) {
    if (!exists[u] && (int)edges[u].size() == 2) {
        exists[u] = true;
        queue.push(u);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d", a + i, b + i);
        a[i] --;
        b[i] --;
        add_edge(i);
    }
    int edge_count = m;
    memset(mark, 0, sizeof(mark));
    memset(exists, 0, sizeof(exists));
    for (int i = 0; i < n; ++ i) {
        enqueue(i);
    }
    for (int total = n; total > 3; total --) {
        int u = queue.front();
        queue.pop();
        int v, w;
        {
            Iterator iter = edges[u].begin();
            v = iter->first;
            remove_edge(iter->second);
            iter ++;
            w = iter->first;
            remove_edge(iter->second);
        }
        int id = get_edge(v, w);
        if (id == -1) {
            a[edge_count] = v;
            b[edge_count] = w;
            add_edge(edge_count ++);
        } else {
            mark[id] = true;
        }
        enqueue(v);
        enqueue(w);
    }
    for (int i = 0; i < n; ++ i) {
        edges[i].clear();
    }
    for (int i = 0; i < m; ++ i) {
        if (!mark[i]) {
            add_edge(i);
        }
    }
    int prev = 0;
    int now = n;
    foreach (iter, edges[0]) {
        now = std::min(now, iter->first);
    }
    printf("%d", 1);
    while (now) {
        printf(" %d", now + 1);
        int next = n;
        foreach (iter, edges[now]) {
            if (iter->first != prev) {
                next = iter->first;
            }
        }
        prev = now;
        now = next;
    }
    puts("");
    return 0;
}
