#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 500;
const int M = N * N;

int n, m, degree[N], edgeCount, firstEdge[N], to[M], nextEdge[M];
bool used[M];
set <int> passedCycle[N];
vector <vector <int> > paths, cycles;

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void dfs(int u) {
    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        if (!used[iter >> 1]) {
            int v = to[iter];
            used[iter >> 1] = true;
            dfs(v);
            cycles.back().push_back(v);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    edgeCount = 0;
    memset(degree, 0, sizeof(degree));
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        degree[-- a] ++;
        degree[-- b] ++;
        addEdge(a, b);
        addEdge(b, a);
    }
    memset(used, 0, sizeof(used));
    while (true) {
        int i = 0;
        while (i < n && (degree[i] & 1) == 0) {
            i ++;
        }
        if (i == n) {
            break;
        }
        paths.push_back(vector <int>(1, i));
        while ((degree[i] & 1) == 1) {
            while (used[firstEdge[i] >> 1]) {
                firstEdge[i] = nextEdge[firstEdge[i]];
            }
            int iter = firstEdge[i];
            used[iter >> 1] = true;
            int j = to[iter];
            degree[i] --;
            degree[j] --;
            paths.back().push_back(j);
            i = j;
        }
    }
    for (int i = 0; i < n; ++ i) {
        while (used[firstEdge[i] >> 1]) {
            firstEdge[i] = nextEdge[firstEdge[i]];
        }
        if (firstEdge[i] != -1) {
            cycles.push_back(vector <int>());
            dfs(i);
        }
    }
//for (int i = 0; i < (int)cycles.size(); ++ i) {
//    for (int j = 0; j < (int)cycles[i].size(); ++ j) {
//        printf("%d, ", cycles[i][j]);
//    }
//    puts("");
//}
//puts("---");
//for (int i = 0; i < (int)paths.size(); ++ i) {
//    for (int j = 0; j < (int)paths[i].size(); ++ j) {
//        printf("%d, ", paths[i][j]);
//    }
//    puts("");
//}
//puts("---");
    for (int i = 0; i < (int)cycles.size(); ++ i) {
        for (int j = 0; j < (int)cycles[i].size(); ++ j) {
            passedCycle[cycles[i][j]].insert(i);
        }
    }
    vector <vector <int> > result;
    for (int i = 0; i < (int)paths.size(); ++ i) {
        result.push_back(vector <int>());
        for (int j = 0; j < (int)paths[i].size(); ++ j) {
            int u = paths[i][j];
            result.back().push_back(u);
            while (!passedCycle[u].empty()) {
                int id = *passedCycle[u].begin();
                int k = 0;
                while (cycles[id][k] != u) {
                    k ++;
                }
                for (int _ = (int)cycles[id].size(); _ > 0; -- _) {
                    k = (k + 1) % (int)cycles[id].size();
                    result.back().push_back(cycles[id][k]);
                }
                for (int k = 0; k < (int)cycles[id].size(); ++ k) {
                    passedCycle[cycles[id][k]].erase(id);
                }
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        while (!passedCycle[i].empty()) {
            int id = *passedCycle[i].begin();
            result.push_back(cycles[id]);
            for (int k = 0; k < (int)cycles[id].size(); ++ k) {
                passedCycle[cycles[id][k]].erase(id);
            }
            result.back().push_back(cycles[id].front());
        }
    }
    printf("%d\n", (int)result.size());
    for (int i = 0; i < (int)result.size(); ++ i) {
        for (int j = 0; j < (int)result[i].size(); ++ j) {
            printf("%d%c", result[i][j] + 1, j == (int)result[i].size() - 1? '\n': ' ');
        }
    }
    return 0;
}
