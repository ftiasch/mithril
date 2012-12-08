#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 30000;

int n, m, depth[N], parent[N];
std::vector <int> adjacent[N];

void dfs(int p, int u) {
	parent[u] = p;
	depth[u] = p == -1 ? 0 : depth[p] + 1;
	foreach (iter, adjacent[u]) {
		if (*iter != p) {
			dfs(u, *iter);
		}
	}
}

int left[N];

void cover(int u, int d) {
	if (d <= m && d < left[u]) {
		left[u] = d;
		foreach (iter, adjacent[u]) {
			cover(*iter, d + 1);
		}
	}
}

int main() {
	int test_count;
	scanf("%d", &test_count);
	while (test_count --) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++ i) {
			adjacent[i].clear();
		}
		for (int i = 0; i < n - 1; ++ i) {
			int a, b;
			scanf("%d%d", &a, &b);
			a --, b --;
			adjacent[a].push_back(b);
			adjacent[b].push_back(a);
		}
		dfs(-1, 0);
		std::vector <std::pair <int, int> > orders;
		for (int i = 0; i < n; ++ i) {
			orders.push_back(std::make_pair(depth[i], i));
		}
		std::sort(orders.begin(), orders.end(), std::greater <std::pair <int, int> >());
		for (int i = 0; i < n; ++ i) {
			left[i] = INT_MAX;
		}
		int answer = 0;
		foreach (iter, orders) {
			int u = iter->second;
			if (left[u] == INT_MAX) {
				for (int _ = 0; _ < m && parent[u] != -1; ++ _) {
					u = parent[u];
				}
				answer ++;
				cover(u, 0);
			}
		}
		printf("%d\n", answer);
	}
	return 0;
}

