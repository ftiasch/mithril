#include <cstdio>
#include <cstring>
#include <climits>
#include <map>
#include <vector>
#include <algorithm>

typedef unsigned long long Hash;

const Hash MAGIC = 100003;

const int M = 100;

int n, m, a[M], b[M];
Hash h[(M << 1) + 1], power;

Hash minimize() {
    std::map <int, int> map;
    for (int i = 0; i < m; ++ i) {
        map[a[i]] = i - m;
    }
    for (int i = 0; i < m; ++ i) {
        b[i] = i - map[a[i]];
        map[a[i]] = i;
    }
    h[m << 1] = 0;
    for (int i = (m << 1) - 1; i >= 0; -- i) {
        h[i] = h[i + 1] * MAGIC + b[i % m];
    }
    Hash ret = 0;
    for (int i = 0; i < m; ++ i) {
        ret = std::max(ret, h[i] - power * h[i + m]);
    }
    return ret;
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d%d", &n, &m);
        power = 1;
        for (int i = 0; i < m; ++ i) {
            power *= MAGIC;
        }

        std::vector <Hash> hashes;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf("%d", a + j);
            }
            hashes.push_back(minimize());
        }

        std::sort(hashes.begin(), hashes.end());
        //int answer = n * (n - 1) / 2;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && hashes[i] == hashes[j]) {
                j ++;
            }
            //int s = j - i;
            //answer -= s * (s - 1) / 2;
            i = j;
        }
        printf("%d\n", (int)(std::unique(hashes.begin(), hashes.end()) - hashes.begin()));
        //printf("%d\n", answer);
    }
    return 0;
}
