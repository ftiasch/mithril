#include <cstdio>
#include <cstring>
#include <cstdlib>

const int maxn = 105;

char s[maxn], t[maxn];
int f[maxn][maxn], pos[maxn];

inline void update(int &a, int b)
{
    if (a == -1 || a > b) {
        a = b;
    }
}

int main()
{
    int T, test = 1;
    for (scanf("%d", &T); T --; ++ test) {
        scanf("%s%s", s, t);
        int n = strlen(t), ones = 0;
        for (int i = 0; i < n; ++ i) {
            if (t[i] == '1') {
                pos[ones ++] = i;
            }
        }
        memset(f, -1, sizeof(f));
        f[0][0] = 0;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j <=i; ++ j) {
                if (f[i][j] != -1) {
                    if (s[i] == '0' || s[i] == '?') {
                        update(f[i + 1][j], f[i][j] + (s[i] == '?'));
                    }
                    if (j < ones && (s[i] == '1' || s[i] == '0' || s[i] == '?')) {
                        update(f[i + 1][j + 1], f[i][j] + (s[i] != '1') + (t[i] != '1'));
                    }
                }
            }
        }
        printf("Case %d: %d\n", test, f[n][ones]);
    }
    return 0;
}
