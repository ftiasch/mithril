#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <set>
#include <algorithm>

using std::make_pair;

const unsigned long long MAGIC = 0x2357abcdef;

const int N = 100000 << 1;

unsigned long long powers[N];

struct Node {
    int length, weight, size, maximum;
    bool color;
    unsigned long long hash;
    Node *left, *right;

    Node(int length, bool color, Node *left, Node *right) : length(length), weight(rand()), size(1), maximum(INT_MIN), color(color), hash((length << 1) | color), left(left), right(right) {}


    void update() {
        size = left->size + 1 + right->size;
        hash = left->hash + powers[left->size] * ((length << 1 | color) + MAGIC * right->hash);
        maximum = std::max(length, std::max(left->maximum, right->maximum));
    }

};

Node *null;

Node *merge(Node *a, Node *b) {
    if (a == null) {
        return b;
    }
    if (b == null) {
        return a;
    }
    if (a->weight < b->weight) {
        a->right = merge(a->right, b);
        a->update();
        return a;
    } else {
        b->left = merge(a, b->left);
        b->update();
        return b;
    }
}

typedef std::pair <Node*, Node*> Pair;

Pair split(Node *u, int n) {
    if (u == null) {
        return make_pair(null, null);
    }
    if (u->left->size >= n) {
        Node *l = u->left;
        u->left = null;
        u->update();
        Pair ret = split(l, n);
        return make_pair(ret.first, merge(ret.second, u));
    } else {
        Node *r = u->right;
        u->right = null;
        u->update();
        Pair ret = split(r, n - (u->left->size + 1));
        return make_pair(merge(u, ret.first), ret.second);
    }
}

int n, m;
char initial_color[6];

int find_rank(Node *u) {
    if (u->left->maximum == u->maximum) {
        return find_rank(u->left);
    }
    if (u->length == u->maximum) {
        return u->left->size + 1;
    }
    return u->left->size + 1 + find_rank(u->right);
}

void print(Node *u) {
    if (u != null) {
        print(u->left);
        printf("%c%d, ", u->color ? 'B' : 'W', u->length);
        print(u->right);
    }
}

int main() {
    null = new Node(0, 0, NULL, NULL);
    null->weight = INT_MAX;
    null->size = 0;
    null->left = null->right = null;
    powers[0] = 1;
    for (int i = 0; i + 1 < N; ++ i) {
        powers[i + 1] = powers[i] * MAGIC;
    }
    scanf("%d%d%s", &n, &m, initial_color);
    Node *root = null;
    for (int i = 0; i < n; ++ i) {
        int length;
        scanf("%d", &length);
        Node *u = new Node(length, (*initial_color == 'b') ^ (i & 1), null, null);
        u->update();
        root = merge(root, u);
    }
    std::set <unsigned long long> states;
    states.insert(root->hash);
    if (root->maximum == 1) {
        puts("0");
        return 0;
    }
    for (int i = 1; i <= m; ++ i) {
        int rank = find_rank(root);
        Pair ret = split(root, rank);
        Node* latter = ret.second;
        ret = split(ret.first, rank - 1);
        Node* former = ret.first;
        int now_length = ret.second->length;
        int now_color = ret.second->color;
        delete ret.second;
        int white = now_length >> 1;
        int black = now_length >> 1;
        if (now_length & 1) {
            if (now_color) {
                black ++;
            } else {
                white ++;
            }
        }
        while (former != null) {
            ret = split(former, former->size - 1);
            if (!ret.second->color) {
                white += ret.second->length;
                former = ret.first;
            } else {
                former = merge(ret.first, ret.second);
                break;
            }
        }
        while (latter != null) {
            ret = split(latter, 1);
            if (ret.first->color) {
                black += ret.first->length;
                latter = ret.second;
            } else {
                latter = merge(ret.first, ret.second);
                break;
            }
        }
        Node *u = new Node(white, 0, null, null);
        u->update();
        Node *v = new Node(black, 1, null, null);
        v->update();
        root = merge(merge(former, merge(u, v)), latter);
        if (root->maximum == 1 || states.find(root->hash) != states.end()) {
            printf("%d\n", i);
            return 0;
        }
        states.insert(root->hash);
    }
    printf("%d\n", m);
    return 0;
}
