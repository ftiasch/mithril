#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 100000;

int n, m;
char buffer[N + 1];
vector <short> map[N];
vector <bool> visit[N];

const int DELTA[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int flood(int x_0, int y_0) {
    int size = 1;
    queue <pair <int, int> > opened;
    opened.push(make_pair(x_0, y_0));
    visit[x_0][y_0] = true;
    while (!opened.empty()) {
        int x = opened.front().first;
        int y = opened.front().second;
        opened.pop();
        for (int k = 0; k < 4; ++ k) {
            int new_x = x + DELTA[k][0];
            int new_y = y + DELTA[k][1];
            if (0 <= new_x && new_x < n && 0 <= new_y && new_y < m 
                    && map[new_x][new_y] && !visit[new_x][new_y]) {
                size ++;
                visit[new_x][new_y] = true;
                opened.push(make_pair(new_x, new_y));
            }
        }
    }
    return size;
}

int main() {
    freopen("blot.in", "r", stdin);
    freopen("blot.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", buffer);
        map[i].resize(m);
        for (int j = 0; j < m; ++ j) {
            map[i][j] = buffer[j] - '0';
        }
    }
    for (int i = 0; i < n; ++ i) {
        visit[i].resize(m);
        for (int j = 0; j < m; ++ j) {
            visit[i][j] = false;
        }
    }
    int component = 0;
    int max_component = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (map[i][j] && !visit[i][j]) {
                component ++;
                max_component = max(max_component, flood(i, j));
            }
        }
    }
    printf("%d %d\n", component, max_component);
    return 0;
}
