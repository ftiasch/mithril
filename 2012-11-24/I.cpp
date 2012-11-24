#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <utility>
#include <algorithm>
using namespace std;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

const int N = 100000;

int n, answer, from, to, type[N + 1];
char buffer[N + 1];
vector <int> adjacent[N];

bool mark[N];

int size[N], max_subtree[N];
vector <int> nodes;

void dfs(int p, int u) {
    nodes.push_back(u);
    size[u] = 1;
    max_subtree[u] = 0;
    foreach (iter, adjacent[u]) {
        if (*iter != p && !mark[*iter]) {
            dfs(u, *iter);
            size[u] += size[*iter];
            max_subtree[u] = max(max_subtree[u], size[*iter]);
        }
    }
}

struct Array { // -n .. n
    int time, stamp[(N << 1) + 1];
    pair <int, int> value[(N << 1) + 1];

    Array() {
        time = -1;
        memset(stamp, -1, sizeof(stamp));
    }

    void clear() {
        time ++;
    }

    pair <int, int> &operator[](int key) {
        int k = key + n;
        if (stamp[k] != time) {
            stamp[k] = time;
            value[k] = make_pair(INT_MIN, -1);
        }
        return value[k];
    }
};

Array hash;

vector <pair <int, pair <int, int> > > paths;

void search(int p, int u, int difference, int depth) {
    difference += type[u];
    paths.push_back(make_pair(difference, make_pair(depth, u)));
    foreach (iter, adjacent[u]) {
        if (*iter != p && !mark[*iter]) {
            search(u, *iter, difference, depth + 1);
        }
    }
}

void divide(int root) {
    nodes.clear();
    dfs(-1, root);
    int new_root = root;
    {
        int value = INT_MAX;
        foreach (iter, nodes) {
            int ret = max(size[root] - size[*iter], max_subtree[*iter]);
            if (ret < value) {
                value = ret;
                new_root = *iter;
            }
        }
    }
    hash.clear();
    hash[type[new_root]] = make_pair(0, new_root);
    foreach (iter, adjacent[new_root]) {
        if (!mark[*iter]) {
            paths.clear(); // (difference, (depth, id))
            search(new_root, *iter, 0, 1);
            foreach (path, paths) {
                if (hash[-path->first].second != -1 && hash[-path->first].first + path->second.first > answer) {
                    answer = hash[-path->first].first + path->second.first;
                    from = hash[-path->first].second;
                    to = path->second.second;
                }
            }
            foreach (path, paths) {
                pair <int, int> &ret = hash[path->first + type[new_root]];
                ret = max(ret, make_pair(path->second.first, path->second.second));
            }
        }
    }
    mark[new_root] = true;
    foreach (iter, adjacent[new_root]) {
        if (!mark[*iter]) {
            divide(*iter);
        }
    }
}

bool print(int p, int u, int v) {
    bool ret = false;
    if (u == v) {
        ret = true;
    }
    foreach (iter, adjacent[u]) {
        if (*iter != p) {
            ret |= print(u, *iter, v);
        }
    }
    if (ret) {
        printf("%d ", u + 1);
    }
    return ret;
}

int main() {
    freopen("shoes.in", "r", stdin);
    freopen("shoes.out", "w", stdout);
    scanf("%d%s", &n, buffer);
    for (int i = 0; i < n; ++ i) {
        type[i] = buffer[i] == 'R' ? 1 : -1;
    }
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b --;
        adjacent[a].push_back(b);
        adjacent[b].push_back(a);
    }
    answer = -1;
    memset(mark, 0, sizeof(mark));
    divide(0);
    printf("%d\n", answer + 1);
    if (answer != -1) {
        print(-1, from, to);
        puts("");
    }
    return 0;
}
