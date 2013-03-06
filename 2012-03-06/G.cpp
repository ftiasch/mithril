#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

typedef unsigned long long ULL;

const int N = 2000000;
const int MAGIC = 127;

int n, m;
char a[N], b[N];

ULL ha[N + 1], hb[N + 1], power[N + 1];

void prepare_hash(const char *a, int n, ULL *h) {
    h[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        h[i] = h[i + 1] * MAGIC + a[i];
    }
}

bool compare_bprefix(int i, int j) {
    int low = 0;
    int high = m;
    while (low < high) {
        int middle = low + high + 1 >> 1;
        if (hb[i] - power[middle] * hb[i + middle] == hb[j] - power[middle] * hb[j + middle]) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return b[i + low] < b[j + low];
}

int lcp(int x, int y) {
    x %= n;
    y %= m;
    int low = 0;
    int high = m;
    while (low < high) {
        int middle = low + high + 1 >> 1;
        if (ha[x] - power[middle] * ha[x + middle] == hb[y] - power[middle] * hb[y + middle]) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return low;
}

bool check(int x, int y) {
    if (ha[x] - power[m] * ha[x + m] == hb[y] - power[m] * hb[y + m]) {
        return true;
    }
    int l = lcp(x, y);
    return l + 1 + lcp(x + l + 1, y + l + 1) >= m;
}

int main() {
    scanf("%d%d%s%s", &n, &m, a, b);
    for (int i = 0; i < n; ++ i) {
        a[n + i] = a[i];
    }
    for (int i = 0; i < m; ++ i) {
        b[m + i] = b[i];
    }
    power[0] = 1;
    for (int i = 0; i < N; ++ i) {
        power[i + 1] = power[i] * MAGIC;
    }
    prepare_hash(a, 2 * n, ha);
    prepare_hash(b, 2 * m, hb);
    int best = 0;
    for (int i = 0; i < m; ++ i) {
        if (compare_bprefix(i, best)) {
            best = i;
        }
    }
    for (int i = 0; i < m; ++ i) {
        putchar(b[best + i]);
    }
    puts("");
    std::vector <int> choices;
    for (int i = 0; i < n; ++ i) {
        if (check(i, best)) {
            choices.push_back(i);
        }
    }
    int answer = choices.front() <= n - choices.back() ? choices.front() : choices.back();
    for (int i = 0; i < n; ++ i) {
        putchar(a[answer + i]);
    }
    puts("");
    return 0;
}
