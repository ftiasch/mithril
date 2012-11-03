#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 100000 + 1;

int nodeCount, key[N], length[N], weight[N], children[N][2], delta[N];

void add(int x, int d) {
    if (x) {
        key[x] += d;
        delta[x] += d;
    }
}

void pushDown(int &x) {
    if (delta[x] != 0) {
        add(children[x][0], delta[x]);
        add(children[x][1], delta[x]);
        delta[x] = 0;
    }
}

void rotate(int &x, int t) {
    int y = children[x][t];
    pushDown(y);
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    x = y;
}

void insert(int &x, int k, int k2) {
    if (x) {
        pushDown(x);
        int t = key[x] < k;
        insert(children[x][t], k, k2);
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    } else {
        x = nodeCount ++;
        key[x] = k;
        length[x] = k2;
        weight[x] = rand();
        delta[x] = 0;
        children[x][0] = children[x][1] = 0;
    }
}

void erase(int &x, int k, int v) {
    if (!x) {
        return;
    }
    pushDown(x);
    if (key[x] != k) {
        erase(children[x][key[x] < k], k, v);
    } else if (length[x] > v) {
        length[x] -= v;
        return;
    } else {
        if (!children[x][0] && !children[x][1]) {
            x = 0;
        } else {
            rotate(x, weight[children[x][0]] > weight[children[x][1]]);
            erase(x, k, v);
        }
    }
}

void cover(int &x, int k, int v) { // increase >= k by v
    if (!x) {
        return;
    }
    pushDown(x);
    if (key[x] < k) {
        cover(children[x][1], k, v);
    } else {
        key[x] += v;
        add(children[x][1], v);
        cover(children[x][0], k, v);
    }
}

const int INF = 1000000000;

pair <int, int> upperBound(int &x, int k) { // max <= k
    if (!x) {
        return make_pair(-INF, 0);
    }
    pushDown(x);
    if (key[x] <= k) {
        return max(upperBound(children[x][1], k), make_pair(key[x], length[x]));
    }
    return upperBound(children[x][0], k);
}

int tree[26];

void print(int &x, int d) {
    if (x) {
        print(children[x][0], d + delta[x]);
        printf("(%d, %d), ", key[x] + d, length[x]);
        print(children[x][1], d + delta[x]);
    }
}

int main() {
    freopen("log.in","r",stdin);
    freopen("log.out","w",stdout);

    weight[0] = INT_MAX;
    nodeCount = 1;
    memset(tree, 0, sizeof(tree));
    int q;
    scanf("%d", &q);
    while (q --) {
//printf("op %d\n", q);
        char op[2];
        scanf("%s", op);
        if (*op == '+') {
            int start, count;
            scanf("%d%d%s", &start, &count, op);
            int i = 0;
            pair <int, int> ret;
            while (i < 26) {
                ret = upperBound(tree[i], start - 1);
                if (ret.first + ret.second - 1 >= start) {
                    break;
                }
                i ++;
            }
            if (i < 26) {
                int d = ret.first + ret.second - start;
                int d2 = ret.second - d;
//printf("%d, %d\n", d, d2);
                erase(tree[i], ret.first, d);
                insert(tree[i], ret.first + d2, d);
            }
            for (int i = 0; i < 26; ++ i) {
                cover(tree[i], start, count);
            }
            insert(tree[*op - 'a'], start, count);
        } else if (*op == '-') {
            int start, count;
            scanf("%d%d", &start, &count);
            while (count) {
                int i = 0;
                pair <int, int> ret;
                while (i < 26) {
                    ret = upperBound(tree[i], start);
                    if (ret.first + ret.second - 1 >= start) {
                        break;
                    }
                    i ++;
                }
                int d = min(count, ret.first + ret.second - start);
                count -= d;
                erase(tree[i], ret.first, d);
                for (int i = 0; i < 26; ++ i) {
                    cover(tree[i], start+1, -d);
                }
            }
        } else {
            int from, to;
            scanf("%d%d", &from, &to);
            int result = 0;
            for (int i = 0; i < 26; ++ i) {
                pair <int, int> ret = upperBound(tree[i], to);
                if (ret.first + ret.second - 1 >= from) {
                    result ++;
                }
            }
            printf("%d\n", result);
        }
/*for (int i = 0; i < 3; ++ i) {
    print(tree[i], 0);
    puts("");
}*/
    }
    return 0;
}
