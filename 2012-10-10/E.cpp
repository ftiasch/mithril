#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000 + 1;

int n, m, t, enter[N], leave[N];
long long counter[N];

int dist(int i, int j) {
    int d = abs(i - j);
    return min(d, m - d);
}

void insert(int k, int v) {
    for (int i = k; i <= n; i += i & -i) {
        counter[i] += v;
    }
}

long long query(int k) {
    long long result = 0;
    for (int i = k; i >= 1; i -= i & -i) {
        result += counter[i];
    }
    return result;
}

int main() {
    freopen("lair.in", "r", stdin);
    freopen("lair.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 1; i <= n; ++ i) {
        enter[i] = leave[i] = 1;
    }
    memset(counter, 0, sizeof(counter));
    for (int i = 1; i <= n; ++ i) {
        insert(i, dist(enter[i], leave[i]));
    }
    while (t --) {
        char buffer[5];
        scanf("%s", buffer);
        if (*buffer == 'M') {
            int k, p, q;
            scanf("%d%d%d", &k, &p, &q);
            insert(k, -dist(enter[k], leave[k]));
            leave[k] = p;
            insert(k, dist(enter[k], leave[k]));
            k ++;
            insert(k, -dist(enter[k], leave[k]));
            enter[k] = q;
            insert(k, dist(enter[k], leave[k]));
        } else {
            int k_0, i_0, k_1, i_1;
            scanf("%d%d%d%d", &k_0, &i_0, &k_1, &i_1);
            if (k_0 > k_1) {
                swap(k_0, k_1);
                swap(i_0, i_1);
            }
            if (k_0 == k_1) {
                cout << dist(i_0, i_1) << endl;
            } else {
                cout << dist(i_0, leave[k_0]) + dist(enter[k_1], i_1) + query(k_1 - 1) - query(k_0) + k_1 - k_0 << endl;
            }
        }
    }
    return 0;
}
