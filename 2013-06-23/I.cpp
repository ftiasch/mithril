#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()
#define SIZE(v) ((int)(v).size())

const int DELTA_X[4] = {0, -1,  0, 1};
const int DELTA_Y[4] = {1,  0, -1, 0};

struct Mirror {
    int t, x, y;

    Mirror(int t, int x, int y) : t(t), x(x), y(y) {}
};

bool operator < (const Mirror &a, const Mirror &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

const int maxR = 1000001;

int r, c;
std::vector <Mirror> rows[maxR], columns[maxR];

typedef std::vector <Mirror> :: iterator Iterator;

void get_next(int &x, int &y, int &d) {
    Mirror mirror(-1, x, y);
    if (d == 0) {
        Iterator iter = std::upper_bound(ALL(rows[x]), mirror);
        if (iter == rows[x].end()) {
            y = c + 1;
        } else {
            y = iter->y;
            d ^= iter->t;
        }
    } else if (d == 1) {
        Iterator iter = std::lower_bound(ALL(columns[y]), mirror);
        if (iter == columns[y].begin()) {
            x = 0;
        } else {
            iter --;
            x = iter->x;
            d ^= iter->t;
        }
    } else if (d == 2) {
        Iterator iter = std::lower_bound(ALL(rows[x]), mirror);
        if (iter == rows[x].begin()) {
            y = 0;
        } else {
            iter --;
            y = iter->y;
            d ^= iter->t;
        }
    } else if (d == 3) {
        Iterator iter = std::upper_bound(ALL(columns[y]), mirror);
        if (iter == columns[y].end()) {
            x = r + 1;
        } else {
            x = iter->x;
            d ^= iter->t;
        }
    }
}

struct Event {
    int t, d, x, y;
    
    Event(int t, int d, int x, int y) : t(t), d(d), x(x), y(y) {}
};

bool operator < (const Event &a, const Event &b) {
    return a.x < b.x;
}

struct Query {
    int t, x, y_1, y_2;

    Query(int t, int x, int y_1, int y_2) : t(t), x(x), y_1(y_1), y_2(y_2) {}
};

bool operator < (const Query &a, const Query &b) {
    return a.x < b.x;
}

std::vector <Event> events;
std::vector <Query> queries;

bool simulate(int t, int sx, int sy, int sd) {
    do {
        int x = sx, y = sy;
        get_next(sx, sy, sd);
//printf("%d %d %d\n", sx, sy, sd);
        if (x == sx) {
            // query
            if (std::min(y, sy) + 1 <= std::max(y, sy) - 1) {
                queries.push_back(Query(t, x, std::min(y, sy) + 1, std::max(y, sy) - 1));
            }
        } else {
            // event
            if (std::min(x, sx) + 1 <= std::max(x, sx) - 1) {
                events.push_back(Event(t,  1, std::min(x, sx) + 1, y));
                events.push_back(Event(t, -1, std::max(x, sx), y));
            }
        }
        if (sx == r && sy == c + 1) {
            return true;
        }
    } while (1 <= sx && sx <= r && 1 <= sy && sy <= c);
    return false;
}

const int N = 1000000;

int n, m, node_count, key[N], weight[N], count[N], size[N], children[N][2];

void update(int &x) {
    size[x] = size[children[x][0]] + count[x] + size[children[x][1]];
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, int k) {
    if (x == 0) {
        x = ++ node_count;
        key[x] = k;
        weight[x] = rand();
        count[x] = 1;
        children[x][0] = children[x][1] = 0;
    } else if (key[x] == k) {
        count[x] ++;
    } else {
        int t = key[x] < k;
        insert(children[x][t], k);
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    }
    update(x);
}

void erase(int &x, int k) {
    if (key[x] == k) {
        if (count[x] > 1) {
            count[x] --;
        } else {
            if (!children[x][0] && !children[x][1]) {
                x = 0;
                return;
            }
            rotate(x, weight[children[x][0]] > weight[children[x][1]]);
            erase(x, k);
        }
    } else {
        erase(children[x][key[x] < k], k);
    }
    update(x);
}

int query(int &x, int k) {
    if (x == 0) {
        return 0;
    }
    if (key[x] > k) {
        return query(children[x][0], k);
    }
    return size[children[x][0]] + count[x] + query(children[x][1], k);
}

int get_min(int &x, int k) {
    if (x == 0) {
        return INT_MAX;
    }
    if (key[x] >= k) {
        return std::min(get_min(children[x][0], k), key[x]);
    }
    return get_min(children[x][1], k);
}

int main() {
//freopen("I.in", "r", stdin);
    size[0] = 0;
    weight[0] = INT_MAX;
    int test_count = 0;
    while (scanf("%d%d%d%d", &r, &c, &n, &m) == 4) {
        std::cout << "Case " << (++ test_count) << ": ";
        for (int i = 1; i <= r; ++ i) {
            rows[i].clear();
        }
        for (int i = 1; i <= c; ++ i) {
            columns[i].clear();
        }
        for (int i = 0; i < n + m; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            Mirror mirror(i < n ? 1 : 3, x, y);
            rows[x].push_back(mirror);
            columns[y].push_back(mirror);
        }
        for (int i = 1; i <= r; ++ i) {
            std::sort(ALL(rows[i]));
        }
        for (int i = 1; i <= c; ++ i) {
            std::sort(ALL(columns[i]));
        }
        events.clear();
        queries.clear();
        if (simulate(0, 1, 0, 0)) {
            std::cout << 0 << std::endl;
        } else {
            simulate(1, r, c + 1, 2);
            std::sort(ALL(events));
            std::sort(ALL(queries));
            int roots[2] = {0, 0};
            node_count = 0;
            long long answer = 0;
            int min_r = INT_MAX, min_c = INT_MAX;
//for (int i = 0; i < SIZE(queries); ++ i) {
//    printf("%d %d %d %d\n" ,queries[i].t, queries[i].x, queries[i].y_1, queries[i].y_2);
//}
//for (int i = 0; i < SIZE(events); ++ i) {
//    printf("%d (%d, %d) %d\n" ,events[i].t, events[i].x, events[i].y, events[i].d);
//}
            for (int i = 0, j = 0; i < SIZE(queries); ++ i) {
                while (j < SIZE(events) && events[j].x <= queries[i].x) {
                    if (events[j].d == 1) {
                        insert(roots[events[j].t], events[j].y);
                    } else {
                        erase(roots[events[j].t], events[j].y);
                    }
                    j ++;
                }
                int t = queries[i].t ^ 1;
                answer += query(roots[t], queries[i].y_2);
                answer -= query(roots[t], queries[i].y_1 - 1);
                int x = queries[i].x;
                int y = get_min(roots[t], queries[i].y_1);
                if (y <= queries[i].y_2) {
                    if (x < min_r || (x == min_r && y < min_c)) {
                        min_r = x;
                        min_c = y;
                    }
                }
            }
            if (answer == 0) {
                std::cout << "impossible" << std::endl;
            } else {
                std::cout << answer << " " << min_r << " " << min_c << std::endl;
            }
        }
    }
    return 0;
}
