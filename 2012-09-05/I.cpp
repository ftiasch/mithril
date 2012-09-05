#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

struct Node {
    int delta;
    LL sum;
    Node *left, *right;

    Node* cover(int, int, int, int, int);

    LL query(int l, int r, int a, int b) {
        if (b <= l || r <= a) {
            return 0;
        }
        if (a <= l && r <= b) {
            return sum;
        }
        int m = (l + r) >> 1;
        return left->query(l, m, a, b) + right->query(m, r, a, b) + (LL)delta * (min(b, r) - max(l, a));
    }
};

const int N = 100000;
const int T = 4000000;

int nodeCount;
Node nodes[T];

Node* newNode(LL delta, LL sum, Node* left, Node* right) {
    assert(nodeCount < T);
    nodes[nodeCount].delta = delta;
    nodes[nodeCount].sum = sum;
    nodes[nodeCount].left = left;
    nodes[nodeCount].right = right;
    return &nodes[nodeCount ++];
}

Node* Node::cover(int l, int r, int a, int b, int d) {
    if (b <= l || r <= a) {
        return this;
    }
    if (a <= l && r <= b) {
        return newNode(delta + d,
                       sum + (LL)d * (r - l),
                       left, right);
    }
    int m = (l + r) >> 1;
    Node* newLeft = left->cover(l, m, a, b, d);
    Node* newRight = right->cover(m, r, a, b, d);
    return newNode(delta, 
                   newLeft->sum + newRight->sum + (LL)delta * (r - l), 
                   newLeft, newRight);
}

int n, m, a[N];

Node* build(int l, int r) {
    if (l + 1 == r) {
        return newNode(0, a[l], NULL, NULL);
    }
    int m = (l + r) >> 1;
    Node* newLeft = build(l, m);
    Node* newRight = build(m, r);
    return newNode(0, newLeft->sum + newRight->sum, newLeft, newRight);
}

Node* trees[N + 1];

int main() {
    //int testCount = 0;
    while (scanf("%d%d", &n, &m) == 2) {
        //testCount ++;
        //if (testCount > 1) {
        //}
        nodeCount = 0;
        for (int i = 0; i < n; ++ i) {
            scanf("%d", a + i);
        }
        int current = 0;
        trees[0] = build(0, n);
        for (int i = 0; i < m; ++ i) {
            char buffer[2];
            scanf("%s", buffer);
            if (*buffer == 'B') {
                int newTime;
                scanf("%d", &newTime);
                current = newTime;
            } else {
                int l, r;
                scanf("%d%d", &l, &r);
                l --;
                if (*buffer == 'Q') {
                    cout << trees[current]->query(0, n, l, r) << endl;
                } else {
                    int x;
                    scanf("%d", &x);
                    if (*buffer == 'H') {
                        cout << trees[x]->query(0, n, l, r) << endl;
                    } else {
                        trees[current + 1] = trees[current]->cover(0, n, l, r, x);
                        current ++;
                    }
                }
            }
        }
        //puts("");
    }
    return 0;
}
