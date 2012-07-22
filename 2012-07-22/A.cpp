#include <cstdio>
#include <cstring>
using namespace std;

int n;
char a[103], b[103], alphabet[10 + 26 + 26];
bool need[256][2];

int main() {
    for (int i = 0; i < 10; ++ i) {
        alphabet[i] = '0' + i;
    }
    for (int i = 0; i < 26; ++ i) {
        alphabet[10 + i] = 'A' + i;
    }
    for (int i = 0; i < 26; ++ i) {
        alphabet[10 + 26 + i] = 'a' + i;
    }
    int testCount = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
        printf("Case %d: ", ++ testCount);
        bool valid = true;
        memset(need, 0, sizeof(need));
        for (int i = 0; i < n; ++ i) {
            scanf("%s%s", a, b);
            int lengthA = strlen(a) - 2;
            int lengthB = strlen(b) - 2;
            if (lengthB > lengthA) {
                valid = false;
            } else {
                for (int i = 1; i <= lengthB; ++ i) {
                    if (a[i] != b[i]) {
                        valid = false;
                    }
                }
                if (valid) {
                    for (int i = 1; i <= lengthB; ++ i) {
                        need[(int)b[i]][1] = true;
                    }
                    if (lengthA > lengthB) {
                        need[(int)a[lengthB + 1]][0] = true;
                    }
                }
            }
        }
        int forbidCount = 0;
        for (int i = 0; i < 62; ++ i) {
            if (need[(int)alphabet[i]][0]) {
                forbidCount ++;
            }
            if (need[(int)alphabet[i]][0] && need[(int)alphabet[i]][1]) {
                valid = false;
            }
        }
        if (!valid || forbidCount == 62) {
            puts("I_AM_UNDONE");
        } else {
            putchar('[');
            int lastNeed = 61;
            while (lastNeed >= 0 && !need[(int)alphabet[lastNeed]][1]) {
                lastNeed --;
            }
            if (lastNeed >= 0) {
                for (int i = 0; i <= lastNeed; ++ i) {
                    if (need[(int)alphabet[i]][0]) {
                        continue;
                    }
                    putchar(alphabet[i]);
                }
            } else {
                int firstValid = 0;
                while (need[(int)alphabet[firstValid]][0]) {
                    firstValid ++;
                }
                putchar(alphabet[firstValid]);
            }
            putchar(']');
            puts("");
        }
    }
    return 0;
}
