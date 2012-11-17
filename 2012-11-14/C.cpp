#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 600000 + 1;

int nodeCount, key[N], weight[N], counter[N], size[N], children[N][2];

void update(int &x) {
    size[x] = size[children[x][0]] + counter[x] + size[children[x][1]];
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, int k) {
    if (!x) {
        x = nodeCount ++;
        key[x] = k;
        weight[x] = rand();
        counter[x] = 1;
        children[x][0] = children[x][1] = 0;
    } else if (key[x] == k) {
        counter[x] ++;
    } else {
        int t = key[x] < k;
        insert(children[x][t], k);
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    }
    update(x);
}

void erase(int &x, int k) {
    if (key[x] == k) {
        if (counter[x] == 1) {
            if (!children[x][0] && !children[x][1]) {
                x = 0;
                return;
            }
            rotate(x, weight[children[x][0]] > weight[children[x][1]]);
            erase(x, k);
        } else {
            counter[x] --;
        }
    } else {
        erase(children[x][key[x] < k], k);
    }
    update(x);
}

int select(int &x, int k) {
    if (k <= size[children[x][0]]) {
        return select(children[x][0], k);
    }
    int ret = size[children[x][0]] + counter[x];
    if (k <= ret) {
        return key[x];
    }
    return select(children[x][1], k - ret);
}

char buffer[22];

int main() {
    size[0] = 0;
    weight[0] = INT_MAX;
    nodeCount = 1;
    int root = 0;
    while (scanf("%s", buffer) == 1) {
        if (*buffer == '#') {
            int c = size[root];
            int r = (c & 1) ? ((c + 1) >> 1) : ((c >> 1) + 1);
            int ret = select(root, r);
            erase(root, ret);
            printf("%d\n", ret);
        } else {
            int x;
            sscanf(buffer, "%d", &x);
            insert(root, x);
        }
    }
    return 0;
}
