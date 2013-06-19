#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>

const int N = 100000;

struct DisjointSet {
    int parent[N];
    
    DisjointSet() {
        for (int i = 0; i < N; ++ i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void link(int u, int v) {
        parent[u] = v;
    }
};

int n, k, a[N], delta[N];
long long sum[N + 1];
DisjointSet left, right;

struct Range {
    int l, r;

    Range() {}
    Range(int l, int r) : l(l), r(r) {}

    long long value() const {
        return sum[l] + sum[r];
    }

    bool valid() {
        if (left.find(l) != l || right.find(l) != l) {
            return false;
        }
        if (left.find(r) != r || right.find(r) != r) {
            return false;
        }
        if (l + 1 == r) {
            return true;
        }
        return left.find(l + 1) == r - 1 && right.find(r - 1) == l + 1;
    }
};

bool operator <(const Range &a, const Range &b) {
    return a.value() > b.value();
}

void merge(int a, int b) {
    left.link(a, b);
    right.link(b, a);
}

int main() {
//freopen("D.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    std::sort(a, a + n);
    long long max_answer = 0;
    for (int i = 0; i < k; ++ i) {
        max_answer += a[n - 1 - i] - a[i];
    }
    for (int i = 0; i + 1 < n; ++ i) {
        delta[i] = a[i + 1] - a[i];
    }
    sum[n - 1] = 0;
    for (int i = n - 2; i >= 0; -- i) {
        sum[i] = delta[i] - sum[i + 1];
    }
    std::priority_queue <Range> heap;
    for (int i = 1; i < n; ++ i) {
        heap.push(Range(i - 1, i));
    }
    long long min_answer = 0;
    for (int _ = 0; _ < k; ++ _) {
        Range ret;
        do {
            ret = heap.top();
            heap.pop();
        } while (!ret.valid());
        min_answer += ret.value();
        int l = ret.l;
        int r = ret.r;
        merge(l, l + 1);
        merge(r - 1, r);
        while (l > 0 && right.find(l - 1) != l - 1) {
            merge(l - 1, l);
            l = right.find(l);
        }
        while (r + 1 < n && left.find(r + 1) != r + 1) {
            merge(r, r + 1);
            r = left.find(r);
        }
        -- l;
        ++ r;
        if (0 <= l && r < n) {
            heap.push(Range(l, r));
        }
    }
    std::cout << max_answer << " " << min_answer << std::endl;
    return 0;
}
