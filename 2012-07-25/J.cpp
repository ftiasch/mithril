#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

#define X first
#define Y second

const int N = 1000;

int n;
pair <int, int> points[N];

int main() {
    while (scanf("%d", &n) == 1 && n > 0) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &points[i].X, &points[i].Y);
        }
        sort(points, points + n);
        int result = 0;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < i; ++ j) {
                if (((points[i].X + points[i].Y + points[j].X + points[j].Y) % 2) == 0) {
                    if (binary_search(points, points + n, make_pair((points[i].X + points[j].X + points[i].Y - points[j].Y) / 2, (points[i].Y + points[j].Y - points[i].X + points[j].X) / 2)) 
                            && binary_search(points, points + n, make_pair((points[i].X + points[j].X - points[i].Y + points[j].Y) / 2, (points[i].Y + points[j].Y + points[i].X - points[j].X) / 2))) {
                        result ++;
                    }
                }
            }
        }
        printf("%d\n", result / 2);
    }
    return 0;
}
