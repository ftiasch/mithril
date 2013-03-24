#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

const long long INF = 1000000000000000000LL;

using std::make_pair;

struct Node;

typedef std::pair <Node*, Node*> Pair;

struct Node {
    int size;
    long long value, sum, minimum, maximum;

    bool reversed;
    long long cover;

    Node *left, *right;

    Node(int);

    Pair split(int);

    Node* add(int delta) {
        cover += delta;
        value += delta;
        minimum += delta;
        maximum += delta;
        sum += (long long)size * delta;
        return this;
    }

    Node* push_down() {
        if (reversed) {
            left->reversed ^= 1;
            right->reversed ^= 1;
            std::swap(left, right);
            reversed = false;
        }
        if (cover != 0) {
            left->add(cover);
            right->add(cover);
            cover = 0;
        }
        return this;
    }

    Node* update() {
        assert(cover == 0);
        size = left->size + 1 + right->size;
        sum = left->sum + value + right->sum;
        minimum = std::min(std::min(left->minimum, right->minimum), value);
        maximum = std::max(std::max(left->maximum, right->maximum), value);
        return this;
    }
};

bool random(int a, int b) {
    return (double)rand() / RAND_MAX < (double)a / (a + b);
}

Node* null;

Node::Node(int value) : size(1), value(value), sum(value), minimum(value), maximum(value), reversed(false), cover(0), left(null), right(null) {}

Node* merge(Node *p, Node *q) {
    if (p == null) {
        return q;
    }
    if (q == null) {
        return p;
    }
    if (random(p->size, q->size)) {
        p->push_down();
        p->right = merge(p->right, q);
        return p->update();
    }
    q->push_down();
    q->left = merge(p, q->left);
    return q->update();
}

Pair Node::split(int need) {
    if (this == null) {
        return make_pair(null, null);
    }
    push_down();
    if (left->size >= need) {
        Pair ret = left->split(need);
        left = null;
        update();
        return make_pair(ret.first, merge(ret.second, this));
    }
    Pair ret = right->split(need - (left->size + 1));
    right = null;
    update();
    return make_pair(merge(this, ret.first), ret.second);
}

int n;

int main() {
    null = new Node(0);
    null->size = 0;
    null->minimum = INF;
    null->maximum = -INF;

    Node* root = null;
    scanf("%d", &n);
    for (int i = 0, a; i < n; ++ i) {
        scanf("%d", &a);
        root = merge(root, new Node(a));
    }
    int m;
    scanf("%d", &m);
    while (m --) {
        char buffer[8];
        int i, j;
        scanf("%s%d%d", buffer, &i, &j);
        Pair p = root->split(i - 1);
        Pair q = p.second->split(j - i + 1);
        Node* r = q.first;
        if (*buffer == 'c') {
            int c;
            scanf("%d", &c);
            r->add(c);
        } else if (*buffer == 'r') {
            r->reversed ^= 1;
        } else {
            printf("%lld %lld %lld\n", r->sum, r->minimum, r->maximum);
        }
        root = merge(p.first, merge(r, q.second));
    }
    return 0;
}
