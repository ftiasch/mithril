#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int maxn = 100000;

int n, a, b, m;
int supply[maxn], consume[maxn];
int balance[maxn];

int decode(int v)
{
	return v < 0 ? (-v - 1) : (v - 1) + a;
}

int ans[maxn];

void solve(int src, vector<pair<int,int> > *adj, bool flag)
{
	vector<pair<int, int> > prev(n);
	vector<bool> vis(n, false);
	vector<int> Q;
	vis[src] = true;
	Q.push_back(src);
	for (int i = 0; i < Q.size(); i++) {
		int p = Q[i];
		FOR (it, adj[p]) {
			if (!vis[it->first]) {
				vis[it->first] = true;
				prev[it->first] = make_pair(p, it->second);
				Q.push_back(it->first);
			}
		}
	}
	assert(Q.size() == n);
	for (int i = Q.size() - 1; i >= 1; i--) {
		int p = Q[i];
		if (balance[p] > 0) {
			if (flag && p < a) {
				int bot = min(supply[p], balance[p]);
				balance[p] -= bot;
				supply[p] -= bot;
			}
			ans[prev[p].second] += balance[p];
			balance[prev[p].first] += balance[p];
			balance[p] -= balance[p];
		}
	}
}

vector<pair<int,int> > adj[maxn], radj[maxn];

int main()
{
	scanf("%d%d%d", &a, &b, &m);
	int sum = 0;
	for (int i = 0; i < a; i++) {
		scanf("%d", supply + i);
		sum += supply[i];
	}
	for (int i = 0; i < b; i++) {
		scanf("%d", consume + i);
	}
	n = a + b;
	for (int i = 0; i < m; i++) {
		int si, ti;
		scanf("%d%d", &si, &ti);
		si = decode(si), ti = decode(ti);
		adj[si].push_back(make_pair(ti, i));
		radj[ti].push_back(make_pair(si, i));
	}
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i < n; i++) {
		balance[i] = i >= a ? consume[i - a] : 0;
	}
	solve(0, adj, true);
	for (int i = 0; i < n; i++) {
		balance[i] = i < a ? supply[i] : 0;
	}
	solve(0, radj, false);
	puts("YES");
	for (int i = 0; i < m; i++) {
		if (i > 0) {
			putchar(' ');
		}
		printf("%d", ans[i]);
	}
	puts("");
}
