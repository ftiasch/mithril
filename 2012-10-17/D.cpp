#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = (100000 << 1) + 1;

int n, begin[N], end[N], parity[N], parent[N], relation[N], counter[N];
vector <int> values;

int find(int i) {
    if (parent[i] != i) {
        int p = find(parent[i]);
        relation[i] ^= relation[parent[i]];
        parent[i] = p;
    }
    return parent[i];
}

int getName(int x) {
    return lower_bound(values.begin(), values.end(), x) - values.begin();
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d", &n);
    values.push_back(0);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", begin + i, end + i, parity + i);
        values.push_back(begin[i] - 1);
        values.push_back(end[i]);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int m = (int)values.size();
    for (int i = 0; i < m; ++ i) {
        parent[i] = i;
        relation[i] = 0;
    }
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        int a = getName(begin[i] - 1);
        int b = getName(end[i]);
        if (find(a) == find(b)) {
            if ((relation[a] ^ relation[b]) != parity[i]) {
                break;
            }
        } else {
            int fa=find(a),fb=find(b);
            relation[fa] = relation[a] ^ relation[b] ^ parity[i];
            parent[fa] = fb;
        }
        result ++;
    }
    printf("%d\n", result);
    return 0;
}
