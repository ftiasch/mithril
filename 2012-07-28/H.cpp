#include <cstdio>
#include <cstring>
#include <queue>
#include <list>
using namespace std;

const int N = 50;

int n, m, map[N][N];
bool used[N][N];

struct Rectangle {
    int lowI, lowJ, highI, highJ;

    Rectangle(int lowI, int lowJ, int highI, int highJ): lowI(lowI), lowJ(lowJ), highI(highI), highJ(highJ) {}

    int count() {
        return map[lowI][lowJ] + map[lowI][highJ] + map[highI][lowJ] + map[highI][highJ];
    }
};

queue <Rectangle> choices[5];

inline void remove(int x, int y) {
    for (int i = 0; i < n; ++ i) {
        if (i != x) {
            for (int j = 0; j < m; ++ j) {
                if (j != y) {
                    Rectangle r(i, j, x, y);
                    if (r.count() > 0) {
                        choices[r.count()].push(r);
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        char buffer[N + 1];
        scanf("%s", buffer);
        for (int j = 0; j < m; ++ j) {
            map[i][j] = buffer[j] == 'i';
        }
    }
    for (int lowI = 0; lowI < n; ++ lowI) {
        for (int highI = lowI + 1; highI < n; ++ highI) {
            for (int lowJ = 0; lowJ < m; ++ lowJ) {
                for (int highJ = lowJ + 1; highJ < m; ++ highJ) {
                    int cnt = map[lowI][lowJ] + map[lowI][highJ] + map[highI][lowJ] + map[highI][highJ];
                    if (cnt > 0) {
                        choices[cnt].push(Rectangle(lowI, lowJ, highI, highJ));
                    }
                }
            }
        }
    }
    int result = 0;
    bool found = true;
    while (found) {
        found = false;
        for (int i = 1; i <= 4 && !found; ++ i) {
            while (!choices[i].empty() && !found) {
                Rectangle r = choices[i].front();
                choices[i].pop();
                if (r.count() != i) {
                    continue;
                }
                result ++;
                map[r.lowI][r.lowJ] = map[r.lowI][r.highJ] = map[r.highI][r.lowJ] = map[r.highI][r.highJ] = 0;
                remove(r.lowI, r.lowJ);
                remove(r.lowI, r.highJ);
                remove(r.highI, r.lowJ);
                remove(r.highI, r.highJ);
                found = true;
            }
        }
    }
    printf("%d\n", result);
    return 0;
}
