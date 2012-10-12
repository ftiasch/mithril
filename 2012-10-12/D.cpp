#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 50;

int n, cut[N][N];

#define foreach(i, v) for (typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

bool valid;
vector <pair <pair <int, int>, int> > edges;

int parent[N];
bool visit[N];

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

bool merge(int i, int j) {
    if (find(i) == find(j)) {
        return false;
    }
    parent[find(i)] = find(j);
    return true;
}

void construct(vector <int> vertices) {
    if (valid && (int)vertices.size() > 1) {
        int minimum = INT_MAX;
        foreach(a, vertices) {
            foreach(b, vertices) {
                if (*a != *b) {
                    minimum = min(minimum, cut[*a][*b]);
                }
            }
        }
        foreach (iter, vertices) {
            parent[*iter] = *iter;
        }
        int component = (int)vertices.size();
        foreach(a, vertices) {
            foreach(b, vertices) {
                if (*a != *b && cut[*a][*b] > minimum) {
                    component -= merge(*a, *b);
                }
            }
        }
        if (component == 1) {
            valid = false;
        } else {
            memset(visit, 0, sizeof(visit));
            int last = -1;
            vector <vector <int> > newVertices;
            foreach(a, vertices) {
                if (!visit[*a]) {
                    if (last != -1) {
                        edges.push_back(make_pair(make_pair(last, *a), minimum));
                    }
                    last = *a;
                    newVertices.push_back(vector <int>());
                    foreach(b, vertices) {
                        if (find(*a) == find(*b)) {
                            newVertices.back().push_back(*b);
                            visit[*b] = true;
                        }
                    }
                }
            }
            foreach(v, newVertices) {
                construct(*v);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%d", &cut[i][j]);
        }
    }
    vector <int> vertices;
    for (int i = 0; i < n; ++ i) {
        vertices.push_back(i);
    }
    valid = true;
    construct(vertices);
    if (!valid) {
        puts("NO");
    } else {
        puts("YES");
        printf("%d\n", (int)edges.size());
        foreach(iter, edges) {
            printf("%d %d %d\n", iter->first.first + 1, iter->first.second + 1, iter->second);
        }
    }
    return 0;
}
