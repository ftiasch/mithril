#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

const int N = 200000;
const int M = 500000;

int n, m, next[M], params[M][2], answer[N];
char buffer[2], type[M];

std::vector <int> indices[N];

int count(int l, int r, int v) {
    std::vector <int> &vec = indices[v];
    return std::lower_bound(vec.begin(), vec.end(), r) - std::lower_bound(vec.begin(), vec.end(), l);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%s%d", buffer, &params[i][0]);
        type[i] = *buffer;
        if (type[i] != '!') {
            scanf("%d", &params[i][1]);
            if (params[i][0] > params[i][1]) {
                std::swap(params[i][0], params[i][1]);
            }
        } else {
            indices[params[i][0] - 1].push_back(i);
        }
        params[i][0] --;
        params[i][1] --;
    }
    std::map <std::pair <int, int>, int> friends;
    for (int i = m - 1; i >= 0; -- i) {
        std::pair <int, int> f(params[i][0], params[i][1]);
        if (type[i] == '-') {
            friends[f] = i;
        } 
        if (type[i] == '+') {
            if (friends.count(f)) {
                next[i] = friends[f];
                friends.erase(f);
            } else {
                next[i] = m;
            }
        }
    }
    for (int i = 0; i < m; ++ i) {
        if (type[i] == '+') {
            for (int j = 0; j < 2; ++ j) {
                answer[params[i][j ^ 1]] += count(i, next[i], params[i][j]);
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", answer[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
