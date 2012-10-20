#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;

const int N = 5000 + 1;

char s[N];
short fail[N], base[N][N], minimum[N], choice[N];

int main() {
    scanf("%s", s);
    int n = strlen(s);
    for (int start = 0; start < n; ++ start) {
        fail[start] = start - 1;
        for (int i = start + 1; i < n; ++ i) {
            fail[i] = start - 1;
            int j = i - 1;
            while (j >= start) {
                j = fail[j];
                if (s[j + 1] == s[i]) {
                    fail[i] = j + 1;
                    break;
                }
            }
        }
        for (int i = start; i < n; ++ i) {
            if ((i - start + 1) % (i - fail[i]) == 0) {
                base[start][i] = i - fail[i];
            } else {
                base[start][i] = i - start + 1;
            }
        }
    }
    minimum[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        minimum[i] = 30000;
        for (int j = i; j < n; ++ j) {
            if (base[i][j] + minimum[j + 1] < minimum[i]) {
                choice[i] = j + 1;
                minimum[i] = base[i][j] + minimum[j + 1];
            }
        }
    }
    printf("%d\n", (int)minimum[0]);
    for (int i = 0; i < n; i = choice[i]) {
        int k = base[i][choice[i] - 1];
        for (int j = 0; j < k; ++ j) {
            putchar(s[i + j]);
        }
        printf(" %d\n", (int)(choice[i] - i) / k);
    }
    return 0;
}
