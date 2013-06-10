#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn = 50005;

struct node
{
    int left, right;
    int key, aux;
    int height;
}tree[maxn];
int node = 0;
int x[maxn], y[maxn];

inline void renew(int root)
{
    tree[root].height = max(tree[tree[root].left].height, tree[tree[root].right].height) + 1;
}

inline void leftRotate(int &root)
{
    int t = tree[root].left;
    tree[root].left = tree[t].right;
    tree[t].right = root;
    renew(root);
    renew(t);
    root = t;
}

inline void rightRotate(int &root)
{
    int t = tree[root].right;
    tree[root].right = tree[t].left;
    tree[t].left = root;
    renew(root);
    renew(t);
    root = t;
}

inline void insert(int &root, int key, int aux)
{
    if (root == 0) {
        root = ++ node;
        tree[root].key = key;
        tree[root].aux = aux;
        tree[root].left = tree[root].right = 0;
        tree[root].height = 0;
        return;
    }
    if (key < tree[root].key) {
        insert(tree[root].left, key, aux);
        if (tree[tree[root].left].aux >= tree[root].aux) {
            leftRotate(root);
        }
    } else {
        insert(tree[root].right, key, aux);
        if (tree[tree[root].right].aux >= tree[root].aux) {
            rightRotate(root);
        }
    }
    renew(root);
}

int main()
{
    int n;
    scanf("%d", &n);
    int root = 0;
    tree[root].left = tree[root].right = 0;
    tree[root].aux = -1;
    tree[root].height = -1;
    
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &x[i]);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &y[i]);
    }
    for (int i = 0; i < n; ++ i) {
        insert(root, x[i], y[i]);
        if (i) {
            printf(" ");
        }
        printf("%d", tree[root].height);
    }
    puts("");
    
    return 0;
}

