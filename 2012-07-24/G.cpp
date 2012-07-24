#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 500;

int n, weight[N], parent[N];
char graph[N][N + 1];

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

pair <int, int> solve(vector <int> v, bool reverse) { 
//putchar('{');
//for (int i = 0; i < (int)v.size(); ++ i) {
//    printf("%d, ", v[i]);
//}
//puts("}");
    if ((int)v.size() == 1) {
        int i = v.front();
        return make_pair(weight[i], weight[i]);
    }
    for (int i = 0; i < (int)v.size(); ++ i) {
        parent[v[i]] = v[i];
    }
    for (int i = 0; i < (int)v.size(); ++ i) {
        for (int j = 0; j < i; ++ j) {
            if ((graph[v[i]][v[j]] - '0') ^ reverse) {
                if (find(v[i]) != find(v[j])) {
                    parent[find(v[i])] = find(v[j]);
                }
            }
        }
    }
    bool connect = true;
    for (int i = 0; i < (int)v.size(); ++ i) {
        connect &= find(v[0]) == find(v[i]);
    }
    if (connect) {
        pair <int, int> ret = solve(v, reverse ^ 1);
        return make_pair(ret.second, ret.first);
    } else {
        pair <int, int> ret = make_pair(0, 0);
        vector <bool> used(v.size());
        for (int i = 0; i < (int)v.size(); ++ i) {
            if (!used[i]) {
                vector <int> newV;
                for (int j = 0; j < (int)v.size(); ++ j) {
                    if (find(v[i]) == find(v[j])) {
                        used[j] = true;
                        newV.push_back(v[j]);
                    }
                }
                pair <int, int> tmp = solve(newV, reverse);
                ret = make_pair(max(ret.first, tmp.first), ret.second + tmp.second);
            }
        }
        return ret;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", graph[i]);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", weight + i);
    }
    vector <int> v;
    for (int i = 0; i < n; ++ i) {
        v.push_back(i);
    }
    printf("%d\n", solve(v, false).first);
    return 0;
}
