#include <cstdio>
#include <cstring>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

using std::vector;

struct Node {
    long long delta;
    Node *left, *right;

    Node(long long delta, Node *left, Node *right) : delta(delta), left(left), right(right) {}

    Node* cover(int, int, int, int, int);
    long long query(int, int, int);
};

const int N = 300000 + 1;

int n, m, q, limit[N];
vector <int> positions[N];

Node* null;
Node* trees[N];

Node* Node::cover(int l, int r, int a, int b, int c) {
    if (b < l || r < a) {
        return this;
    }
    if (a <= l && r <= b) {
        return new Node(delta + c, left, right);
    }
    int m = l + r >> 1;
    return new Node(delta, left->cover(l, m, a, b, c), right->cover(m + 1, r, a, b, c));
}

long long Node::query(int l, int r, int k) {
    if (l == r) {
        return delta;
    }
    int m = l + r >> 1;
    return (k <= m ? left->query(l, m, k) : right->query(m + 1, r, k)) + delta;
}

int main() {
    null = new Node(0, NULL, NULL);
    null->left = null->right = null;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int owner;
        scanf("%d", &owner);
        positions[owner].push_back(i);
    }
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", limit + i);
    }
    scanf("%d", &q);
    trees[0] = null;
    for (int i = 1; i <= q; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        Node* now = trees[i - 1];
        if (a <= b) {
            now = now->cover(1, m, a, b, c);
        } else {
            now = now->cover(1, m, a, m, c);
            now = now->cover(1, m, 1, b, c);
        }
        trees[i] = now;
    }
    for (int i = 1; i <= n; ++ i) {
        int low = 1;
        int high = q + 1;
        while (low < high) {
            int middle = low + high >> 1;
            long long count = 0;
            foreach (iter, positions[i]) {
                count += trees[middle]->query(1, m, *iter);
                if (count >= limit[i]) {
                    break;
                }
            }
            if (count >= limit[i]) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }
        if (high > q) {
            puts("NIE");
        } else {
            printf("%d\n", high);
        }
    }
    return 0;
}
