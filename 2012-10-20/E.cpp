#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 400;

int n, m;
bool graph[N][N];

int nextInt() {
    int x;
    scanf("%d", &x);
    return x;
}

vector <int> nextInts() {
    vector <int> result;
    for (int i = nextInt(); i != n; i = nextInt()) {
        result.push_back(-- i);
    }
    return result;
}

int valid[N][N][2];

vector <int> merge(vector <int> a, vector <int> b) {
    int n = a.size();
    int m = b.size();
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            for (int t = 0; t < 2; ++ t) {
                valid[i][j][t] = -1;
            }
        }
    }
    for (int i = n; i > 0; -- i) {
        for (int j = m; j > 0; -- j) {
            for (int t = 0; t < 2; ++ t) {
                if (i == n && j == m) {
                    valid[i][j][t] = 2;
                } else if ((t ? j : i) <= (t ? m : n)) {
                    int u = t ? b[j-1] : a[i-1];
                    if (i < n && graph[u][a[i]] && valid[i + 1][j][0] != -1) {
                        valid[i][j][t] = 0;
                    }
                    if (j< m && graph[u][b[j]] && valid[i][j + 1][1] != -1) {
                        valid[i][j][t] = 1;
                    }
                }
            }
        }
    }
    int t = 0;
    while (t < 2 && valid[1][1][t] == -1) {
        t ++;
    }
    assert(t < 2);
    vector <int> c;
    c.push_back(0);
    for (int i = 1, j = 1; i < n || j < m; ) {
        int nextT = valid[i][j][t];
        t = nextT;
        if (t) {
            c.push_back(b[j ++]);
        } else {
            c.push_back(a[i ++]);
        }
    }
//printf("%d %d %d\n",a.size(),b.size(),c.size());
    return c;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        char buffer[N + 1];
        scanf("%s", buffer);
        for (int j = 0; j < n; ++ j) {
            graph[i][j] = buffer[j] == '-';
        }
    }
    m --;
    vector <int> result = nextInts();
    while (m --) {
        vector <int> order = nextInts();
        result = merge(result, order);
    }
    for (int i = 0; i < result.size(); ++ i) {
        printf("%d ", result[i] + 1);
    }
    printf("%d\n", n);
    return 0;
}
