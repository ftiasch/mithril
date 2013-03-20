#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

const int N = 450000;

int n, a[N];

struct Node {
    int count;
    Node *left, *right;
    
    Node(int count, Node *left, Node *right): count(count), left(left), right(right) {
    }

    Node* insert(int l, int r, int k);
};

Node *null;
Node* trees[N + 1];

int query(Node *begin, Node *end, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int m = l + r >> 1;
    int size = begin->right->count - end->right->count;
    if (size >= k) {
        return query(begin->right, end->right, m + 1, r, k);
    }
    return query(begin->left, end->left, l, m, k - size);
}

Node* Node::insert(int l, int r, int k) {
    if (k < l || r < k) {
        return this;
    }
    if (l == r) {
        return new Node(count + 1, null, null);
    }
    int m = l + r >> 1;
    return new Node(count + 1, left->insert(l, m, k), right->insert(m + 1, r, k));
}

int main() {
    null = new Node(0, NULL, NULL);
    null->left = null->right = null;
    scanf("%d", &n);
    {
        int l, m;
        scanf("%d%d%d", a, &l, &m);
        for (int i = 1; i < n; ++ i) {
            a[i] = ((long long)a[i - 1] * l + m) % 1000000000;
        }
    }
    std::vector <int> values;
    for (int i = 0; i < n; ++ i) {
        values.push_back(a[i]);
    }
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());
    for (int i = 0; i < n; ++ i) {
        a[i] = std::lower_bound(values.begin(), values.end(), a[i]) - values.begin();
    }
    trees[n] = null;
    for (int i = n - 1; i >= 0; -- i) {
        trees[i] = trees[i + 1]->insert(0, (int)values.size() - 1, a[i]);
    }
    long long answer = 0;
    {
        int b;
        scanf("%d", &b);
        while (b --> 0) {
            int g, x_1, l_x, m_x, y_1, l_y, m_y, k_1, l_k, m_k, i_1, j_1;
            scanf("%d%d%d%d%d%d%d%d%d%d", &g, &x_1, &l_x, &m_x, &y_1, &l_y, &m_y, &k_1, &l_k, &m_k);
            i_1 = std::min(x_1, y_1);
            j_1 = std::max(x_1, y_1);
            for (int i = 1; i <= g; ++ i) {
                answer += values[query(trees[i_1 - 1], trees[j_1], 0, (int)values.size() - 1, (j_1 - i_1 + 1) + 1 - k_1)];
                x_1 = ((long long)(i_1 - 1) * l_x + m_x) % n + 1;
                y_1 = ((long long)(j_1 - 1) * l_y + m_y) % n + 1;
                i_1 = std::min(x_1, y_1);
                j_1 = std::max(x_1, y_1);
                k_1 = ((long long)(k_1 - 1) * l_k + m_k) % (j_1 - i_1 + 1) + 1;
            }
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
