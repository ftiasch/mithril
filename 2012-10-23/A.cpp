#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

const int N = 10;
const int M = 10 << 1;

int n, m;

int edgeCount, firstEdge[N], to[M], capacity[M], flow[M], nextEdge[M];

void addEdge(int u, int v, int w) {
    to[edgeCount] = v;
    capacity[edgeCount] = w;
    flow[edgeCount] = 0;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

int predecessor[N];

void bfs(int source, int sink) {
    while (true) {
        queue <int> opened;
        memset(predecessor, -1, sizeof(predecessor));
        predecessor[source] = 0;
        opened.push(source);
        while (!opened.empty()) {
            int u = opened.front();
            opened.pop();
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                if (flow[iter] < capacity[iter] && predecessor[to[iter]] == -1) {
                    opened.push(to[iter]);
                    predecessor[to[iter]] = iter;
                }
            }
        }
        if (predecessor[sink] == -1) {
            break;
        }
        int delta = INT_MAX;
        for (int i = sink; i != source; i = to[predecessor[i] ^ 1]) {
            int &iter = predecessor[i];
            delta = min(delta, capacity[iter] - flow[iter]);
        }
        for (int i = sink; i != source; i = to[predecessor[i] ^ 1]) {
            int &iter = predecessor[i];
            flow[iter] += delta;
            flow[iter ^ 1] -= delta;
        }
    }
}

vector <int> edges;

int visit[N];

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

vector <vector <int> > vectors;

void dfs(int start, int u) {
    if (start == u && !edges.empty()) {
        vectors.push_back(vector <int>(m, 0));
        foreach (iter, edges) {
            vectors.back()[*iter >> 1] += *iter & 1 ? 1 : -1;
        }
    } else if (!visit[u]) {
        visit[u] = true;
        for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
            if (flow[iter] < capacity[iter]) {
                edges.push_back(iter);
                dfs(start, to[iter]);
                edges.pop_back();
            }
        }
        visit[u] = false;
    }
}

int eliminate() {
    int n = vectors.size();
    int rank = 0;
    for (int k = 0; k < m; ++ k) {
        int pivot = rank;
        while (pivot < n && vectors[pivot][k] == 0) {
            pivot ++;
        }
        if (pivot == n) {
            continue;
        }
        swap(vectors[rank], vectors[pivot]);
        for (int i = 0; i < n; ++ i) {
            if (i != rank && vectors[i][k] != 0) {
                int times = vectors[i][k] / vectors[rank][k];
                for (int j = 0; j < m; ++ j) {
                    vectors[i][j] -= vectors[rank][j] * times;
                }
            }
        }
        rank ++;
    }
    return rank;
}

int main() {
    scanf("%d%d", &n, &m);
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a --;
        b --;
        addEdge(a, b, c);
        addEdge(b, a, 0);
    }
    bfs(0, n - 1);
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < n; ++ i) {
        dfs(i, i);
    }
//foreach (iter, vectors) {
//    for (int i = 0; i < m; ++ i) {
//        printf("%4d", (*iter)[i]);
//    }
//    puts("");
//}
    printf("%d\n", eliminate());
    return 0;
}
