#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define FOR(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++ i)

const int maxn = 50005;
const int maxm = maxn * 15 + 5;

namespace Hopcroft
{
    int cx[maxn], cy[maxn], mk[maxn], q[maxn], src[maxn], pre[maxn];
    int head[maxn], vtx[maxm], next[maxm], tot, n, m;
    
    inline void clear(int left, int right) {
        n = left;
        m = right;
        tot = 2;
        memset(head, 0, sizeof(head));
    }

    inline void add(int a, int b) 
    {
//printf("%d %d\n", a, b);
        vtx[tot] = b;
        next[tot] = head[a];
        head[a] = tot ++;
    }

    inline int maxMatch()
    {
        memset(mk, -1, sizeof(mk));
        memset(cx, -1, sizeof(cx));
        memset(cy, -1, sizeof(cy));
        for (int p = 1, fl = 1, h, tail; fl; ++ p) {
            fl = 0;
            h = tail = 0;
            for (int i = 0; i < n; ++ i) {
                if (cx[i] == -1) {
                    q[++ tail] = i;
                    pre[i] = -1;
                    src[i] = i;
                }
            }
            for (h = 1; h <= tail; ++ h) {
                int u = q[h];
                if (cx[src[u]] != -1) {
                    continue;
                }
                for (int pp = head[u], v = vtx[pp]; pp; pp = next[pp], v = vtx[pp]) {
                    if (mk[v] != p) {
                        mk[v] = p;
                        q[++ tail] = cy[v];
                        if (cy[v] >= 0) {
                            pre[cy[v]] = u;
                            src[cy[v]] = src[u];
                            continue;
                        }
                        int d, e, t;
                        for (--tail, fl = 1, d = u, e = v; d != -1; t = cx[d], cx[d] = e, cy[e] = d, e = t, d = pre[d]);
                        break;
                    }
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++ i) {
            res += cx[i] != -1;
        }
        return res;
    }
};

map<vector<int>, int> states[2];
vector<vector<int> > record[2];

inline void generate(int i, const vector<int> &capacity, vector<int> &current, int mod2)
{
    if (i >= capacity.size()) {
        int cur = states[mod2].size();
        record[mod2].push_back(current);
        states[mod2][current] = cur;
        return;
    }
    for (current[i] = 0; current[i] <= capacity[i]; ++ current[i]) {
        generate(i + 1, capacity, current, (mod2 + current[i]) % 2);
    }
}

inline int solve(int mod2, int forbid, const vector<int> &capacity)
{
    Hopcroft::clear(states[mod2].size(), states[mod2 ^ 1].size());
    FOR (it, states[mod2]) {
        if (it->second == forbid) {
            continue;
        }
        vector<int> cur = it->first;
        for (int i = 0; i < cur.size(); ++ i) {
            if (cur[i] + 1 <= capacity[i]) {
                ++ cur[i];
                int v = states[mod2 ^ 1][cur];
                Hopcroft::add(it->second, v);
                -- cur[i];
            }
            if (cur[i] - 1 >= 0) {
                -- cur[i];
                int v = states[mod2 ^ 1][cur];
                Hopcroft::add(it->second, v);
                ++ cur[i];
            }
        }
    }
    return Hopcroft::maxMatch();
}

int main()
{
    for (int nBox;scanf("%d", &nBox) == 1 && nBox;) {
        vector<int> capacity(nBox, 0), init(nBox, 0), current(nBox, 0);
        for (int i = 0; i < nBox; ++ i) {
            scanf("%d", &capacity[i]);
        }
        int mod2 = 0;
        for (int i = 0; i < nBox; ++ i) {
            scanf("%d", &init[i]);
            mod2 += init[i];
            mod2 %= 2;
        }
        
        states[0].clear();
        states[1].clear();
        record[0].clear();
        record[1].clear();
        
        generate(0, capacity, current, 0);
        
        int start = states[mod2][init];
        
        int maxi = solve(mod2, -1, capacity);
        int del = solve(mod2, start, capacity);
        
//        printf("maxi = %d, del = %d\n", maxi, del); fflush(stdout);
        
        if (maxi != del) {
            puts("Alice");fflush(stdout);
            solve(mod2, -1, capacity);
            while (true) {
                start = states[mod2][init];
                current = record[mod2 ^ 1][Hopcroft::cx[start]];
                for (int i = 0; i < current.size(); ++ i) {
                    if (current[i] < init[i]) {
                        printf("%d -\n", i + 1);
                    } else if (current[i] > init[i]){
                        printf("%d +\n", i + 1);
                    }
                }
                fflush(stdout);
                int id; char op[10];
                scanf("%d%s", &id, op);
                if (id == 0) {
                    break;
                }
                -- id;
                init = current;
                if (op[0] == '+') {
                    ++ init[id];
                } else {
                    -- init[id];
                }
            }
        } else {
            puts("Bob");fflush(stdout);
            int id; char op[10];
            scanf("%d%s", &id, op);
            if (id) {
                -- id;
                if (op[0] == '+') {
                    ++ init[id];
                } else {
                    -- init[id];
                }
                while (true) {
                    start = states[mod2 ^ 1][init];
//printf("    start = %d, node = %d\n", start, Hopcroft::cy[start]);
                    current = record[mod2][Hopcroft::cy[start]];
                    for (int i = 0; i < current.size(); ++ i) {
                        if (current[i] < init[i]) {
                            printf("%d -\n", i + 1);
                        } else if (current[i] > init[i]){
                            printf("%d +\n", i + 1);
                        }
                    }
                    fflush(stdout);
                    init = current;
                    
                    int id; char op[10];
                    scanf("%d%s", &id, op);
                    if (id == 0) {
                        break;
                    }
                    -- id;
                    if (op[0] == '+') {
                        ++ init[id];
                    } else {
                        -- init[id];
                    }
                }
            }
        }
    }
    return 0;
}

