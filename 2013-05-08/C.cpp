#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000;
typedef pair <int, int> Pair;
typedef set <Pair, greater <Pair> > Set;

int n, h, w, width[N], start[N + 1], belongs[N];
char buffer[N + 1];
vector <char> map[N];

bool full[N];

int height[N];

bool by_height(int i, int j) {
    return height[i] > height[j];
}

vector <int> to_left[N], to_right[N];

int find(vector <int> &link, int i) {
    if (link[i] != i) {
        link[i] = find(link, link[i]);
    }
    return link[i];
}

vector <Pair> take(Set &s, int count) {
    vector <Pair> ret;
    __typeof((s).begin()) it = s.begin();
    while (count -- && it != s.end()) {
        ret.push_back(*it);
        it ++;
    }
    ret.push_back(make_pair(0, -1));
    return ret;
}

int solve(int answer = -1) {
    memset(height, 0, sizeof(height));
    int max_area = -1;
    for (int baseline = 0; baseline < h; ++ baseline) {
        vector <int> order;
        for (int i = 0; i < w; ++ i) {
            if (map[baseline][i] == '1') {
                height[i] = 0;
            } else {
                height[i] ++;
            }
            order.push_back(i);
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j <= width[i]; ++ j) {
                to_left[i][j] = to_right[i][j] = j;
            }
        }
        sort(order.begin(), order.end(), by_height);
        int total = 0;
        Set lefts, rights;
        for (int i = 0; i < n; ++ i) {
            lefts.insert(make_pair(0, i));
            rights.insert(make_pair(0, i));
        }
        fill(full, full + n, false);
        for (int _ = 0; _ < w; ++ _) {
            int i = order[_];
            int id = belongs[i];
            int j = i - start[id];
            rights.erase(make_pair(find(to_right[id], 0), id));
            lefts.erase(make_pair(width[id] - find(to_left[id], width[id]), id));
            to_left[id][j + 1] = j;
            to_right[id][j] = j + 1;
            max_area = max(max_area, (find(to_right[id], j + 1) - find(to_left[id], j)) * height[i]);
            if (max_area == answer) {
                printf("%d", id + 1);
                for (int k = 0; k < n; ++ k) {
                    if (k != id) {
                        printf(" %d", k + 1);
                    }
                }
                puts("");
                printf("%d %d %d %d\n", baseline + 2 - height[i], find(to_left[id], j) + 1, baseline + 1, find(to_right[id], j + 1));
                return -1;
            }
            if (find(to_left[id], width[id]) == 0) {
                total += width[id];
                full[id] = true;
            } else {
                rights.insert(make_pair(find(to_right[id], 0), id));
                lefts.insert(make_pair(width[id] - find(to_left[id], width[id]), id));
            }
            vector <Pair> leftv(take(lefts, 2));
            vector <Pair> rightv(take(rights, 2));
            int now_area = total * height[i];
            if (now_area == answer) {
                vector <int> config;
                for (int k = 0; k < n; ++ k) {
                    if (full[k]) {
                        config.push_back(k);
                    }
                }
                for (int k = 0; k < n; ++ k) {
                    if (!full[k]) {
                        config.push_back(k);
                    }
                }
                for (int k = 0; k < n; ++ k) {
                    printf("%d%c", config[k] + 1, " \n"[k == n - 1]);
                }
                printf("%d %d %d %d\n", baseline + 2 - height[i], 1, baseline + 1, total);
                return -1;
            }
            foreach (p, leftv) {
                foreach (q, rightv) {
                    if (p->second != q->second) {
                        now_area = max(now_area, (total + p->first + q->first) * height[i]);
                        if (now_area == answer) {
                            vector <int> config;
                            if (p->second != -1) {
                                config.push_back(p->second);
                            }
                            for (int k = 0; k < n; ++ k) {
                                if (full[k]) {
                                    config.push_back(k);
                                }
                            }
                            if (p->second != -1) {
                                full[p->second] = true;
                            }
                            if (q->second != -1) {
                                config.push_back(q->second);
                                full[q->second] = true;
                            }
                            for (int k = 0; k < n; ++ k) {
                                if (!full[k]) {
                                    config.push_back(k);
                                }
                            }
                            for (int k = 0; k < n; ++ k) {
                                printf("%d%c", config[k] + 1, " \n"[k == n - 1]);
                            }
                            int where = p->second == -1 ? 1 : width[p->second] - p->first + 1;
                            printf("%d %d %d %d\n", baseline + 2 - height[i], where, baseline + 1, where + total + p->first + q->first - 1);
                            return -1;
                        }
                    }
                }
            }
            if (now_area > max_area) {
                max_area = now_area;
            }
        }
    }
    return max_area;
}

int main() {
    scanf("%d%d", &n, &h);
    start[0] = 0;
    w = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", width + i);
        w += width[i];
        start[i + 1] = start[i] + width[i];
        for (int j = start[i]; j < start[i + 1]; ++ j) {
            belongs[j] = i;
        }
        for (int j = 0; j < h; ++ j) {
            scanf("%s", buffer);
            for (int k = 0; k < width[i]; ++ k) {
                map[j].push_back(buffer[k]);
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        to_left[i].resize(width[i] + 1);
        to_right[i].resize(width[i] + 1);
    }
    int max_area = solve(-1);
    solve(max_area);
    return 0;
}
