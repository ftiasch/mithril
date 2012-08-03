#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 111111;

int length, array[N], rank[N], cnt[N], tmpRank[N][2], tmpArray[N], height[N], queue[N];
char text[N];
int minimum[N << 2];

int n, m;
int to[N][26];

const int T = 222222;

int trieCount, children[T][26];

void build(int t, int l, int r) {
    if (l + 1 == r) {
        minimum[t] = height[r];
    } else {
        int m = (l + r) >> 1;
        build(t << 1, l, m);
        build((t << 1) + 1, m, r);
        minimum[t] = min(minimum[t << 1], minimum[(t << 1) + 1]);
    }
}

int query(int t, int l, int r, int i, int j) {
    //printf("%d, %d, %d, %d\n", t, l, r, minimum[t]);
    if (j <= l || r <= i) {
        return INT_MAX;
    }
    if (i <= l && r <= j) {
        return minimum[t];
    }
    int m = (l + r) >> 1;
    return min(query(t << 1, l, m, i, j), query((t << 1) + 1, m, r, i, j));
}

int lcp(int i, int j) {
    if (i == j) {
        return length - array[i];
    }
    if (i > j) {
        return lcp(j, i);
    }
    return query(1, 0, length - 1, i, j);
}

vector <char> stack;

void dfs(int u) {
    int cnt = 0;
    for (int token = 0; token < 26; ++ token) {
        if (children[u][token] != -1) {
            cnt ++;
            stack.push_back(token);
            dfs(children[u][token]);
            stack.pop_back();
        }
    }
    if (u && !cnt) {
        for (int i = 0; i < (int)stack.size(); ++ i) {
            printf("%c", stack[i] + 'a');
        }
        puts("");
    }
}

int main() {
    scanf("%s", text);
    length = strlen(text);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < length; ++ i) {
        cnt[text[i] - 'a'] ++;
    }
    for (int i = 1; i < 26; ++ i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < length; ++ i) {
        array[-- cnt[text[i] - 'a']] = i;
    }
    rank[array[0]] = 0;
    for (int i = 1; i < length; ++ i) {
        rank[array[i]] = rank[array[i - 1]] + (text[array[i]] != text[array[i - 1]]);
    }
    for (int k = 1; k < length; k <<= 1) {
        for (int i = 0; i < length; ++ i) {
            tmpRank[i][0] = rank[i] + 1;
            tmpRank[i][1] = i + k < length? (rank[i + k] + 1): 0;
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < length; ++ i) {
            cnt[tmpRank[i][1]] ++;
        }
        for (int i = 1; i <= length; ++ i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = length - 1; i >= 0; -- i) {
            tmpArray[-- cnt[tmpRank[i][1]]] = i;
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < length; ++ i) {
            cnt[tmpRank[i][0]] ++;
        }
        for (int i = 1; i <= length; ++ i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = length - 1; i >= 0; -- i) {
            array[-- cnt[tmpRank[tmpArray[i]][0]]] = tmpArray[i];
        }
        rank[array[0]] = 0;
        for (int i = 1; i < length; ++ i) {
            rank[array[i]] = rank[array[i - 1]] + (tmpRank[array[i]][0] != tmpRank[array[i - 1]][0] || tmpRank[array[i]][1] != tmpRank[array[i - 1]][1]);
        }
    }
    for (int i = 0, k = 0; i < length; ++ i) {
        if (rank[i]) {
            int j = array[rank[i] - 1];
            while (i + k < length && j + k < length && text[i + k] == text[j + k]) {
                k ++;
            }
            height[rank[i]] = k;
            if (k) {
                k --;
            }
        }
    }
    scanf("%d%d", &n, &m);
    memset(to, 0, sizeof(to));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        char buffer[2];
        scanf("%d%d%s", &a, &b, buffer);
        if ('a' <= *buffer && *buffer <= 'z') {
            to[a][*buffer - 'a'] = b;
        }
    }
//for (int i = 0; i < length; ++ i) {
//    printf(">> %s\n", text + array[i]);
//}
    if (length > 1) {
        build(1, 0, length - 1);
    }
    int limit;
    scanf("%d", &limit);
    vector <int> nodes;
    nodes.push_back(1);
    int curIndex = -1;
    int curLength = 0;
    trieCount = 1;
    memset(children, -1, sizeof(children));
    for (int i = limit - 1; i < length; ++ i) {
        int upperBound = lcp(i - limit + 1, i);
        int lowerBound = 1;
        if (i - limit >= 0) {
            lowerBound = max(lowerBound, height[i - limit + 1] + 1);
        }
        if (i + 1 < length) {
            lowerBound = max(lowerBound, height[i + 1] + 1);
        }
        if (upperBound < 0) {
            printf("%d, %d\n", i, i - limit + 1);
            return -1;
        }
//printf("%s %d %d\n", text + array[i], lowerBound, upperBound);
        if (lowerBound <= upperBound) {
            //puts("hi");
            if (curIndex != -1) {
                int curLCP = min(lcp(curIndex, i), curLength);
                while (curLCP + 1 < (int)nodes.size()) {
                    nodes.pop_back();
                }
            }
            curIndex = i;
            curLength = (int)nodes.size() - 1;
            while (curLength > upperBound) {
                curLength --;
                nodes.pop_back();
            }
            while (curLength < upperBound) {
                if (array[i] + curLength < length && to[nodes.back()][text[array[i] + curLength] - 'a']) {
                    nodes.push_back(to[nodes.back()][text[array[i] + curLength] - 'a']);
                    curLength ++;
                } else {
                    break;
                }
            }
            if (curLength >= lowerBound) {
                int p = 0;
                for (int k = 0; k < curLength; ++ k) {
                    int token = text[array[i] + k] - 'a';
                    if (children[p][token] == -1) {
                        children[p][token] = trieCount ++;
                    }
                    p = children[p][token];
                }
            }
        }
    }
    dfs(0);
    return 0;
}
