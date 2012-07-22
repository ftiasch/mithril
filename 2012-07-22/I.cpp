#include <cstdio>
#include <cstring>
#include <climits>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}

    Point negate() const {
        return Point(-x, -y);
    }
};

ostream &operator <<(ostream &out, Point &p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

bool operator <(const Point &a, const Point &b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

Point operator +(const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator *(const Point &a, int k) {
    return Point(a.x * k, a.y * k);
}

const Point velocity[6] = {Point(1, -1), Point(1, 0), Point(0, 1), Point(-1, 1), Point(-1, 0), Point(0, -1)};

const int N = 20;
const int M = 10;
const int K = 3 * N * N - 3 * N + 1;
const int V = 100;
const int E = 4000;

Point coordinates[K];
map <Point, int> mapping;

int n, m, initialCost[K], need[M], edgeCount, firstEdge[V], to[E], nextEdge[E], capacity[E], cost[E], queue[V], previous[V], dist[V];
bool valid[K], visit[V];

int size(int n) {
    return 3 * n * n - 3 * n + 1;
}

void myAddEdge(int u, int v, int c, int w) {
    to[edgeCount] = v;
    capacity[edgeCount] = c;
    cost[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void addEdge(int a, int b, int c, int w) {
    myAddEdge(a, b, c, w);
    myAddEdge(b, a, 0, -w);
}

int main() {
    mapping[Point(0, 0)] = 0;
    coordinates[0] = Point(0, 0);
    {
        int counter = 1;
        for (int i = 1; i < N; ++ i) {
            int pointer = 0;
            Point current = velocity[0] * i;
            int times = size(i + 1) - size(i);
            while (times > 0) {
                times --;
                mapping[current] = counter;
                coordinates[counter ++] = current;
                while (mapping.find(current + velocity[(pointer + 1) % 6]) == mapping.end()) {
                    pointer = (pointer + 1) % 6;
                }
                current = current + velocity[pointer];
            }
        }
    }
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        printf("Case %d:\n", t);
        scanf("%d%d", &n, &m);
        for (int i = 0; i < size(n); ++ i) {
            scanf("%d", initialCost + i);
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d", need + i);
        }
        edgeCount = 0;
        memset(firstEdge, -1, sizeof(firstEdge));
        int minX = INT_MAX;
        int maxX = INT_MIN;
        int minY = INT_MAX;
        int maxY = INT_MIN;
        for (int i = 0; i < size(n); ++ i) {
            Point &p = coordinates[i];
            minX = min(minX, p.x);
            maxX = max(maxX, p.x);
            minY = min(minY, p.y);
            maxY = max(maxY, p.y);
        }
        int totalX = maxX - minX + 1;
        int totalY = maxY - minY + 1;
        memset(valid, true, sizeof(valid));
        for (int k = 0; k < m; ++ k) {
            edgeCount = 0;
            memset(firstEdge, -1, sizeof(firstEdge));
            int source = totalX + totalY;
            int target = source + 1;
            for (int i = 0; i < totalX; ++ i) {
                addEdge(source, i, 3, 0);
            }
            for (int i = 0; i < totalY; ++ i) {
                addEdge(totalX + i, target, 2, 0);
            }
            for (int i = 0; i < size(n); ++ i) {
                if (valid[i]) {
                    Point &p = coordinates[i];
                    addEdge(p.x - minX, p.y - minY + totalX, 1, initialCost[i] + k);
                }
            }
            int result = 0;
            while (need[k] > 0) {
                need[k] --;
                for (int i = 0; i <= target; ++ i) {
                    dist[i] = INT_MAX;
                }
                dist[source] = 0;
                memset(visit, 0, sizeof(visit));
                int tail = 0;
                queue[tail ++] = source;
                int head = 0;
                while (head != tail) {
                    int u = queue[head];
                    visit[u] = false;
                    head = (head + 1) % V;
                    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                        if (capacity[iter] > 0 && dist[u] + cost[iter] < dist[to[iter]]) {
                            previous[to[iter]] = iter;
                            dist[to[iter]] = dist[u] + cost[iter];
                            if (!visit[to[iter]]) {
                                visit[to[iter]] = true;
                                queue[tail] = to[iter];
                                tail = (tail + 1) % V;
                            }
                        }
                    }
                }
                for (int i = target; i != source; i = to[previous[i] ^ 1]) {
                    result += cost[previous[i]];
                    capacity[previous[i]] --;
                    capacity[previous[i] ^ 1] ++;
                }
            }
            printf("Month %d: %d unit of money\n", k + 1, result);
            for (int i = 0; i < edgeCount; i += 2) {
                int u = to[i ^ 1];
                int v = to[i];
                if (0 <= u && u < totalX && totalX <= v && v < totalX + totalY && capacity[i] == 0) {
                    valid[mapping[Point(u + minX, v - totalX + minY)]] = false;
                }
            }
        }
        puts("");
    }
    return 0;
}
