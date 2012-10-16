#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000000;
const int MAXN = 100000;

typedef unsigned long long ULL;

//#define foreach(i, v) for (typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

int n;
ULL p[MAXN];

const int MAXT = (MAXN << 1) + 1;

int nodeCount, weight[MAXT], children[MAXT][2], value[MAXT], sum[MAXT], minSum[MAXT];
ULL key[MAXT];

void update(int &x) {
    sum[x] = sum[children[x][0]] + value[x] + sum[children[x][1]];
    minSum[x] = min(min(minSum[children[x][0]], 0) + value[x] + sum[children[x][1]], minSum[children[x][1]]);
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, ULL k, int v) {
    if (!x) {
        x = nodeCount ++;
        key[x] = k;
        value[x] = v;
        weight[x] = rand();
        children[x][0] = children[x][1] = 0;
    } else if (key[x] == k) {
        value[x] += v;
    } else {
        int t = key[x] < k;
        insert(children[x][t], k, v);
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    }
    update(x);
}

void erase(int &x, ULL k) {
    if (x) {
        if (key[x] != k) {
            erase(children[x][key[x] < k], k);
        } else {
            if (!children[x][0] && !children[x][1]) {
                x = 0;
                return;
            }
            rotate(x, weight[children[x][0]] > weight[children[x][1]]);
            erase(x, k);
        }
        update(x);
    }
}

bool find(int &x, ULL k) {
    if (!x) {
        return false;
    }
    if (key[x] == k) {
        return true;
    }
    return find(children[x][key[x] < k], k);
}

int main() {
    sum[0] = 0;
    minSum[0] = INF;
    weight[0] = INT_MAX;
    while (cin >> n) {
        ULL l, r, a, b;
        cin >> l >> r >> a >> b;
        for (int i = 0; i < n; ++ i) {
            cin >> p[i];
        }
        vector <pair <ULL, short> > events;
        for (int i = 0; i < n; ++ i) {
            events.push_back(make_pair(p[i], 1));
            if (p[i] + b >= l + a) {
                events.push_back(make_pair(p[i] + b - a, -1));
            }
        }
        sort(events.begin(), events.end());
        vector <ULL> points;
        for (int i = 0; i < (int)events.size(); ++ i) {
#define INSERT(x) if ((x) + a <= r + 1) { \
    points.push_back(x); \
}
            INSERT(events[i].first);
            if (events[i].first >= l + b) {
                INSERT(events[i].first - b);
            }
#undef INSERT
        }
        points.push_back(r + 1 - a);
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        int result = 0;
        if (a) {
            int suffix = 0;
            nodeCount = 0;
            int root = nodeCount ++;
            for (int i = (int)points.size() - 1, 
                     j = (int)events.size() - 1, 
                     k = (int)events.size() - 1; i >= 0; -- i) {
                while (j >= 0 && events[j].first >= points[i]) {
                    insert(root, events[j].first, events[j].second);
                    j --;
                }
                while (k >= 0 && events[k].first > points[i] + b) {
                    suffix += events[k].second;
                    erase(root, events[k].first);
                    k --;
                }
                int tmp = INT_MAX;
                if (root) {
                    tmp = min(tmp, minSum[root] + suffix);
                }
                if (!find(root, points[i] + b)) {
                    tmp = min(tmp, suffix);
                }
                result = max(result, tmp);
            }
        }
        cout << result << endl;
    }
    return 0;
}
