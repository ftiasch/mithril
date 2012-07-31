#include <cstdio>
#include <cstring>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 2000;
const int M = 100000;

int n, m, a, b, c, d, edgeCount, firstEdge[N], to[M], nextEdge[M], prev[N][N];

int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d);
    if (a > b) {
        swap(a, b);
    }
    if (c > d) {
        swap(c, d);
    }
    a --, b --, c --, d --;
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < m; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        u --, v --;
        to[edgeCount] = v;
        nextEdge[edgeCount] = firstEdge[u];
        firstEdge[u] = edgeCount ++;
    }
    queue <pair <int, int> > q;
    q.push(make_pair(a, c));
    memset(prev, -1, sizeof(prev));
    while (!q.empty()) {
        int a = q.front().first;
        int c = q.front().second;
        q.pop();
        if (a < c || c == d) {
            for (int iter = firstEdge[a]; iter != -1; iter = nextEdge[iter]) {
                if (to[iter] != c) {
                    if (prev[to[iter]][c] == -1) {
                        prev[to[iter]][c] = a * n + c;
                        q.push(make_pair(to[iter], c));
                    }
                }
            }
        } 
        if (c < a || a == b) {
            for (int iter = firstEdge[c]; iter != -1; iter = nextEdge[iter]) {
                if (to[iter] != a) {
                    if (prev[a][to[iter]] == -1) {
                        prev[a][to[iter]] = a * n + c;
                        q.push(make_pair(a, to[iter]));
                    }
                }
            }
        }
    }
    if (prev[b][d] == -1) {
        puts("NO");
    } else {
        puts("YES");
        vector <int> pathA, pathB;
        pathA.push_back(b);
        pathB.push_back(d);
        for (int i = b, j = d; i != a || j != c; ) {
            int x = prev[i][j] / n;
            int y = prev[i][j] % n;
            if (i != x) {
                pathA.push_back(i = x);
            } else {
                pathB.push_back(j = y);
            }
        }
        for (int i = (int)pathA.size() - 1; i >= 0; -- i) {
            printf("%d%c", pathA[i] + 1, i == 0? '\n': ' ');
        }
        for (int i = (int)pathB.size() - 1; i >= 0; -- i) {
            printf("%d%c", pathB[i] + 1, i == 0? '\n': ' ');
        }
    }
    return 0;
}
