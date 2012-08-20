#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100000;
const unsigned long long MAGIC = 137ULL;

char mapping[26], text[N + 1], unmapping[26];
unsigned long long textHash[N + 1], cipherHash[N + 1], power[N + 1];

int main() {
    power[0] = 1;
    for (int i = 1; i <= N; ++ i) {
        power[i] = power[i - 1] * MAGIC;
    }
    int testCount;
    scanf("%d", &testCount);
    while (testCount --) {
        scanf("%s%s", mapping, text);
        for (int i = 0; i < 26; ++ i) {
            unmapping[mapping[i] - 'a'] = 'a' + i;
        }
        int n = strlen(text);
        textHash[n] = 0;
        for (int i = n - 1; i >= 0; -- i) {
            textHash[i] = textHash[i + 1] * MAGIC + text[i];
        }
        cipherHash[n] = 0;
        for (int i = n - 1; i >= 0; -- i) {
            cipherHash[i] = cipherHash[i + 1] * MAGIC + mapping[text[i] - 'a'];
        }
        int i = (n + 1) / 2;
        while (true) {
            int length = min(i, n - i);
            if (textHash[0] - textHash[length] * power[length] == cipherHash[i] - cipherHash[i + length] * power[length]) {
                break;
            }
            i ++;
        }
        //printf("%d\n", i);
        for (int k = 0; k < i; ++ k) {
            putchar(text[k]);
        }
        for (int k = 0; k < i; ++ k) {
            putchar(unmapping[text[k] - 'a']);
        }
        puts("");
    }
    return 0;
}
