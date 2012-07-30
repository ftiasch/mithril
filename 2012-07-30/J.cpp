#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2000;
const int M = N << 2;

int n, m, limit, edgeCount, firstEdge[N], to[M], cost[M], nextEdge[M], degree[N];
bool leaf[N];
vector <int> chain, edges;

void addEdge(int u, int v, int w) {
    to[edgeCount] = v;
    cost[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

int main() {
    scanf("%d%d%d", &n, &m, &limit);
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a --;
        b --;
        degree[a] ++;
        degree[b] ++;
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    memset(leaf, 0, sizeof(leaf));
    for (int i = 0; i < n; ++ i) {
        leaf[i] = degree[i] == 1;
    }
    for (int i = 0; i < n; ++ i) {
        if (leaf[i]) {
            for (int iter = firstEdge[i]; iter != -1; iter = nextEdge[iter]) {
                degree[to[iter]] --;
            }
        }
    }
    bool isCircle = false;
    int source = 0;
    while (source < n && (leaf[source] || degree[source] > 1)) {
        source ++;
    }
    if (source == n) {
        isCircle = true;
        source = 0;
        while (leaf[source]) {
            source ++;
        }
    }
    {
        int i = source;
        chain.push_back(i);
        while (true) {
            bool found = false;
            for (int iter = firstEdge[i]; iter != -1 && !found; iter = nextEdge[iter]) {
                if (!leaf[to[iter]] && ((int)chain.size() <= 1 || chain[(int)chain.size() - 2] != to[iter])) {
                    found = true;
                    edges.push_back(iter);
                    chain.push_back(i = to[iter]);
                }
            }
            if (!found) {
                break;
            }
            if (chain.back() == source) {
                chain.pop_back();
                break;
            }
        }
    }
//for (int i = 0; i < (int)chain.size(); ++ i) {
//    printf("%d (%d, %d)\n", chain[i] + 1, to[edges[i] ^ 1] + 1, to[edges[i]] + 1);
//}
//puts("");
//printf("%d\n",chain.size());
    long long result = 1000000000000000000LL;
    int resultStart, resultLength;
    for (int i = 0; i < (int)chain.size(); ++ i) {
        long long heapCount = 0;
        long long newCost = 0;
        int newLimit = limit;
        priority_queue <int> heap;
        for (int j = 0; j <= (int)chain.size(); ++ j) {
            if (!isCircle && i + j >= (int)chain.size()) {
                break;
            }
            int k = (i + j) % (int)chain.size();
            int u = chain[k];
            if (j < (int)chain.size()) {
                for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                    if (leaf[to[iter]]) {
                        heapCount += cost[iter];
                        heap.push(cost[iter]);
                    }
                }
            }
            while ((int)heap.size() > newLimit) {
                heapCount -= heap.top();
                heap.pop();
            }
//printf(":: %d -> %d = %d \n", chain[i] + 1, chain[k] + 1, (int)heap.size());
            if ((int)heap.size() == newLimit) {
//printf("%d -> %d: %lld + %lld = %lld\n", chain[i] + 1, chain[k] + 1, newCost, heapCount, newCost + heapCount);
                if (newCost + heapCount < result) {
                    result = newCost + heapCount;
                    resultStart = i;
                    resultLength = j;
                }
                result = min(result, newCost + heapCount);
            }
            newLimit --;
            if (k < (int)edges.size()) {
                newCost += cost[edges[k]];
            }
            if (newLimit < 0) {
                break;
            }
        }
    }
    //cout << result << endl;
    vector <pair <int, int> > choices;
    for (int j = 0; j < resultLength; ++ j) {
        int k = (resultStart + j) % (int)chain.size();
        printf("%d\n", (edges[k] >> 1) + 1);
    }
    for (int j = 0; j <= resultLength; ++ j) {
        int k = (resultStart + j) % (int)chain.size();
        int u = chain[k];
        if (j < (int)chain.size()) {
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                if (leaf[to[iter]]) {
                    choices.push_back(make_pair(cost[iter], iter));
                }
            }
        }
    }
    sort(choices.begin(), choices.end());
    for (int i = 0; i < limit - resultLength; ++ i) {
        printf("%d\n", (choices[i].second >> 1) + 1);
    }
    return 0;
}
