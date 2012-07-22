#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 20;
const int C = 26 + N;
const int M = 100000 + N;


struct State {
    int length, mask;
    long long ways;
    State *parent;
    State *go[C];

    State(int length): length(length), mask(-1), parent(NULL) {
        memset(go, 0, sizeof(go));
    }

    State* extend(State *start, int token) {
        State *p = this;
        State *np = new State(this->length + 1);
        while (p != NULL && p->go[token] == NULL) {
            p->go[token] = np;
            p = p->parent;
        }
        if (p == NULL) {
            np->parent = start;
        } else {
            State *q = p->go[token];
            if (p->length + 1 == q->length) {
                np->parent = q;
            } else {
                State *nq = new State(p->length + 1);
                memcpy(nq->go, q->go, sizeof(q->go));
                nq->parent = q->parent;
                np->parent = q->parent = nq;
                while (p != NULL && p->go[token] == q) {
                    p->go[token] = nq;
                    p = p->parent;
                }
            }
        }
        return np;
    }
};

int n, m, text[M];
char buffer[M];

void dfs(State *p) {
    if (p->mask == -1) {
        p->mask = p->ways = 0;
        for (int token = 0; token < C; ++ token) {
            if (p->go[token] != NULL) {
                if (token >= 26) {
                    p->mask |= 1 << (token - 26);
                } else {
                    dfs(p->go[token]);
                    p->mask |= p->go[token]->mask;
                    p->ways += p->go[token]->ways;
                }
            }
        }
        p->ways ++;
        if (p->mask != (1 << n) - 1) {
            p->ways = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    m = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%s", buffer);
        int length = strlen(buffer);
        for (int j = 0; j < length; ++ j) {
            text[m ++] = buffer[j] - 'a';
        }
        text[m ++] = 26 + i;
    }
    State *start = new State(0);
    State *current = start;
    for (int i = 0; i < m; ++ i) {
        current = current->extend(start, text[i]);
    }
    dfs(start);
    int queryCount;
    scanf("%d", &queryCount);
    while (queryCount > 0) {
        queryCount --;
        long long rank;
        cin >> rank;
        rank ++;
        State *p = start;
        while (rank > 1) {
            rank --;
            for (int token = 0; token < 26; ++ token) {
                if (p->go[token] != NULL) {
                    if (p->go[token]->ways >= rank) {
                        putchar('a' + token);
                        p = p->go[token];
                        break;
                    } else {
                        rank -= p->go[token]->ways;
                    }
                }
            }
        }
        puts("");
    }
    return 0;
}
