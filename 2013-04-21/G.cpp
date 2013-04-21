#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <deque>
#include <iostream>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

typedef long long LL;

const int N = 100000;
const LL INF = 1000000000000000000LL;

int n, x[N], c[N], t[N];
LL maximum[N];

struct Line {
    LL k, b;

    Line(LL k, LL b): k(k), b(b) {}

    LL on(LL x) {
        return k * x + b;
    }
};

bool operator <(const Line &a, const Line &b) {
    if (a.k != b.k) {
        return a.k < b.k;
    }
    return a.b > b.b;
}

bool convex(const Line &u, const Line &v, const Line &w) {
    return (u.b - v.b) * (w.k - v.k) < (v.b - w.b) * (v.k - u.k);
}

void solve(int l, int r) {
    if (r - l > 1) {
        int m = l + r >> 1;
        solve(l, m);
        for (int _ = 0; _ < 2; ++ _) {
            std::vector <Line> lines;
            std::vector <std::pair <int, int> > queries;
            for (int i = l; i < m; ++ i) {
                if (_ == 0) {
                    lines.push_back(Line(-c[i], (long long)c[i] * x[i] + maximum[i]));
                } else {
                    lines.push_back(Line(c[i], (long long)-c[i] * x[i] + maximum[i]));
                }
            }
            std::sort(lines.begin(), lines.end());
            std::deque <Line> queue;
            foreach (iter, lines) {
                if (!queue.empty() && queue.back().k == iter->k) {
                    continue;
                }
                while ((int)queue.size() >= 2 && !convex(queue[(int)queue.size() - 2], queue.back(), *iter)) {
                    queue.pop_back();
                }
                queue.push_back(*iter);
            }
            for (int i = m; i < r; ++ i) {
                queries.push_back(std::make_pair(x[i], i));
            }
            std::sort(queries.begin(), queries.end());
            foreach (iter, queries) {
                while ((int)queue.size() >= 2 && queue[0].on(iter->first) < queue[1].on(iter->first)) {
                    queue.pop_front();
                }
                maximum[iter->second] = std::max(maximum[iter->second], queue[0].on(iter->first) + t[iter->second]);
            }
        }
        solve(m, r);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", x + i, c + i, t + i);
    }
    std::fill(maximum, maximum + n, -INF);
    maximum[0] = 0;
    solve(0, n);
    std::cout << maximum[n - 1] << std::endl;
    return 0;
}
