#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int N = 500;
const int INF = 1000000000;

int n, a[N];
bool perm[N][N];
int count[N + 1], f[N][N], g[N + 1];
short cost[N][N][N];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
	}
	memset(cost, 0, sizeof(cost));
	for (int i = 0; i < n; ++ i) {
		int min = INT_MAX;
		for (int j = i; j < n; ++ j) {
			min = std::min(min, a[j]);
			int now = 0;
			for (int k = j + 1; k < n; ++ k) {
				if (a[k] > min) {
					now ++;
				}
				cost[i][j][k] += now;
			}
		}
	}
	for (int i = n - 1; i >= 0; -- i) {
		int min = INT_MAX;
		for (int j = i; j >= 0; -- j) {
			min = std::min(min, a[j]);
			int now = 0;
			for (int k = j - 1; k >= 0; -- k) {
				if (a[k] > min) {
					now ++;
				}
				cost[k][j - 1][i] += now;
			}
		}
	}
	memset(perm, 0, sizeof(perm));
	for (int i = 0; i < n; ++ i) {
		memset(count, 0, sizeof(count));
		int max = INT_MIN;
		for (int j = i; j < n; ++ j) {
			count[a[j]] ++;
			max = std::max(max, a[j]);
			bool &res = perm[i][j];
			res = true;
			for (int k = 1; k <= max && res; ++ k) {
				res &= count[k] == 1;
			}
		}
	}
	for (int i = n - 1; i >= 0; -- i) {
		f[i][i] = 0;
		for (int j = i + 1; j < n; ++ j) {
			f[i][j] = INF;
			for (int k = i; k < j; ++ k) {
				f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j] + cost[i][k][j]);
			}
		}
	}
	g[n] = 0;
	for (int i = n - 1; i >= 0; -- i) {
		g[i] = INF;
		for (int j = i; j < n; ++ j) {
			if (perm[i][j]) {
				g[i] = std::min(g[i], g[j + 1] + f[i][j]);
			}
		}
	}
	if (g[0] < INF) {
		printf("%d\n", g[0]);
	} else {
		puts("impossible");
	}
	return 0;
}
