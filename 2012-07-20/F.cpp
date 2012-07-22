#include <cstdio>
#include <cstring>
using namespace std;

const int N = 555555;

int n, best[N], mark[26];
bool used[N];
char text[N];

int main() {
    scanf("%s", text);
    n = strlen(text);
    memset(mark, -1, sizeof(mark));
    memset(best, -1, sizeof(best));
    for (int i = 0; i <= n; ++ i) {
        for (int c = 0; c < 26 && best[i] == -1; ++ c) {
            if (mark[c] != -1) {
                best[i] = mark[c];
            }
        }
        if (i < n) {
            mark[text[i] - 'a'] = i;
        }
    }
    memset(used, 0, sizeof(used));
    for (int i = n; i > 0; i = best[i]) {
        used[best[i]] = true;
    }
    for (int i = n - 1; i >= 0; -- i) {
        if (used[i]) {
            putchar(text[i]);
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (!used[i]) {
            putchar(text[i]);
        }
    }
    puts("");
    return 0;
}
