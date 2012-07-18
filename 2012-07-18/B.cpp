// Problem B -- Chip Reconstruction 
// Author: Xiaoxu Guo
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 1000;

int n, m, h, a[N], b[N];
char map[N][N];
vector <int> result[N], buffer[N + 1];
priority_queue <pair <int, int> > choice;

int main() {
    scanf("%d%d%d", &n, &m, &h);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < m; ++ i) {
        scanf("%d", b + i);
    }
    for (int i = 0; i < m; ++ i) {
        if (b[i] > 0) {
            choice.push(make_pair(b[i], i));
        }
    }
    bool valid = true;
    for (int i = 0; i < n && valid; ++ i) {
        for (vector <int> :: iterator iter = buffer[i].begin(); iter != buffer[i].end(); ++ iter) {
            if (b[*iter] > 0) {
                choice.push(make_pair(b[*iter], *iter));
            }
        }
        if (!valid) {
            break;
        }
        while (a[i] < m) {
            for (int j = 0; j < h; ++ j) {
                if (i + j >= n) {
                    valid = false;
                    break;
                }
                a[i + j] ++;
                if (a[i + j] > m) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                break;
            }
            if (choice.empty()) {
                valid = false;
                break;
            }
            int id = choice.top().second;
            b[id] --;
            choice.pop();
            result[id].push_back(i);
            buffer[i + h].push_back(id);
        }
    }
    for (int i = 0; i < m; ++ i) {
        valid &= b[i] == 0;
    }
    if (!valid) {
        puts("inconsistent");
    } else {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                map[i][j] = '*';
            }
        }
        for (int j = 0; j < m; ++ j) {
            for (vector <int> :: iterator iter = result[j].begin(); iter != result[j].end(); ++ iter) {
                map[*iter][j] = '+';
                for (int k = 1; k < h - 1; ++ k) {
                    map[(*iter) + k][j] = '|';
                }
                map[(*iter) + h - 1][j] = '+';
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                putchar(map[i][j]);
            }
            puts("");
        }
    }
    return 0;
}
