#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <queue>
#include <utility>
#include <queue>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 25000;
const int M = 50000;
const int C = 1000;

int n, m, cc, a[M], b[M], c[M], dist[N], people[C];
std::vector <std::pair <int, int> > graph[N];

const int V = N + 2;
const int E = (M * 2 + C) * 2;

int first_edge[V], edge_count, to[E], capacity[E], next_edge[E];

void _add_edge(int u, int v, int w) {
	to[edge_count] = v;
	capacity[edge_count] = w;
	next_edge[edge_count] = first_edge[u];
	first_edge[u] = edge_count ++;
}

void add_edge(int a, int b, int c) {
	_add_edge(a, b, c);
	_add_edge(b, a, 0);
}

int level[V];

bool bfs(int source, int target) {
	std::queue <int> queue;
	memset(level, -1, sizeof(level));
	level[source] = 0;
	queue.push(source);
	while (!queue.empty() && level[target] == -1) {
		int u = queue.front();
		queue.pop();
		for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
			if (capacity[iter] > 0 && level[to[iter]] == -1) {
				level[to[iter]] = iter;
				queue.push(to[iter]);
			}
		}
	}
	if (level[target] == -1) {
		return false;
	}
	for (int u = target; u != source; u = to[level[u] ^ 1]) {
		capacity[level[u]] --;
		capacity[level[u] ^ 1] ++;
	}
	return true;
}

int main() {
	scanf("%d%d%d", &n, &m, &cc);
	for (int i = 0; i < m; ++ i) {
		scanf("%d%d%d", a + i, b + i, c + i);
		a[i] --, b[i] --;
		graph[a[i]].push_back(std::make_pair(b[i], c[i]));
		graph[b[i]].push_back(std::make_pair(a[i], c[i]));
	}
	for (int i = 0; i < cc; ++ i) {
		scanf("%d", people + i);
		people[i] --;
	}
	std::fill(dist, dist + n, INT_MAX);
	dist[0] = 0;
	std::priority_queue <std::pair <int, int> > heap;
	heap.push(std::make_pair(0, 0));
	while (!heap.empty()) {
		int u = heap.top().second;
		int now = -heap.top().first;
		heap.pop();
		if (now != dist[u]) {
			continue;
		}
		foreach (iter, graph[u]) {
			if (dist[u] + iter->second < dist[iter->first]) {
				dist[iter->first] = dist[u] + iter->second;
				int v = iter->first;
				heap.push(std::make_pair(-dist[v], v));
			}
		}
	}
	int answer = 0;
	for (int i = 0; i < cc; ++ i) {
		if (people[i] != -1) {
			edge_count = 0;
			memset(first_edge, -1, sizeof(first_edge));
			for (int k = 0; k < m; ++ k) {
				if (dist[a[k]] + c[k] == dist[b[k]]) {
					add_edge(b[k], a[k], 1);
				}
				if (dist[b[k]] + c[k] == dist[a[k]]) {
					add_edge(a[k], b[k], 1);
				}
			}
			int source = n;
			int now_dist = dist[people[i]];
			for (int j = 0; j < cc; ++ j) {
				if (people[j] != -1 && dist[people[j]] == now_dist) {
					add_edge(source, people[j], 1);
					people[j] = -1;
				}
			}
			while (bfs(source, 0)) {
				answer ++;
			}
		}
	}
	printf("%d\n", answer);
	return 0;
}
