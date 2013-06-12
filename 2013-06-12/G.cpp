#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100;

int n, new_type[N];
char type[N][20];
std::vector <int> graph[N];

int visit[1 << 9][N], back[1 << 9][N];

int get_id(int mask, int u) {
    return u << 9 | mask;
}

int main() {
    scanf("%d", &n);
    std::map <std::string, int> mapping;
    for (int i = 0; i < n; ++ i) {
        scanf("%s", type[i]);
        mapping[type[i]] = -1;
        int k;
        scanf("%d", &k);
        while (k --) {
            int j;
            scanf("%d", &j);
            graph[i].push_back(-- j);
        }
    }
    int visit_count = 0;
    for (int _ = 0; _ < 10000; ++ _) {
        foreach (iter, mapping) {
            iter->second = rand() % 9;
        }
        for (int i = 0; i < n; ++ i) {
            new_type[i] = mapping[type[i]];
        }
        visit_count ++;
        std::queue <int> queue;
        for (int i = 0; i < n; ++ i) {
            visit[1 << new_type[i]][i] = visit_count;
            queue.push(get_id(1 << new_type[i], i));
        }
        bool found = false;
        while (!queue.empty() && !found) {
            int u = queue.front() >> 9;
            int mask = queue.front() & 511;
            queue.pop();
            foreach (iter, graph[u]) {
                int v = *iter;
                if ((~mask >> new_type[v] & 1) && visit[mask | 1 << new_type[v]][v] != visit_count) {
                    back[mask | 1 << new_type[v]][v] = u;
                    visit[mask | 1 << new_type[v]][v] = visit_count;
                    found |= (mask | 1 << new_type[v]) == 511;
                    queue.push(get_id(mask | 1 << new_type[v], v));
                }
            }
        }
        if (found) {
            std::vector <int> answer;
            int u = 0;
            while (visit[511][u] != visit_count) {
                u ++;
            }
            int mask = 511;
            while (mask) {
                answer.push_back(u);
                int v = back[mask][u];
                mask ^= 1 << new_type[u];
                u = v;
            }
            std::reverse(answer.begin(), answer.end());
            for (int i = 0; i < 9; ++ i) {
                if (i) {
                    printf(" ");
                }
                printf("%d", answer[i] + 1);
            }
            puts("");
            return 0;
        }
    }
    puts("fail");
    return 0;
}

