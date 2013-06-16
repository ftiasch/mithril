#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 202;

int n, m;
char buffer[N];
bool map[N][N];

int get_id(int x, int y) {
    return x * m + y;
}

int parent[N * N];

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

bool used[N * N];
int count[N * N];

const char* TYPES = "WAKJSD";

void solve(int x, int y) {
    x = find(x);
    y = find(y);
    if (map[x / m][x % m]) {
        std::swap(x, y);
    }
    if (used[x] || x == find(0)) {
        return;
    }
    used[x] = true;
    count[y] ++;
}

int get_buffer(int i) {
    if (isdigit(buffer[i])) {
        return buffer[i] - '0';
    }
    return buffer[i] - 'a' + 10;
}

int main() {
    int test_count = 0;
    while (scanf("%d%d", &n, &m) == 2 && n + m) {
        memset(map, 0, sizeof(map));
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", buffer);
            for (int j = 0; j < m << 2; ++ j) {
                map[i][j + 1] = get_buffer(j >> 2) >> (3 - (j & 3)) & 1;
            }
        }
        n += 2;
        m <<= 2;
        m += 2;
        for (int i = 0; i < n * m; ++ i) {
            parent[i] = i;
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (i && map[i][j] == map[i - 1][j]) {
                    merge(get_id(i, j), get_id(i - 1, j));
                }
                if (j && map[i][j] == map[i][j - 1]) {
                    merge(get_id(i, j), get_id(i, j - 1));
                }
            }
        }
        memset(used, 0, sizeof(used));
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (i && map[i][j] != map[i - 1][j]) {
                    solve(get_id(i, j), get_id(i - 1, j));
                }
                if (j && map[i][j] != map[i][j - 1]) {
                    solve(get_id(i, j), get_id(i, j - 1));
                }
            }
        }
        std::vector <char> answer;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (map[i][j]) {
                    int x = get_id(i, j);
                    if (find(x) == x) {
                        answer.push_back(TYPES[count[x]]);
                    }
                }
            }
        }
        std::sort(answer.begin(), answer.end());
        printf("Case %d: ", ++ test_count);
        for (int i = 0; i < (int)answer.size(); ++ i) {
            putchar(answer[i]);
        }
        puts("");
    }
    return 0;
}
