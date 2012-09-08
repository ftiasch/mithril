#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;

const int N = 50000;

int edgeCount, firstEdge[N], to[N << 1], nextEdge[N << 1], degree[N];

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

int treeSize[N], maxSubTree[N];

void countSize(int p, int u) {
    treeSize[u] = 1;
    maxSubTree[u] = 0;
    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        int v = to[iter];
        if (v != p) {
            countSize(u, v);
            treeSize[u] += treeSize[v];
            maxSubTree[u] = max(maxSubTree[u], treeSize[v]);
        }
    }
}


typedef unsigned long long ULL;

const int MAGIC = 37;

ULL magicPower[(N << 1) + 1];

struct TreeHash {
    int length;
    ULL hash;

    TreeHash(int token): length(1), hash(token) {}
    TreeHash(int length, ULL hash): length(length), hash(hash) {}
};

TreeHash operator +(const TreeHash &a, const TreeHash &b) {
    return TreeHash(a.length + b.length,
                    a.hash * magicPower[b.length] + b.hash);
}

bool operator <(const TreeHash &a, const TreeHash &b) {
    if (a.length == b.length) {
        return a.hash < b.hash;
    }
    return a.length < b.length;
}

bool operator ==(const TreeHash &a, const TreeHash &b) {
    return a.length == b.length && a.hash == b.hash;
}


const int MOD = 1000000007;

int inverse(int a) {
    if (a == 1) {
        return 1;
    }
    return (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

const int L = 200000;

int factorial[L + 1];

int choose(int n, int k) {
    return (long long)factorial[n] * inverse(k) % MOD 
            * inverse(n - k) % MOD;
}

typedef pair <TreeHash, int> Pair;

int combine(vector <Pair> &children) {
    sort(children.begin(), children.end());
    int ways = 1;
    for (int low = 0; low < (int)children.size(); ++ low) {
        int high = low;
        while (high < (int)children.size() && 
                children[low].first == children[high].first) {
            high ++;
        }
        int number = high - low;
        int color = children[low].second + number - 1;
        for (int i = 0; i < number; ++ i) {
            ways = (long long)ways * (color - i) % MOD;
        }
        ways = (long long)ways * inverse(factorial[number]) % MOD;
        low = high - 1;
    }
    return ways;
}

Pair solve(int p, int u) {
    vector <Pair> children;
    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        int v = to[iter];
        if (v != p) {
            children.push_back(solve(u, v));
        }
    }
    int ways = (long long)combine(children) * m % MOD;
    TreeHash hash(0);
    for (int i = 0; i < (int)children.size(); ++ i) {
        hash = hash + children[i].first;
    }
    return make_pair(hash + TreeHash(1), ways);
}

int main() {
    magicPower[0] = 1;
    for (int i = 0; i < N << 1; ++ i) {
        magicPower[i + 1] = magicPower[i] * MAGIC;
    }
    factorial[0] = 1;
    for (int i = 0; i < L; ++ i) {
        factorial[i + 1] = (long long)factorial[i] * (i + 1) % MOD;
    }
    while (scanf("%d%d", &n, &m) == 2) {
        edgeCount = 0;
        memset(firstEdge, -1, sizeof(firstEdge));
        for (int i = 0; i < n - 1; ++ i) {
            int a, b;
            scanf("%d%d", &a, &b);
            a --; 
            b --;
            addEdge(a, b);
            addEdge(b, a);
        }
        countSize(-1, 0);
        for (int i = 0; i < n; ++ i) {
            maxSubTree[i] = max(maxSubTree[i], n - treeSize[i]);
        }
        int minMaxSubTree = *min_element(maxSubTree, maxSubTree + n);
        vector <int> centroid;
        for (int i = 0; i < n; ++ i) {
            if (maxSubTree[i] == minMaxSubTree) {
                centroid.push_back(i);
            }
        }
        if ((int)centroid.size() == 1) {
            printf("%d\n", solve(-1, centroid[0]).second);
        } else {
            int u = centroid[0];
            int v = centroid[1];
            vector <Pair> children;
            children.push_back(solve(u, v));
            children.push_back(solve(v, u));
            printf("%d\n", combine(children));
        }
    }
    return 0;
}
