#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

const int D = 20;
const int N = 200000;

int n;
char string[N + 1];

int array[N], rank[N], count[N + 1], newRank[N][2], newArray[N], height[N];

void construct() {
    if (n == 1) {
        array[0] = rank[0] = 0;
        return;
    }
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; ++ i) {
        count[(int)string[i]] ++;
    }
    for (int i = 0; i < 255; ++ i) {
        count[i + 1] += count[i];
    }
    for (int i = 0; i < n; ++ i) {
        rank[i] = count[(int)string[i]] - 1;
    }
    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; ++ i) {
            newRank[i][0] = rank[i];
            newRank[i][1] = i + l >= n ? 0 : rank[i + l] + 1;
        }
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++ i) {
            count[newRank[i][1]] ++;
        }
        for (int i = 0; i < n; ++ i) {
            count[i + 1] += count[i];
        }
        for (int i = 0; i < n; ++ i) {
            newArray[-- count[newRank[i][1]]] = i;
        }
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++ i) {
            count[newRank[i][0]] ++;
        }
        for (int i = 0; i < n; ++ i) {
            count[i + 1] += count[i];
        }
        for (int i = n - 1; i >= 0; -- i) {
            array[-- count[newRank[newArray[i]][0]]] = newArray[i];
        }
        rank[array[0]] = 0;
        for (int i = 1; i < n; ++ i) {
            rank[array[i]] = rank[array[i - 1]] + (newRank[array[i]][0] != newRank[array[i - 1]][0] || newRank[array[i]][1] != newRank[array[i - 1]][1]);
        }
        if (rank[array[n - 1]] == n - 1) {
            break;
        }
    }
    for (int i = 0, now = 0; i < n; ++ i) {
        if (rank[i]) {
            int j = array[rank[i] - 1];
            while (i + now < n && j + now < n && string[i + now] == string[j + now]) {
                now ++;
            }
            height[rank[i] - 1] = now;
            if (now) {
                now --;
            }
        }
    }
}

int minimum[D][N], log[N + 1], begin[N], end[N];

int get_minimum(int i, int j) { // [i, j)
    int l = log[j - i];
    return std::min(minimum[l][i], minimum[l][j - (1 << l)]);
}


typedef unsigned long long ULL;

const ULL MAGIC = 173;

ULL power[N + 1], hash[N + 1];

ULL get_hash(int i, int l) {
    return hash[i] - hash[i + l] * power[l];
}

int get_lcp(int i, int j) {
    int low = 0;
    int high = std::min(n - i, n - j);
    while (low < high) {
        int middle = low + high + 1 >> 1;
        if (get_hash(i, middle) == get_hash(j, middle)) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return low;
}

struct Data {
    int i, j;

    Data(int i = -1, int j = -1): i(i), j(j) {}
};

bool operator <(const Data &a, const Data &b) {
    if (a.i == -1) {
        return false;
    }
    if (b.i == -1) {
        return true;
    }
    int x = get_lcp(a.i, a.j);
    int z = get_lcp(a.i, b.i);
    if (z < x && string[a.i + z] != string[b.i + z]) {
        return string[a.i + z] < string[b.i + z];
    }
    if (a.i != b.i) {
        return a.i < b.i;
    }
    return a.j < b.j;
}

Data answer[N + 1];

int main() {
    scanf("%s", string);
    n = strlen(string);
    power[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        power[i] = power[i - 1] * MAGIC;
    }
    hash[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        hash[i] = hash[i + 1] * MAGIC + string[i];
    }
    construct();
    //for (int i = 0; i < n; ++ i) {
    //    printf("%s\n", string + array[i]);
    //}

    for (int i = 0; i < n; ++ i) {
        minimum[0][i] = array[i];
    }
    for (int j = 1; j < D; ++ j) {
        for (int i = 0; i + (1 << j) <= n; ++ i) {
            minimum[j][i] = std::min(minimum[j - 1][i], minimum[j - 1][i + (1 << j - 1)]);
        }
    }
    log[0] = 0;
    for (int i = 1; i <= n; ++ i) {
        log[i] = log[i - 1];
        if (1 << log[i] + 1 < i) {
            log[i] ++;
        }
    }
    // height [0..n)
    for (int i = 0; i < n - 1; ++ i) {
        begin[i] = i - 1;
        while (begin[i] != -1 && height[begin[i]] >= height[i]) {
            begin[i] = begin[begin[i]];
        }
    }
    for (int i = n - 2; i >= 0; -- i) {
        end[i] = i + 1;
        while (end[i] != n - 1 && height[end[i]] >= height[i]) {
            end[i] = end[end[i]];
        }
    }
    for (int i = 0; i < n; ++ i) {
        answer[n - i] = Data(i, i);
    }
//for (int i = 0; i < n; ++ i) {
//    printf("%s\n", string + array[i]);
//}
    for (int i = 0; i + 1 < n; ++ i) {
        int l = begin[i] + 1;
        int r = end[i];
        int a = get_minimum(l, i + 1);
        int b = get_minimum(i + 1, r + 1);
        if (a > b) {
            std::swap(a, b);
        }
        Data d(a, b);
        answer[height[i]] = std::min(answer[height[i]], d);
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        int l;
        scanf("%d", &l);
        if (answer[l].i == -1) {
            puts("-1 -1");
        } else {
            printf("%d %d\n", answer[l].i + 1, answer[l].j + 1);
        }
    }
    return 0;
}
