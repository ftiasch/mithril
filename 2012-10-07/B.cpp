#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1000;

int n, parent[N], value[N];
vector <int> children[N];

int gcd(int a, int b) {
    return b == 0? a: gcd(b, a % b);
}

int allGcd[N];
vector <int> primes[N], divisors[N], choice[N];
vector <short> found[N];

void dfs(int u) {
    allGcd[u] = value[u] == -1? 0: value[u];
    for (vector <int> :: iterator iter = children[u].begin();
            iter != children[u].end(); ++ iter) {
        int v = *iter;
        dfs(v);
        allGcd[u] = gcd(allGcd[u], allGcd[v]);
    }
}

bool solve(int u, int b) {
    if (value[u] != -1) {
        return b < value[u] && value[u] % b == 0;
    }
    int t = lower_bound(divisors[u].begin(), divisors[u].end(), b) - divisors[u].begin();
    if (found[u][t] == -1) {
        found[u][t] = false;
        for (vector <int> :: iterator p = primes[u].begin(); 
                p != primes[u].end(); ++ p) {
            if (allGcd[u] % ((long long)b * (*p)) == 0) {
                bool valid = true;
                for (vector <int> :: iterator c = children[u].begin();
                        c != children[u].end(); ++ c) {
                    valid &= solve(*c, b * (*p));
                }
                if (valid) {
                    found[u][t] = true;
                    choice[u][t] = *p;
                    break;
                }
            }
        }
    }
    return found[u][t];
}

void construct(int u, int b) {
    if (value[u] == -1) {
        int t = lower_bound(divisors[u].begin(), divisors[u].end(), b) - divisors[u].begin();
        int p = choice[u][t];
        value[u] = b * p;
        for (vector <int> :: iterator c = children[u].begin(); 
                c != children[u].end(); ++ c) {
            construct(*c, b * p);
        }
    }
}

int main() {
    freopen("divisibility-tree.in", "r", stdin);
    freopen("divisibility-tree.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", parent + i, value + i);
        if (parent[i] != -1) {
            children[-- parent[i]].push_back(i);
        }
    }
    int root = 0;
    while (parent[root] != -1) {
        root ++;
    }
    dfs(root);
    for (int i = 0; i < n; ++ i) {
        int m = allGcd[i];
        for (int d = 1; d * d <= m; ++ d) {
            if (m % d == 0) {
                divisors[i].push_back(d);
                if (d * d != m) {
                    divisors[i].push_back(m / d);
                }
            }
        }
        sort(divisors[i].begin(), divisors[i].end());
        int s = divisors[i].size();
        found[i].resize(s);
        choice[i].resize(s);
        fill(found[i].begin(), found[i].end(), -1);
        for (int d = 2; d * d <= m; ++ d) {
            if (m % d == 0) {
                primes[i].push_back(d);
                while (m % d == 0) {
                    m /= d;
                }
            }
        }
        if (m > 1) {
            primes[i].push_back(m);
        }
    }
    bool valid = true;
    for (vector <int> :: iterator iter = children[root].begin();
            iter != children[root].end(); ++ iter) {
        valid &= solve(*iter, 1);
    }
    if (valid) {
        if (value[root] == -1) {
            value[root] = 1;
        }
        for (vector <int> :: iterator iter = children[root].begin();
                iter != children[root].end(); ++ iter) {
            construct(*iter, 1);
        }
    } else {
        for (int i = 0; i < n; ++ i) {
            value[i] = -1;
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", value[i], i == n - 1? '\n': ' ');
    }
    return 0;
}
