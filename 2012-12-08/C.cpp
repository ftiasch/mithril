#include <cstdio>
#include <cstring>

const int N = 500;

int n, m;
char names[N + 1];

int visit[256];

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf("%d%d%s", &n, &m, names);
        memset(visit, 0, sizeof(visit));
        int answer = 0;
        for (int i = 0; i < n; ++ i) {
            if (i - m - 1 >= 0) {
                visit[names[i - m - 1]] --;
            }
            answer += visit[names[i]] > 0;
            visit[names[i]] ++;
        }
        printf("Case %d: %d\n", t, answer);
    }
    return 0;
}
