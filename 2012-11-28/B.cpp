#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

const int maxn = 2048;

int n;
int coin[55];

void update(int &a, int v)
{
	if (a < 0 || a > v) {
		a = v;
	}
}

int *checkPossible()
{
	static int opt[maxn];
	memset(opt, -1, sizeof(opt));
	opt[0] = 0;
	for (int i = 0; i < n; i++) {
		int c = coin[i];
		for (int j = c; j < maxn; j++) {
			if (opt[j - c] >= 0) {
				update(opt[j], opt[j - c] + 1);
			}
		}
	}
	return opt;
}

int *checkGreedy()
{
	static int opt[maxn];
	memset(opt, -1, sizeof(opt));
	opt[0] = 0;
	for (int j = 1; j < maxn; j++) {
		int maxc = 0;
		for (int i = 0; i < n; i++) {
			if (coin[i] <= j) {
				maxc = max(maxc, coin[i]);
			}
		}
		if (maxc > 0 && opt[j - maxc] >= 0) {
			opt[j] = opt[j - maxc] + 1;
		}
	}
	return opt;
}

int main()
{
	int cas = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) {
			scanf("%d", coin + i);
		}
		int *best = checkPossible();
		int *greedy = checkGreedy();
		bool isPossible = true;
		bool isGreedyOkay = true;
		for (int i = 0; i < maxn; i++) {
			if (best[i] < 0) {
				isPossible = false;
			}
			if (best[i] != greedy[i]) {
				isGreedyOkay = false;
			}
		}
		if (!isPossible) {
			printf("Case #%d: Cannot pay some amount\n", ++cas);
		} else if (!isGreedyOkay) {
			printf("Case #%d: Cannot use greedy algorithm\n", ++cas);
		} else {
			printf("Case #%d: OK\n", ++cas);
		}
	}
}
