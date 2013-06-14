#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

struct Node;

typedef std::pair <Node*, Node*> Pair;

struct Data {
    int open, close, pair;

    Data() {}
    Data(int open, int close, int pair) : open(open), close(close), pair(pair) {} 
};

Data merge(const Data &a, const Data &b) {
    int tmp = std::min(a.open, b.close);
    return Data(a.open + b.open - tmp, a.close + b.close - tmp, a.pair + b.pair + tmp);
}

struct Node {
    Data data, key;
    int type, count, size, total;
    Node *left, *right;

    Node(int, int);

    Node* update() {
        size = left->size + 1 + right->size;
        total = left->total + count + right->total;
        data = merge(merge(left->data, key), right->data);
        return this;
    }

    Pair split(int);

    void print_node() {
        printf("<%d, %d, %d, %d, %d>", type, count, data.open, data.close, data.pair);
    }

    void print();
};

std::vector <Node*> nodes;

bool random(int a, int b) {
    return rand() % (a + b) < a;
}

Node *null;

Node::Node(int type, int count) : key((type == 0 ? count : 0), (type == 1 ? count : 0), 0), type(type), count(count), size(1), total(count), left(null), right(null) {
    data = key;
    nodes.push_back(this);
}

void Node::print() {
    if (this != null) {
        putchar('[');
        left->print();
        print_node();
        right->print();
        putchar(']');
    }
}

Node* merge(Node *p, Node *q) {
    if (p == null) {
        return q;
    }
    if (q == null) {
        return p;
    }
    if (random(p->size, q->size)) {
        p->right = merge(p->right, q);
        return p->update();
    }
    q->left = merge(p, q->left);
    return q->update();
}

Pair Node::split(int n) {
    if (this == null) {
        return std::make_pair(null, null);
    }
    if (n <= left->total) {
        Pair ret = left->split(n);
        left = null;
        return std::make_pair(ret.first, merge(ret.second, this->update()));
    }
    if (n >= left->total + count) {
        Pair ret = right->split(n - left->total - count);
        right = null;
        return std::make_pair(merge(this->update(), ret.first), ret.second);
    }
    int x = n - left->total;
    return std::make_pair(merge(left, new Node(type, x)), merge(new Node(type, count - x), right));
}

int main() {
    null = new Node(0, 0);
    null->data.open = null->data.close = null->data.pair = 0;
    null->size = null->total = 0;
    null->left = null->right = null;
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        printf("Case %d:\n", t);
        int n;
        scanf("%d", &n);
        Node *root = new Node(0, 1);
        while (n --) {
            int type, where, count;
            scanf("%d%d%d", &type, &where, &count);
            Pair ret = root->split(where);
            root = merge(ret.first, merge(new Node(type, count), ret.second));
//root->print(); puts("");
            printf("%d\n", root->data.pair);
        }
        foreach (iter, nodes) {
            if (*iter != null) {
                delete *iter;
            }
        }
        nodes.resize(1);
    }
    return 0;
}
// Case 1:
// [[<0, 1, 1, 0, 0>]<1, 4, 0, 3, 1>]
// 1
// [[[<0, 1, 0, 1, 1>[<1, 2, 0, 2, 0>]]<0, 3, 3, 1, 1>]<1, 2, 1, 1, 3>]
// 3
// [<0, 2, 2, 0, 0>]
// 0
// Case 2:
// [<1, 1, 0, 1, 0>]
// 0
