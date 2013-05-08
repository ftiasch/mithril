#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

const int N = 500000;
const long long INF = 1000000000000000000LL;

int n, s[N];

int get_id(int l, int r) {
    return l + r | l != r;
}

std::vector <int> lines[N << 1];

bool check(int i, int j, int k) {
    return (long long)(s[i] - s[j]) * (k - j) < (long long)(s[j] - s[k]) * (j - i);
}

void build(int l, int r) {
    std::vector <int> &ls = lines[get_id(l, r)];
    for (int i = l; i <= r; ++ i) {
        while ((int)ls.size() >= 2 && !check(ls[(int)ls.size() - 2], ls.back(), i)) {
            ls.pop_back();
        }
        ls.push_back(i);
    }
    if (l < r) {
        int m = l + r >> 1;
        build(l, m);
        build(m + 1, r);
    }
}

long long query(int l, int r, int a, int b, int z) {
    if (b < l || r < a) {
        return -INF;
    }
    if (a <= l && r <= b) {
        std::vector <int> &ls = lines[get_id(l, r)];
        int low = 0;
        int high = (int)ls.size() - 1;
        while (low < high) {
            int middle = low + high >> 1;
            if ((s[ls[middle]] - s[ls[middle + 1]]) <  (long long)(ls[middle + 1] - ls[middle]) * z) {
                low = middle + 1;
            } else {
                high = middle;
            }
        }
        return s[ls[high]] + (long long)ls[high] * z;
    }
    int m = l + r >> 1;
    return std::max(query(l, m, a, b, z), query(m + 1, r, a, b, z));
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", s + i);
    }
    build(0, n - 1);
    while (m --) {
        int a, b, z;
        scanf("%d%d%d", &a, &b, &z);
        a --;
        b --;
        long long start = (1LL - a) * z;
        printf("%I64d\n", query(0, n - 1, a, b, z) + start);
    }
    return 0;
}
