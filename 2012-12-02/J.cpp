#include <cstdio>
#include <cstring>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 1024;

int parent[maxn];

int findRoot(int a)
{
	return parent[a] < 0 ? a : parent[a] = findRoot(parent[a]);
}

bool mergeComp(int a, int b)
{
	a = findRoot(a);
	b = findRoot(b);
	if (a == b) {
		return false;
	}
	parent[a] = b;
	return true;
}

int firstEdge[maxn], nextEdge[maxn], removedEdge[maxn];
int from[maxn], dest[maxn];
int n, m;

vector<int> findCycle()
{
	memset(firstEdge, -1, sizeof(firstEdge));
	for (int i = 0; i < m; i++) {
		if (removedEdge[i]) {
			continue;
		}
		from[i] = findRoot(from[i]);
		dest[i] = findRoot(dest[i]);
		nextEdge[i] = firstEdge[from[i]];
		firstEdge[from[i]] = i;
	}
	for (int removal = 0; removal < m; removal ++) {
		if (removedEdge[removal]) {
			continue;
		}
		queue<int> Q;
		vector<int> prev(n, -1);
		Q.push(dest[removal]);
		prev[dest[removal]] = -2;
		while (!Q.empty()) {
			int p = Q.front();
			Q.pop();
			for (int e = firstEdge[p]; e >= 0; e = nextEdge[e]) {
				int q = dest[e];
				if (prev[q] == -1) {
					prev[q] = e;
					Q.push(q);
				}
			}
		}
		if (prev[from[removal]] != -1) {
			int p = removal;
			vector<int> ret;
			while (p >= 0) {
				ret.push_back(p);
				p = prev[from[p]];
			}
			reverse(ret.begin(), ret.end());
			return ret;
		}
	}
	assert(false);
}

struct Wheel
{
	int vertex;
	vector<int> edge;
	vector<Wheel> wheel;

	Wheel(int v = -1) : vertex(v) {}

	void output() const {
		if (vertex >= 0) {
			printf("vertex %d\n", vertex + 1);
		} else {
			printf("wheel %d\n", edge.size());
			for (int i = 0; i < edge.size(); i++) {
				wheel[i].output();
				printf("edge %d\n", edge[i] + 1);
			}
		}
	}
};

Wheel ans[maxn];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", from + i, dest + i);
		from[i] --;
		dest[i] --;
	}
	memset(removedEdge, false, sizeof(removedEdge));
	memset(parent, -1, sizeof(parent));
	for (int i = 0; i < n; i++) {
		ans[i] = Wheel(i);
	}
	int leftEdges = m;
	while (leftEdges > 0) {
		vector<int> cycle = findCycle();
		leftEdges -= cycle.size();
		Wheel w(-1);
		w.edge = cycle;
		for (int i = 0; i < cycle.size(); i++) {
			w.wheel.push_back(ans[from[cycle[i]]]);
			removedEdge[cycle[i]] = true;
		}
		for (int i = 1; i < cycle.size(); i++) {
			mergeComp(from[cycle[0]], from[cycle[i]]);
		}
		ans[findRoot(from[cycle[0]])] = w;
	}
	ans[findRoot(0)].output();
}
