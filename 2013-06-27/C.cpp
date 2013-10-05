#include <cstdio>
#include <cstring>
#include <algorithm>

int p[7][6], q[7][6], order[7], r[7];

bool check() {
    int start = q[order[0]][0];
    for (int i = 1; i < 7; ++ i) {
        r[order[i]] = q[order[i]][p[order[0]][(start + i - 1) % 6]];
    }
    for (int i = 0; i < 6; ++ i) {
        int x = order[1 + i];
        int y = order[1 + (i + 1) % 6];
        if (p[x][(r[x] + 5) % 6] != p[y][(r[y] + 1) % 6]) {
            return false;
        }
    }
    return true;
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        for (int i = 0; i < 7; ++ i) {
            for (int j = 0; j < 6; ++ j) {
                scanf("%d", &p[i][j]);
                q[i][-- p[i][j]] = j;
            }
            order[i] = i;
        }
        bool found = false;
        do {
            found |= check();
        } while (!found && std::next_permutation(order, order + 7));
        printf("Case %d:", t);
        if (found) {
            for (int i = 0; i < 7; ++ i) {
                printf(" %d", order[i]);
            }
            puts("");
        } else {
            puts(" No solution");
        }
    }
    return 0;
}
