#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <utility>
#include <functional>
#include <iostream>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

typedef long long LL;

const int N = 50000;

int n, limit;
std::vector <std::pair <int, int> > edges[N];

int parent[N];
LL depth[N], answer;
std::set <LL> *sets[N];

void dfs(int p, int u) {
    std::vector <std::pair <int, int > > children;
    foreach (iter, edges[u]) {
        int v = iter->first;
        if (v != p) {
            children.push_back(std::make_pair((int)sets[v]->size(), v));
        }
    }
    std::sort(children.begin(), children.end(), std::greater <std::pair <int, int> >());
    if (children.empty()) {
        sets[u] = new std::set <LL>();
        sets[u]->insert(depth[u]);
    } else {
        sets[u] = sets[children.front().second];
        std::set <LL> :: iterator iter = sets[u]->lower_bound(depth[u] + limit);
        if (iter != sets[u]->end()) {
            answer = std::min(answer, (*iter - depth[u]) - limit);
        }
        if (iter != sets[u]->begin()) {
            iter --;
            answer = std::min(answer, limit - (*iter - depth[u]));
        }
        sets[u]->insert(depth[u]);
    }
    for (int i = 1; i < (int)children.size(); ++ i) {
        int v = children[i].second;
        foreach (iter, *sets[v]) {
            LL base = *iter - 2 * depth[u];
            std::set <LL> :: iterator key = sets[u]->lower_bound(limit - base);
            if (key != sets[u]->end()) {
                answer = std::min(answer, (*key + base) - limit);
            }
            if (key != sets[u]->begin()) {
                key --;
                answer = std::min(answer, limit - (*key + base));
            }
        }
        foreach (iter, *sets[v]) {
            sets[u]->insert(*iter);
        }
    }
}

int main() {
    scanf("%d%d", &n, &limit);
    for (int i = 0, a, b, c; i < n - 1; ++ i) {
        scanf("%d%d%d", &a, &b, &c);
        a --;
        b --;
        edges[a].push_back(std::make_pair(b, c));
        edges[b].push_back(std::make_pair(a, c));
    }
    answer = limit;
    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[0] = 0;
    std::vector <int> queue;
    queue.push_back(0);
    for (int head = 0; head < (int)queue.size(); ++ head) {
        int u = queue[head];
        foreach (iter, edges[u]) {
            int v = iter->first;
            if (depth[v] == -1) {
                parent[v] = u;
                depth[v] = depth[u] + iter->second;
                queue.push_back(v);
            }
        }
    }
    for (int i = (int)queue.size() - 1; i >= 0; -- i) {
        int u = queue[i];
        dfs(parent[u], u);
    }
    std::cout << answer << std::endl;
    return 0;
}
