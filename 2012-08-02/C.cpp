#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;

ULL nextLong() {
    ULL result = 0;
    char c = getchar();
    while (!isdigit(c)) {
        c = getchar();
    }
    while (isdigit(c)) {
        result = result * 10 + c - '0';
        c = getchar();
    }
    return result;
}

const int N = 1000000 << 2;

int n, from[N][2];
short power[N];
bool pick[N];
ULL sum, weight[N];
vector <int> id[64];

bool compare(int i, int j) {
    return weight[i] < weight[j];
}

void mark(int i) {
    if (i != -1) {
        pick[i] = true;
        mark(from[i][0]);
        mark(from[i][1]);
    }
}

int main() {
    int oldN = n = nextLong();
    sum = nextLong();
    for (int i = 0; i < n; ++ i) {
        power[i] = nextLong();
        weight[i] = nextLong();
    }
    for (int i = 0; i < n; ++ i) {
        id[power[i]].push_back(i);
    }
    memset(pick, 0, sizeof(pick));
    memset(from, -1, sizeof(from));
    for (int b = 0; b < 64; ++ b) {
        if (b > 0) {
            int i = 0;
            while (i < (int)id[b - 1].size() && pick[id[b - 1][i]]) {
                i ++;
            }
            while (i + 1 < (int)id[b - 1].size()) {
                weight[n] = weight[id[b - 1][i]] + weight[id[b - 1][i + 1]];
                from[n][0] = id[b - 1][i];
                from[n][1] = id[b - 1][i + 1];
                id[b].push_back(n);
                n ++;
                i += 2;
            }
        }
        sort(id[b].begin(), id[b].end(), compare);
        if (sum & 1) {
            if (id[b].empty()) {
                puts("0");
                return 0;
            }
            pick[id[b].front()] = true;
        }
        sum >>= 1;
    }
    for (int i = 0; i < n; ++ i) {
        if (pick[i]) {
            mark(i);
        }
    }
    int size = 0;
    for (int i = 0; i < oldN; ++ i) {
        if (pick[i]) {
            size ++;
        }
    }
    printf("%d\n", size);
    for (int i = 0; i < oldN; ++ i) {
        if (pick[i]) {
            printf("%d\n", i + 1);
        }
    }
    return 0;
}
