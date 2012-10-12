#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 200;
const int M = 1000;

#define foreach(i, v) for (typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

int n, m, t;
bool terminated[N];

int headEdge[N], from[M], to[M], nextEdge[M], lable[M];

vector <int> right[N];
int parent[N];

int text[N];

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

bool merge(int i, int j) {
    if (find(i) == find(j)) {
        return false;
    }
    parent[find(i)] = find(j);
    return true;
}

int main() {
    scanf("%d%d%d", &n, &m, &t);
    memset(terminated, 0, sizeof(terminated));
    for (int i = 0; i < t; ++ i) {
        int x;
        scanf("%d", &x);
        terminated[-- x] = true;
    }
    memset(headEdge, -1, sizeof(headEdge));
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d", from + i, to + i);
        from[i] --;
        nextEdge[i] = headEdge[from[i]];
        headEdge[from[i]] = i;
        to[i] --;
    }
    int length = 0;
    while (true) {
        int u = 0;
        while (u < n) {
            bool found = false;
            for (int iter = headEdge[u]; iter != -1; iter = nextEdge[iter]) {
                int v = to[iter];
                found |= right[v].empty();
            }
            if (right[u].empty() && !found) {
                break;
            }
            u ++;
        }
        if (u == n) {
            break;
        }
        if (terminated[u]) {
            right[u].push_back(0);
        }
        for (int iter = headEdge[u]; iter != -1; iter = nextEdge[iter]) {
            int v = to[iter];
            foreach (p, right[v]) {
                right[u].push_back(*p + 1);
            }
        }
        sort(right[u].begin(), right[u].end());
        length = max(length, right[u].back());
    }
    //for (int i = 0; i < n; ++ i) {
    //    foreach (iter, right[i]) {
    //        printf("%d ", *iter);
    //    }
    //    puts("");
    //}
    for (int i = 0; i < length; ++ i) {
        parent[i] = i;
    }
    for (int u = 0; u < n; ++ u) {
        for (int iter = headEdge[u]; iter != -1; iter = nextEdge[iter]) {
            int v = to[iter];
            int i = right[v].back();
            foreach (p, right[v]) {
                merge(length - 1 - *p, length - 1 - i);
            }
        }
    }
    int size = 0;
    memset(text, -1, sizeof(text));
    for (int i = 0; i < length; ++ i) {
        if (text[i] == -1) {
            for (int j = 0; j < length; ++ j) {
                if (find(i) == find(j)) {
                    text[j] = size;
                }
            }
            size ++;
        }
    }
    printf("%d %d\n", length, size);
    for (int i = 0; i < length; ++ i) {
        printf("%d%c", text[i] + 1, i == length - 1 ? '\n' : ' ');
    }
    for (int u = 0; u < n; ++ u) {
        for (int iter = headEdge[u]; iter != -1; iter = nextEdge[iter]) {
            int v = to[iter];
            int i = right[v].back();
            lable[iter] = text[length - 1 - i];
        }
    }
    for (int i = 0; i < m; ++ i) {
        printf("%d%c", lable[i] + 1, i == m - 1 ? '\n' : ' ');
    }
    return 0;
}
