#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100001;

int treapCount, weight[N], sons[N][2], total[N], size[N];
long long key[N];

void update(int &x) {
    size[x] = size[sons[x][0]] + total[x] + size[sons[x][1]];
}

void rotate(int &x, int t) {
    int y = sons[x][t];
    sons[x][t] = sons[y][1 ^ t];
    sons[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, long long k) {
    if (x == 0) {
        x = treapCount ++;
        key[x] = k;
        weight[x] = rand();
        sons[x][0] = sons[x][1] = 0;
        total[x] = 1;
    } else if (key[x] == k) {
        total[x] ++;
    } else {
        int t = key[x] < k;
        insert(sons[x][t], k);
        if (weight[sons[x][t]] < weight[x]) {
            rotate(x, t);
        }
    }
    update(x);
}

int query(int &x, long long k) {
    if (x == 0) {
        return 0;
    }
    if (key[x] >= k) {
        return query(sons[x][0], k);
    }
    return query(sons[x][1], k) + total[x] + size[sons[x][0]];
}

int p, q, n;

int main() {
    treapCount = 1;
    size[0] = 0;
    weight[0] = INT_MAX;
    scanf("%d%d%d", &p, &q, &n);
    int root = 0;
    long long result = 0;
    for (int i = 0; i < n; ++ i) {
        int a;
        scanf("%d", &a);
        result += query(root, (long long)q * a);
        insert(root, (long long)p * a);
    }
    cout << result << endl;
    return 0;
}
