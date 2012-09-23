#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100000 + 1;

int a[N];

int nodeCount;

struct Node {
    int count;
    Node *left, *right;
    
    Node* insert(int l, int r, int k);
    int query(int l, int r, int k);
};

const int D = 20;

Node pool[N * D];
Node* null;

Node* newNode(int count, Node *left, Node *right) {
    pool[nodeCount].count = count;
    pool[nodeCount].left = left;
    pool[nodeCount].right = right;
    return &pool[nodeCount ++];
}

vector <int> values;

Node* Node::insert(int l, int r, int k) {
//printf("%d, %d\n", l, r);
    if (k < values[l] || values[r] < k) {
        return this;
    }
    if (l == r) {
        return newNode(count + 1, null, null);
    }
    int m = (l + r) >> 1;
    return newNode(count + 1,
                   left->insert(l, m, k),
                   right->insert(m + 1, r, k));
}

int Node::query(int l, int r, int k) {
    if (k < values[l]) {
        return 0;
    }
    if (values[r] <= k) {
        return count;
    }
    int m = (l + r) >> 1;
    return left->query(l, m, k) + right->query(m + 1, r, k);
}

Node* tree[N];

int main() {
    null = &pool[0];
    null->count = 0;
    null->left = null->right = null;
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        printf("Case %d:\n", t);
        int n, m;
        scanf("%d%d", &n, &m);
        values.clear();
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", a + i);
            values.push_back(a[i]);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        nodeCount = 1;
        tree[0] = null;
        int max = (int)values.size() - 1;
        for (int i = 1; i <= n; ++ i) {
            tree[i] = tree[i - 1]->insert(0, max, a[i]);
        }
        while (m --) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            printf("%d\n", tree[b + 1]->query(0, max, c)
                         - tree[a]->query(0, max, c));
        }
    }
    return 0;
}
