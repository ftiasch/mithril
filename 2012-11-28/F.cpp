#include <ctime>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 100;
const int INF = 1000000000;

int n, m, limit;
int graph[N][N];

const int V = (N << 1) + 2;

int capacity[V][V], level[V];

bool bfs(int source, int target) {
	memset(level, -1, sizeof(level));
	queue <int> nodes;
	nodes.push(target);
	level[target] = 0;
	while (!nodes.empty() && level[source] == -1) {
		int u = nodes.front();
		nodes.pop();
		for (int i = 0; i <= target; ++ i) {
			if (capacity[i][u] > 0 && level[i] == -1) {
				level[i] = level[u] + 1;
				nodes.push(i);
			}
		}
	}
	return level[source] != -1;
}

int dfs(int source, int target, int limit) {
	if (source == target) {
		return limit;
	}
	int delta = 0;
	for (int i = 0; i <= target; ++ i) {
		if (capacity[source][i] > 0 && level[source] == level[i] + 1) {
			int ret = dfs(i, target, min(limit - delta, capacity[source][i]));
			capacity[source][i] -= ret;
			capacity[i][source] += ret;
			delta += ret;
			if (delta == limit) {
				break;
			}
		}
	}
	return delta;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &limit) == 3) {
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				graph[i][j] = i == j ? 0 : INF;
			}
		}
		for (int i = 0; i < m; ++ i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a --, b --;
			graph[a][b] = graph[b][a] = min(graph[a][b], c);
		}
		for (int k = 0; k < n; ++ k) {
			for (int i = 0; i < n; ++ i) {
				for (int j = 0; j < n; ++ j) {
					graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
				}
			}
		}
		memset(capacity, 0, sizeof(capacity));
		int source = n << 1;
		int target = source + 1;
		for (int i = 0; i < n; ++ i) {
			scanf("%d", &capacity[source][i]);
		}
		for (int i = 0; i < n; ++ i) {
			scanf("%d", &capacity[n + i][target]);
		}
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (graph[i][j] < limit) {
					capacity[i][n + j] = INF;
				}
			}
		}
		int answer = 0;
		while (bfs(source, target)) {
			answer += dfs(source, target, INF);
		}
		printf("%d\n", answer);
	}
	return 0;
}
