#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int N = 1000005;

char buffer[N];
int fail[N];

int main() {
    freopen("decimal.in", "r", stdin);
    freopen("decimal.out", "w", stdout);
    scanf("%s", buffer);
    int n = strlen(buffer);
    fail[n - 1] = n;
    for (int i = n - 2; buffer[i] != '.'; -- i) {
        fail[i] = n;
        int j = i + 1;
        while (j != n) {
            j = fail[j];
            if (buffer[i] == buffer[j - 1]) {
                fail[i] = j - 1;
                break;
            }
        }
    }
    int x = std::min_element(fail + 2, fail + n) - fail;
    putchar(buffer[0]);
    putchar(buffer[1]);
    for (int i = 2; i < x; ++ i) {
        putchar(buffer[i]);
    }
    putchar('(');
    for (int i = x; i < fail[x]; ++ i) {
        putchar(buffer[i]);
    }
    putchar(')');
    puts("");
    return 0;
}
