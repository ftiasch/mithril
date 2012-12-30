#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <algorithm>

using std::pair;
using std::make_pair;

bool generator(double p) {
    double x = (double)rand() / RAND_MAX;
    return x < p;
}

struct Node {
    int value, size;
    Node *left, *right;

    Node(int value, int size, Node *left, Node *right) : value(value), size(size), left(left), right(right) {}

    void update() {
        size = left->size + 1 + right->size;
    }
};

Node *null;

Node* merge(Node *a, Node *b) {
    assert(a != null || b != null);
    if (a == null) {
        return b;
    }
    if (b == null) {
        return a;
    }
    if (generator((double)a->size / (a->size + b->size))) {
        a->right = merge(a->right, b);
        a->update();
        return a;
    } else {
        b->left = merge(a, b->left);
        b->update();
        return b;
    }
}

typedef pair <Node*, Node*> Pair;

Pair split(Node *u, int s) {
    if (u == null) {
        return make_pair(null, null);
    }
    Node *l = u->left;
    Node *r = u->right;
    u->left = u->right = null;
    u->update();
    if (l->size >= s) {
        Pair ret = split(l, s);
        return make_pair(ret.first, merge(merge(ret.second, u), r));
    } else {
        Pair ret = split(r, s - (l->size + 1));
        return make_pair(merge(l, merge(u, ret.first)), ret.second);
    }
}

int n, m;

void print(Node *u) {
    if (u != null) {
        print(u->left);
        printf("%d ", u->value);
        print(u->right);
    }
}

int main() {
    null = new Node(0, 0, NULL, NULL);
    null->left = null->right = null;
    Node *root = null;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        root = merge(root, new Node(i, 1, null, null));
    }
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a > 1) {
            Pair latter = split(root, b);
            Pair former = split(latter.first, a - 1);
            root = merge(former.second, merge(former.first, latter.second));
        }
    }
    print(root);
    puts("");
    return 0;
}
