#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

const double EPS = 1e-6;

int n;
double need, fast_cost, slow_cost;
int fast_time, slow_time;

const int N = 202;
const int M = 5 * N + 1 << 1;

int edge_count, first_edge[N], to[M], capacity[M], next_edge[M];
double cost[M];

void _add_edge(int u, int v, int ca, double co) {
	to[edge_count] = v;
	capacity[edge_count] = ca;
	cost[edge_count] = co;
	next_edge[edge_count] = first_edge[u];
	first_edge[u] = edge_count ++;
}

void add_edge(int u, int v, int ca, double co) {
	_add_edge(u, v, ca, co);
	_add_edge(v, u, 0, -co);
}

bool visit[N];
int from[N];
double distance[N];

int main() {
	int test_count;
	scanf("%d", &test_count);
	while (test_count --) {
		scanf("%d%lf%lf%lf%d%d", &n, &need, &fast_cost, &slow_cost, &fast_time, &slow_time);
		edge_count = 0;
		memset(first_edge, -1, sizeof(first_edge));
		int source = n << 1;
		int target = source + 1;
		add_edge(source, 0, INT_MAX, need);
		for (int i = 0; i + 1 < n; ++ i) {
			add_edge(i, i + 1, INT_MAX, 0);
		}
		for (int i = 0; i < n; ++ i) {
			int r;
			scanf("%d", &r);
			add_edge(i, target, r, 0);
			add_edge(source, n + i, r, 0);
		}
		for (int i = 0; i < n; ++ i) {
			if (i + fast_time < n) {
				add_edge(i + n, i + fast_time, INT_MAX, fast_cost);
			}
			if (i + slow_time < n) {
				add_edge(i + n, i + slow_time, INT_MAX, slow_cost);
			}
		}
		double answer = 0;
		while (true) {
			for (int i = 0; i <= target; ++ i) {
				distance[i] = INT_MAX;
			}
			distance[source] = 0;
			memset(visit, 0, sizeof(visit));
			visit[source] = true;
			std::queue <int> queue;
			queue.push(source);
			while (!queue.empty()) {
				int u = queue.front();
				queue.pop();
				visit[u] = false;
				for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
					if (capacity[iter] > 0 && distance[u] + cost[iter] + EPS < distance[to[iter]]) {
						from[to[iter]] = iter;
						distance[to[iter]] = distance[u] + cost[iter];
						if (!visit[to[iter]]) {
							visit[to[iter]] = true;
							queue.push(to[iter]);
							if (distance[queue.front()] > distance[queue.back()]) {
								std::swap(queue.front(), queue.back());
							}
						}
					}
				}
			}
			if (distance[target] < INT_MAX) {
				int delta = INT_MAX;
				for (int i = target; i != source; i = to[from[i] ^ 1]) {
					delta = std::min(delta, capacity[from[i]]);
				}
				for (int i = target; i != source; i = to[from[i] ^ 1]) {
					answer += delta * cost[from[i]];
					capacity[from[i]] -= delta;
					capacity[from[i] ^ 1] += delta;
				}
			} else {
				break;
			}
		}
		printf("%.2f\n", answer);
	}
	return 0;
}

