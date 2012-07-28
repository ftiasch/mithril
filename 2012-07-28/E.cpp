#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100000;

int n, a[N], b[N], c[N], o[N], cnt[N];

bool cmp(int i, int j) {
    if (a[i] == a[j]) {
        return b[i] > b[j];
    }
    return a[i] < a[j];
}

int query(int k) {
    int result = INT_MAX;
    for (int i = k; i >= 1; i -= i & -i) {
        result = min(result, cnt[i]);
    }
    return result;
}

void insert(int k, int v) {
    for (int i = k; i <= n; i += i & -i) {
        cnt[i] = min(cnt[i], v);
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", a + i, b + i, c + i);
        a[i] *= -1;
        b[i] *= -1;
        c[i] *= -1;
        o[i] = i;
    }
    sort(o, o + n, cmp);
    
    vector <int> values;
    for (int i = 0; i < n; ++ i) {
        values.push_back(b[i]);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    for (int i = 0; i < n; ++ i) {
        b[i] = lower_bound(values.begin(), values.end(), b[i]) - values.begin() + 1;
    }
    for (int i = 1; i <= n; ++ i) {
        cnt[i] = INT_MAX;
    }
    int result = n;
    for (int i = 0; i < n; ++ i) {
        if (query(b[o[i]] - 1) < c[o[i]]) {
            result --;
        }
        insert(b[o[i]], c[o[i]]);
    }
    printf("%d\n", result);
    return 0;
}
