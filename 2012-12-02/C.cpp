#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 1000;
const int M = 20000;
const int MAX_COUNT = 100;
const double INF = 1e8;
const double EPS = 1e-8;

int n, m;
bool in_path[M];

int edge_count, first_edge[N], to[M << 1], length[M << 1], next_edge[M << 1];

void add_edge(int u, int v, int w) {
	to[edge_count] = v;
	length[edge_count] = w;
	next_edge[edge_count] = first_edge[u];
	first_edge[u] = edge_count ++;
}

double delta;

double get_length(int id) {
	if (in_path[id >> 1]) {
		return max(length[id] - delta, 1.0);
	}
	return length[id] + delta;
}

int signum(double x) {
	return x < -EPS ? -1 : x > EPS;
}

double dist[N];

bool check() {
	for (int i = 0; i < n; ++ i) {
		dist[i] = INF;
	}
	dist[0] = 0;
	priority_queue <pair <double, int> > heap;
	heap.push(make_pair(0, 0));
	while (!heap.empty()) {
		pair <double, int> ret = heap.top();
		heap.pop();
		int u = ret.second;
		if (signum(-ret.first - dist[u]) > 0) {
			continue;
		}
		for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
			int v = to[iter];
			if (dist[u] + get_length(iter) < dist[v]) {
				dist[v] = dist[u] + get_length(iter);
				heap.push(make_pair(-dist[v], v));
			}
		}
	}
	double difference = dist[n - 1];
	for (int i = 0; i < m; ++ i) {
		if (in_path[i]) {
			difference -= get_length(i << 1);
		}
	}
	return signum(difference) >= 0;
}

int main() {
	scanf("%d%d", &n, &m);
	edge_count = 0;
	memset(first_edge, -1, sizeof(first_edge));
	for (int i = 0; i < m; ++ i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a --;
		b --;
		add_edge(a, b, c);
		add_edge(b, a, c);
	}
	memset(in_path, 0, sizeof(in_path));
	{
		int k;
		scanf("%d", &k);
		while (k --) {
			int id;
			scanf("%d", &id);
			in_path[-- id] = true;
		}
	}
	double low = 0;
	double high = 1e4;
	for (int _ = 0; _ < MAX_COUNT; ++ _) {
		double middle = (low + high) / 2.0;
		::delta = middle;
		if (check()) {
			high = middle;
		} else {
			low = middle;
		}
	}
	double answer = (low + high) / 2.0;
	printf("%.8f\n", answer);
	::delta = answer;
	for (int i = 0; i < m; ++ i) {
		printf("%.8f%c", get_length(i << 1), i == m - 1 ? '\n': ' ');
	}
	return 0;
}
