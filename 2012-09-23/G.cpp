#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

//#pragma comment(linker, "/STACK:10777216")

const int N = 333333;

int text[N];
char buffer[N];

int array[N], rank[N], newRank[N][2], counter[N], newArray[N], height[N];

void construct(int n) {
    vector <pair <int, int> > events;
    for (int i = 0; i < n; ++ i) {
        events.push_back(make_pair(text[i], i));
    }
    sort(events.begin(), events.end());
    for (int i = 0; i < n; ++ i) {
        array[i] = events[i].second;
    }
    rank[array[0]] = 1;
    for (int i = 1; i < n; ++ i) {
        rank[array[i]] = rank[array[i - 1]] + (text[array[i]] != text[array[i - 1]]);
    }
    for (int length = 1; length < n && *max_element(rank, rank + n) != n; length <<= 1) {
        for (int i = 0; i < n; ++ i) {
            newRank[i][0] = rank[i];
            newRank[i][1] = i + length < n? rank[i + length]: 0;
        }
        fill(counter, counter + (n + 1), 0);
        for (int i = n - 1; i >= 0; -- i) {
            counter[newRank[i][1]] ++;
        }
        for (int i = 1; i <= n; ++ i) {
            counter[i] += counter[i - 1];
        }
        for (int i = n - 1; i >= 0; -- i) {
            newArray[-- counter[newRank[i][1]]] = i;
        }
        fill(counter, counter + (n + 1), 0);
        for (int i = n - 1; i >= 0; -- i) {
            counter[newRank[i][0]] ++;
        }
        for (int i = 1; i <= n; ++ i) {
            counter[i] += counter[i - 1];
        }
        for (int i = n - 1; i >= 0; -- i) {
            array[-- counter[newRank[newArray[i]][0]]] = newArray[i];
        }
        rank[array[0]] = 1;
        for (int i = 1; i < n; ++ i) {
            rank[array[i]] = rank[array[i - 1]]
                + (newRank[array[i]][0] != newRank[array[i - 1]][0] || newRank[array[i]][1] != newRank[array[i - 1]][1]);
        }
    }
    for (int i = 0, length = 0; i < n; ++ i) {
        if (rank[i] > 1) {
            int j = array[rank[i] - 2];
            while (i + length < n && j + length < n && text[i + length] == text[j + length]) {
                length ++;
            }
            height[rank[i] - 1] = length;
            if (length > 0) {
                length --;
            }
        }
    }
}

int firstLength, length, sum[N];
long long result;

int children[N][2];

void solve(int root, int l, int r, int lcp) {
    int ret = l == r? firstLength - array[l]: height[root];
    if (sum[l] - sum[r + 1] == 0) {
        result += ret - lcp;
    }
    if (l < r) {
        solve(children[root][0], l, root - 1, ret);
        solve(children[root][1], root, r, ret);
    }
}

int main() {
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        int n;
        scanf("%d", &n);
        scanf("%s", buffer);
        firstLength = length = strlen(buffer);
        for (int i = 0; i < length; ++ i) {
            text[i] = buffer[i] - 'a';
        }
        for (int i = 0; i < n; ++ i) {
            text[length ++] = 26 + i;
            scanf("%s", buffer);
            for (int k = 0; buffer[k] != '\0'; ++ k) {
                text[length ++] = buffer[k] - 'a';
            }
        }
        construct(length);
        for (int i = 1; i < n; ++ i) {
            children[i][0] = children[i][1] = 0;
        }
        vector <int> stack;
        for (int i = 1; i < length; ++ i) {
            int p = 0;
            while ((int)stack.size() > 0 && height[stack.back()] >= height[i]) {
                children[stack.back()][1] = p;
                p = stack.back();
                stack.pop_back();
            }
            children[i][0] = p;
            stack.push_back(i);
        }
        int root  = 0;
        while ((int)stack.size() > 0) {
            children[stack.back()][1] = root;
            root = stack.back();
            stack.pop_back();
        }
        sum[length] = 0;
        for (int i = length - 1; i >= 0; -- i) {
            sum[i] = sum[i + 1] + (array[i] >= firstLength);
        }
        result = 0;
        solve(root, 0, length - 1, 0);
        cout << "Case " << t << ": " << result << endl;
    }
    
    return 0;
}
