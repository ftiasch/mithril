#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

const int N = 50000;
const int M = N * 40 + 1;

int n;
char buffer[40 + 1];

int trie_size, depth[M];
int children[M], next[M];
short data[M];
bool end[M];
long long cost[41], minimum[M];

int counter;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

void print(int i, int u, bool f) {
    if (minimum[u] == cost[depth[u]]) {
        counter ++;
        buffer[i] = '\0';
        if (f) {
            printf("%s\n", buffer);
        }
    } else {
        for (int iter = children[u]; iter != -1; iter = next[iter]) {
            buffer[i] = 'a' + data[iter];
            print(i + 1, iter, f);
        }
    }
}

int main() {
    freopen("compression.in", "r", stdin);
    freopen("compression.out", "w", stdout);
    scanf("%d", &n);
    trie_size = 1;
    depth[0] = 0;
    memset(end, 0, sizeof(end));
    memset(children, -1, sizeof(children));
    for (int i = 0; i < n; ++ i) {
        scanf("%s", buffer);
        int p = 0;
        for (int i = 0; buffer[i]; ++ i) {
            int token = buffer[i] - 'a';
            int found = -1;
            for (int iter = children[p]; iter != -1; iter = next[iter]) {
                if (data[iter] == token) {
                    found = iter;
                }
            }
            if (found == -1) {
                depth[found = trie_size] = depth[p] + 1;
                data[trie_size] = token;
                next[trie_size] = children[p];
                children[p] = trie_size ++;
            }
            p = found;
        }
        end[p] = true;
    }
    for (int i = 1; i <= 40; ++ i) {
        cost[i] = 1LL << 40 - i;
    }
    for (int i = trie_size - 1; i >= 0; -- i) {
        minimum[i] = 0;
        for (int iter = children[i]; iter != -1; iter = next[iter]) {
            minimum[i] += minimum[iter];
        }
        if (end[i] || cost[depth[i]] < minimum[i]) {
            minimum[i] = cost[depth[i]];
        }
    }
    long long answer = 0;
    for (int iter = children[0]; iter != -1; iter = next[iter]) {
        answer += minimum[iter];
    }
    cout << answer << endl;
    counter = 0;
    for (int iter = children[0]; iter != -1; iter = next[iter]) {
        buffer[0] = 'a' + data[iter];
        print(1, iter, false);
    }
    printf("%d\n", counter);
    for (int iter = children[0]; iter != -1; iter = next[iter]) {
        buffer[0] = 'a' + data[iter];
        print(1, iter, true);
    }
    return 0;
}
