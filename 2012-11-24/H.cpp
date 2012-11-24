#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000;
const long long INF = 1000000000000000000LL;

int n, a[N], b[N], c[N];
vector <int> values;

bool by_begin(int i, int j) {
    return a[i] < a[j];
}

bool by_end(int i, int j) {
    return b[i] < b[j];
}

long long delta[N << 3];
pair <long long, int> minimum[N << 3];

int get_id(int l, int r) {
    return l + r | l != r;
}

void build(int l, int r) {
    int id = get_id(l, r);
    delta[id] = 0;
    minimum[id] = make_pair(0, l);
    if (l < r) {
        int m = l + r >> 1;
        build(l, m);
        build(m + 1, r);
    }
}

void insert(int l, int r, int a, int b, int c) {
    if (b < values[l] || values[r] < a) {
        return;
    }
    int id = get_id(l, r);
    if (a <= values[l] && values[r] <= b) {
        delta[id] += c;
        minimum[id].first += c;
    } else {
        int m = l + r >> 1;
        insert(l, m, a, b, c);
        insert(m + 1, r, a, b, c);
        minimum[id] = min(minimum[get_id(l, m)], minimum[get_id(m + 1, r)]); 
        minimum[id].first += delta[id];
    }
}

pair <long long, int> query(int l, int r, int a, int b) {
    if (b < values[l] || values[r] < a) {
        return make_pair(INF, -1);
    }
    int id = get_id(l, r);
    if (a <= values[l] && values[r] <= b) {
        return minimum[id];
    }
    int m = l + r >> 1;
    pair <long long, int> ret = min(query(l, m, a, b), query(m + 1, r, a, b));
    ret.first += delta[id];
    return ret;
}

int main() {
    freopen("lamps.in", "r", stdin);
    freopen("lamps.out", "w", stdout);
    scanf("%d", &n);
    vector <int> ends;
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", a + i, b + i, c + i);
        a[i] *= 2, b[i] *= 2;
        ends.push_back(a[i]);
        ends.push_back(b[i]);
    }
    sort(ends.begin(), ends.end());
    ends.erase(unique(ends.begin(), ends.end()), ends.end());
    for (int i = 0; i < (int)ends.size(); ++ i) {
        values.push_back(ends[i]);
        if (i + 1 < (int)ends.size()) {
            values.push_back(ends[i] / 2 + ends[i + 1] / 2);
        }
    }
    sort(values.begin(), values.end());
    vector <int> begin_order, end_order;
    for (int i = 0; i < n; ++ i) {
        begin_order.push_back(i);
        end_order.push_back(i);
    }
    sort(begin_order.begin(), begin_order.end(), by_begin);
    sort(end_order.begin(), end_order.end(), by_end);
    long long answer = INF;
    int first_cut = -1;
    int second_cut = -1;
    build(0, (int)values.size() - 1);
    int j = n - 1;
    int k = n - 1;
    long long total = 0;
    for (int i = 0; i < n; ++ i) {
        total += c[i];
    }
    long long left_total = total;
    long long right_total = 0;
    long long min_end = INF;
    long long max_begin = -INF;
    for (int i = (int)values.size() - 1; i >= 0; -- i) {
        while (j >= 0 && a[begin_order[j]] > values[i]) {
            min_end = min(min_end, (long long)b[begin_order[j]]);
            max_begin = max(max_begin, (long long)a[begin_order[j]]);
            insert(0, (int)values.size() - 1, a[begin_order[j]], b[begin_order[j]], c[begin_order[j]]);
            right_total += c[begin_order[j]];
            j --;
        }
        while (k >= 0 && b[end_order[k]] >= values[i]) {
            left_total -= c[end_order[k]];
            k --;
        }
        long long left_delete = total - left_total - right_total;
        if (left_total > 0 && min_end + 1 <= max_begin - 1) {
            pair <long long, int> ret = query(0, (int)values.size() - 1, min_end + 1, max_begin - 1);
            long long right_delete = ret.first;
            if (left_delete + right_delete < answer) {
                answer = left_delete + right_delete;
                first_cut = values[i];
                second_cut = values[ret.second];
            }
        }
    }
    if (answer == INF) {
        puts("-1");
    } else {
        cout << answer << endl;
        vector <int> ways;
        for (int i = 0; i < n; ++ i) {
            if (a[i] <= first_cut && first_cut <= b[i] 
                    || a[i] <= second_cut && second_cut <= b[i]) {
                ways.push_back(i);
            }
        }
        printf("%d\n", (int)ways.size());
        for (int i = 0; i < (int)ways.size(); ++ i) {
            printf("%d%c", ways[i] + 1, i == (int)ways.size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
