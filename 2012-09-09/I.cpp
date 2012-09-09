#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#pragma comment(linker, "/STACK:10000000")

const int N = 1000000 + 5;

short type[N];
int nodeCount, parent[N], children[N][2], size[N], stack[N], key[N];
bool reversed[N];

void update(int x) {
    size[x] = size[children[x][0]] + 1 + size[children[x][1]];
}

void push(int x) {
    if (reversed[x]) {
        reversed[x] = 0;
        swap(children[x][0], children[x][1]);
        for (int k = 0; k < 2; ++ k) {
            type[children[x][k]] = k;
            reversed[children[x][k]] ^= 1;
        }
    }
}

void rotate(int x) {
    int t = type[x];
    int y = parent[x];
    int z = children[x][1 ^ t];
    type[x] = type[y];
    parent[x] = parent[y];
    if (type[x] != 2) {
        children[parent[x]][type[x]] = x;
    }
    type[y] = 1 ^ t;
    parent[y] = x;
    children[x][1 ^ t] = y;
    if (z != 0) {
        type[z] = t;
        parent[z] = y;
    }
    children[y][t] = z;
    update(y);
}

void splay(int x) {
    int stackSize = 0;
    stack[stackSize ++] = x;
    for (int i = x; type[i] != 2; i = parent[i]) {
        stack[stackSize ++] = parent[i];
    }
    for (int i = stackSize - 1; i >= 0; -- i) {
        push(stack[i]);
    }
    while (type[x] != 2) {
        int y = parent[x];
        if (type[x] == type[y]) {
            rotate(y);
        } else {
            rotate(x);
        }
        if (type[x] == 2) {
            break;
        }
        rotate(x);
    }
    update(x);
}

int findByRank(int x, int rank) { // 1-based
    while (true) {
        push(x);
        if (size[children[x][0]] + 1 == rank) {
            break;
        }
        if (rank <= size[children[x][0]]) {
            x = children[x][0];
        } else {
            rank -= size[children[x][0]] + 1;
            x = children[x][1];
        }
    }
    splay(x);
    return x;
}

void clear(int x) {
    type[x] = 2;
    reversed[x] = false;
    parent[x] = children[x][0] = children[x][1] = 0;
    update(x);
}

void split(int &x, int &y, int a) {
    if (a == 0) {
        y = x, x = 0;
        return;
    } else if (a == size[x]) {
        y = 0;
        return;
    }
    y = findByRank(x, a + 1);
    splay(y);
    x = children[y][0];
    type[x] = 2;
    children[y][0] = 0;
    update(y);
}

int join(int x, int y) {
    if (x == 0 || y == 0) {
        return x | y;
    }
    x = findByRank(x, size[x]);
    children[x][1] = y;
    type[y] = 1;
    parent[y] = x;
    update(x);
    return x;
}

char command[22];

bool first;

void printTree(int x) {
    if (x != 0) {
        push(x);
        printTree(children[x][0]);
        if (first) {
            first = false;
        } else {
            putchar(' ');
        }
        printf("%d", key[x]);
        printTree(children[x][1]);
    }
}

int main() {
    size[0] = 0;
    int testCount;
    scanf("%d", &testCount);
    while (testCount > 0) {
        testCount --;
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++ i) {
            clear(i);
            scanf("%d", key + i);
        }
        int leftPointer, rightPointer;
        scanf("%d%d", &leftPointer, &rightPointer);
        int leftRoot = 0;
        int root = 0;
        int rightRoot = 0;
        for (int i = 1; i < leftPointer; ++ i) {
            leftRoot = join(leftRoot, i);
        }
        for (int i = leftPointer; i <= rightPointer; ++ i) {
            root = join(root, i);
        }
        for (int i = rightPointer + 1; i <= n; ++ i) {
            rightRoot = join(rightRoot, i);
        }
        nodeCount = n + 1;
        int operationCount;
        scanf("%d", &operationCount);
        int tmpRoot;
        while (operationCount > 0) {
            operationCount --;
            scanf("%s", command);
            if (strcmp(command, "MoveLeft") == 0) {
                scanf("%s", command);
                if (*command == 'L') {
                    split(leftRoot, tmpRoot, size[leftRoot] - 1);
                    root = join(tmpRoot, root);
                } else { 
                    split(root, tmpRoot, size[root] - 1);
                    rightRoot = join(tmpRoot, rightRoot);
                }
            } else if (strcmp(command, "MoveRight") == 0) {
                scanf("%s", command);
                if (*command == 'L') {
                    split(root, tmpRoot, 1);
                    swap(root, tmpRoot);
                    leftRoot = join(leftRoot, tmpRoot);
                } else {
                    split(rightRoot, tmpRoot, 1);
                    swap(rightRoot, tmpRoot);
                    root = join(root, tmpRoot);
                }
            } else if (strcmp(command, "Reverse") == 0) {
                reversed[root] ^= 1;
            } else {
                if (strcmp(command, "Insert") == 0) {
                    scanf("%s", command);
                    clear(nodeCount);
                    scanf("%d", key + nodeCount);
                    if (*command == 'L') {
                        root = join(nodeCount, root);
                    } else {
                        root = join(root, nodeCount);
                    }
                    nodeCount ++;
                } else if (strcmp(command, "Delete") == 0) {
                    scanf("%s", command);
                    if (*command == 'L') {
                        split(root, tmpRoot, 1);
                        root = tmpRoot;
                    } else {
                        split(root, tmpRoot, size[root] - 1);
                    }
                }
            }
        }
        first = true;
        printTree(leftRoot);
        printTree(root);
        printTree(rightRoot);
        puts("");
    }
    return 0;
}
