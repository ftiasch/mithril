#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

using std::vector;
using std::pair;
using std::make_pair;

int delta, kappa, lambda;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int V = 50;

bool visit[V][V];

int main() {
    scanf("%d%d%d", &delta, &kappa, &lambda);
    memset(visit, 0, sizeof(visit));
    if (kappa <= lambda && lambda <= delta) {
        std::vector <std::pair <int, int> > edges;
        for (int i = kappa; i < kappa + delta + 1; ++ i) {
            for (int j = i + 1; j < kappa + delta + 1; ++ j) {
                edges.push_back(make_pair(i, j));
                edges.push_back(make_pair(i + (delta + 1), j + (delta + 1)));
            }
        }
        for (int i = 0; i < kappa; ++ i) {
            for (int j = 0; j < delta; ++ j) {
                edges.push_back(make_pair(i, kappa + j));
            }
            int bais = kappa + delta + 1;
            edges.push_back(make_pair(i, bais + i));
        }
        foreach (iter, edges) {
            visit[iter->first][iter->second] = true;
            visit[iter->second][iter->first] = true;
        }
        int left = lambda - kappa;
        for (int i = 0; i < kappa; ++ i) {
            int bais = kappa + delta + 1;
            for (int j = 0; j < delta + 1; ++ j) {
                if (!visit[i][bais + j] && left) {
                    left --;
                    edges.push_back(make_pair(i, bais + j));
                }
            }
        }
        printf("%d %d\n", (delta + 1 << 1) + kappa, (int)edges.size());
        foreach (iter, edges) {
            printf("%d %d\n", 1 + iter->first, 1 + iter->second);
        }
    } else {
        puts("0 0");
    }
    return 0;
}
