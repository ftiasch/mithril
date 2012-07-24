#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000;

int n, x[N][2], y[N][2];

const int INSERT = 0;
const int QUERY = 1;
const int DELETE = 2;

const int DELTA = 1000001;


struct Event {
    int x, type, low, high;

    Event(int x, int type, int low, int high): x(x), type(type), low(low), high(high) {}
};

bool operator <(const Event &a, const Event &b) {
    if (a.x == b.x) {
        return a.type < b.type;
    }
    return a.x < b.x;
}

const int M = 2222222;

struct BinaryIndexTree {
    static int markCount, mark[M];

    int count[M];

    void clear() {
        markCount ++;
    }

    void insert(int key, int value) {
        for (int i = key; i < M; i += i & -i) {
            if (mark[i] != markCount) {
                mark[i] = markCount;
                count[i] = 0;
            }
            count[i] += value;
        }
    }

    int query(int key) {
        int result = 0;
        for (int i = key; i >= 1; i -= i & -i) {
            if (mark[i] != markCount) {
                mark[i] = markCount;
                count[i] = 0;
            }
            result += count[i];
        }
        return result;
    }
};

int BinaryIndexTree::markCount;
int BinaryIndexTree::mark[M];

BinaryIndexTree tree;

long long count(vector <pair <int, int> > segments) {
    long long result = 0;
    sort(segments.begin(), segments.end());
    tree.clear();
    for (int i = (int)segments.size() - 1; i >= 0; -- i) {
        result += tree.query(segments[i].second);
        tree.insert(segments[i].first, 1);
    }
    return result;
}

bool compare(int i, int j) {
    return x[i][0] < x[j][0];
}

long long solve() {
    vector <int> order;
    for (int i = 0; i < n; ++ i) {
        if (x[i][0] == x[i][1]) {
            order.push_back(i);
        }
    }
    sort(order.begin(), order.end(), compare);
    vector <pair <int, int> > segments;
    long long result = 0;
    for (int i = 0; i < (int)order.size(); ++ i) {
        int j = i;
        while (j < (int)order.size() && x[order[i]][0] == x[order[j]][0]) {
            j ++;
        }
        segments.clear();
        for (int k = i; k < j; ++ k) {
            segments.push_back(make_pair(y[order[k]][0], y[order[k]][1]));
        }
        result += count(segments);
        i = j - 1;
    }
    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d%d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
        if (x[i][0] > x[i][1]) {
            swap(x[i][0], x[i][1]);
        }
        if (y[i][0] > y[i][1]) {
            swap(y[i][0], y[i][1]);
        }
        for (int j = 0; j < 2; ++ j) {
            x[i][j] += DELTA;
            y[i][j] += DELTA;
        }
    }
    long long result = 0;
    vector <Event> events;
    vector <pair <int, int> > points;
    for (int i = 0; i < n; ++ i) {
        if (x[i][0] < x[i][1] || y[i][0] < y[i][1]) {
            if (x[i][0] == x[i][1]) {
                events.push_back(Event(x[i][0], QUERY, y[i][0], y[i][1]));
            } else {
                events.push_back(Event(x[i][0], INSERT, y[i][0], y[i][1]));
                events.push_back(Event(x[i][1], DELETE, y[i][1], y[i][1]));
            }
        } else {
            points.push_back(make_pair(x[i][0], y[i][0]));
        }
    }
    sort(points.begin(), points.end());
    for (int i = 0; i < (int)points.size(); ++ i) {
        int j = i;
        while (j < (int)points.size() && points[i] == points[j]) {
            j ++;
        }
        int size = j - i;
        result -= (long long)size * (size - 1) / 2;
        i = j - 1;
    }
    sort(events.begin(), events.end());
    tree.clear();
    for (int i = 0; i < (int)events.size(); ++ i) {
        if (events[i].type == INSERT) {
            tree.insert(events[i].low, 1);
        } else if (events[i].type == QUERY) {
            result += tree.query(events[i].high) - tree.query(events[i].low - 1);
        } else {
            tree.insert(events[i].low, -1);
        }
    }
    result += solve();
    for (int i = 0; i < n; ++ i) {
        swap(x[i][0], y[i][0]);
        swap(x[i][1], y[i][1]);
    }
    result += solve();
    cout << result << endl;
    return 0;
}
