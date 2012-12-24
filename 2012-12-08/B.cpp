#include <cstdio>
#include <cstring>

const int L = (26 << 1) + 1;

int n;
char sequence[L];
int counter[26], match[L];

void solve(int l, int r, int p) {
    if (p != -1) {
        counter[p] ++;
    }
    int t = sequence[l] - 'A';
    counter[t] ++;
    int i = l + 1;
    while (i < r) {
        solve(i, match[i], t);
        i = match[i] + 1;
    }
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf("%s", sequence);
        n = strlen(sequence);
        for (int i = 0; i < n; ++ i) {
            int j = i + 1;
            while (j < n && sequence[i] != sequence[j]) {
                j ++;
            }
            match[i] = j;
        }
        memset(counter, 0, sizeof(counter));
        solve(0, n - 1, -1);
        counter[sequence[0] - 'A'] --;
        printf("Case %d\n", t);
        for (int i = 0; i < 26; ++ i) {
            if (counter[i]) {
                printf("%c = %d\n", 'A' + i, counter[i]);
            }
        }
    }
    return 0;
}
