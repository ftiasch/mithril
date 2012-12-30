#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using std::make_pair;

bool random(double p) {
    return (double)rand() / RAND_MAX < p;
}

struct Node;

typedef std::pair <Node*, Node*> Pair;

struct Node {
    int value, size;
    Node *left, *right;

    Node(int);
    Pair split(int);

    Node* update() {
        size = left->size + 1 + right->size;
        return this;
    }

    void print();
};

Node *null;

Node::Node(int value) : value(value), size(1), left(null), right(null) {}

void Node::print() {
    if (this != null) {
        left->print();
        printf("%d ", value);
        right->print();
    }
}

Node* merge(Node *p, Node *q) {
    if (p == null) {
        return q;
    }
    if (q == null) {
        return p;
    }
    if (random((double)p->size / (p->size + q->size))) {
        p->right = merge(p->right, q);
        return p->update();
    }
    q->left = merge(p, q->left);
    return q->update();
}

Pair Node::split(int need) {
    if (this == null) {
        return make_pair(null, null);
    }
    if (left->size >= need) {
        Pair ret = left->split(need);
        left = null;
        this->update();
        return make_pair(ret.first, merge(ret.second, this));
    }
    Pair ret = right->split(need - (left->size + 1));
    right = null;
    this->update();
    return make_pair(merge(this, ret.first), ret.second);
}

int main() {
    null = new Node(-1);
    null->size = 0;
    null->left = null->right = null;
    Node *root = null;
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        root = merge(root, new Node(i));
    }
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a > 1) {
            Pair latter = root->split(b);
            Pair former = latter.first->split(a - 1);
            root = merge(former.second, merge(former.first, latter.second));
        }
    }
    root->print();
    puts("");
    return 0;
}
