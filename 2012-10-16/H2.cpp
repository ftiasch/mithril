#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 200;
const double EPS = 1e-9;

int sign(double x) {
    return x < -EPS ? -1 : x > EPS;
}

int n;
bool graph[N][N];
double matrix[N][N];

int main() {
    scanf("%d", &n);
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < n; ++ i) {
        int k;
        scanf("%d", &k);
        while (k --) {
            int j;
            scanf("%d", &j);
            graph[i][-- j] = true;
        }
    }
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            if (graph[i][j] && graph[j][i]) {
                matrix[i][j] = (double)rand() / RAND_MAX;
                matrix[j][i] = -matrix[i][j];
            } 
        }
    }
    for (int i = 0; i < n; ++ i) {
        int j = i;
        while (j < n && sign(matrix[j][i]) == 0) {
            j ++;
        }
        if (j == n) {
            puts("NO");
            return 0;
        }
        for (int k = 0; k < n; ++ k) {
            swap(matrix[i][k], matrix[j][k]);
        }
        for (int j = 0; j < n; ++ j) {
            if (i != j && sign(matrix[j][i]) != 0) {
                double c = matrix[j][i] / matrix[i][i];
                for (int k = 0; k < n; ++ k) {
                    matrix[j][k] -= matrix[i][k] * c;
                }
            }
        }
    }
    puts("YES");
    return 0;
}
