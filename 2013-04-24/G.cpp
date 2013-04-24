#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <deque>
#include <iostream>
#include <algorithm>

const int N = 300000 + 1;

int n, m, count[N], rank[N], array[N], new_rank[N][2], new_array[N], height[N];
char buffer[N], string[N];

void construct(char* string, int n) {
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; ++ i) {
        count[(int)string[i]] ++;
    }
    for (int i = 0; i < 256; ++ i) {
        count[i + 1] += count[i];
    }
    for (int i = 0; i < n; ++ i) {
        rank[i] = count[(int)string[i]] - 1;
    }
    for (int length = 1; length < n; length <<= 1) {
        for (int i = 0; i < n; ++ i) {
            new_rank[i][0] = rank[i];
            new_rank[i][1] = i + length < n ? rank[i + length] + 1 : 0;
        }
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++ i) {
            count[new_rank[i][1]] ++;
        }
        for (int i = 0; i < n; ++ i) {
            count[i + 1] += count[i];
        }
        for (int i = n - 1; i >= 0; -- i) {
            new_array[-- count[new_rank[i][1]]] = i;
        }
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++ i) {
            count[new_rank[i][0]] ++;
        }
        for (int i = 0; i < n; ++ i) {
            count[i + 1] += count[i];
        }
        for (int i = n - 1; i >= 0; -- i) {
            array[-- count[new_rank[new_array[i]][0]]] = new_array[i];
        }
        rank[array[0]] = 0;
        for (int i = 0; i + 1 < n; ++ i) {
            rank[array[i + 1]] = rank[array[i]] + (new_rank[array[i]][0] != new_rank[array[i + 1]][0] || new_rank[array[i]][1] != new_rank[array[i + 1]][1]);
        }
    }
    for (int i = 0, length = 0; i < n; ++ i) {
        if (rank[i]) {
            int j = array[rank[i] - 1];
            while (i + length < n && j + length < n && string[i + length] == string[j + length]) {
                length ++;
            }
            height[rank[i]] = length;
            if (length) {
                length --;
            }
        }
    }
}

int rmq[N << 2];

void build(int t, int l, int r) {
    if (l + 1 == r) {
        rmq[t] = height[r];
    } else {
        int m = l + r >> 1;
        build(t * 2, l, m);
        build(t * 2 + 1, m, r);
        rmq[t] = std::min(rmq[t * 2], rmq[t * 2 + 1]);
    }
}


int query(int t, int l, int r, int a, int b) {
    if (b <= l || r <= a) {
        return INT_MAX;
    }
    if (a <= l && r <= b) {
        return rmq[t];
    }

    int m = l + r >> 1;
    return std::min(query(t * 2, l, m, a, b), query(t * 2 + 1, m, r, a, b));
}

int lcp(int i, int j) {
    if (i != j) {
        i = rank[i];
        j = rank[j];
        if (i > j) {
            std::swap(i, j);
        }
        return query(1, 0, n + m, i, j);
    }
    assert(false);
}

int maximum[N];

int main() {
    scanf("%s%s", string, buffer);
    n = strlen(string);
    m = strlen(buffer);
    string[n] = '0';
    for (int i = 0; i < m; ++ i) {
        string[n + 1 + i] = buffer[i];
    }
    construct(string, n + m + 1);
    build(1, 0, n + m);
    memset(maximum, 0, sizeof(maximum));
    for (int i = 0, last = -1; i < n + m + 1; ++ i) {
        if (array[i] < n) {
            last = i;
        }
        if (last != -1 && array[i] > n) {
            maximum[array[i] - n - 1] = std::max(maximum[array[i] - n - 1], lcp(array[last], array[i]));
        }
    }
    for (int i = n + m, last = -1; i >= 0; -- i) {
        if (array[i] < n) {
            last = i;
        }
        if (last != -1 && array[i] > n) {
            maximum[array[i] - n - 1] = std::max(maximum[array[i] - n - 1], lcp(array[last], array[i]));
        }
    }
    long long answer = 0;
    for (int i = 0; i < n + m + 1; ++ i) {
        answer += maximum[i];
    }
    std::cout << answer << std::endl;
    return 0;
}
