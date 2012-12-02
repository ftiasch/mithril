#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef long long BigInt;

const int maxn = 32;

int n;
bool seen[maxn][maxn][maxn][2][2];
BigInt memo[maxn][maxn][maxn][2][2];

BigInt go(int dep, int l, int r, bool fl, bool fr)
{
	if (l >= r) {
		return 0;
	}
	BigInt &ret = memo[dep][l][r][fl][fr];
	if (seen[dep][l][r][fl][fr]) {
		return ret;
	}
	seen[dep][l][r][fl][fr] = true;
	if (dep == n - 1) {
		return ret = 1;
	}
	ret = 0;
	for (int x = 0; x <= dep + 1; x++) {
		if (x <= l) {
			if (fl) {
				ret += go(dep + 1, x, r + (r >= x ? 1 : 0), fl, fr);
			}
		} else {
			ret += go(dep + 1, x, r + (r >= x ? 1 : 0), false, fr);
		}
		if (x <= r) {
			ret += go(dep + 1, l + (l >= x ? 1 : 0), x, fl, false);
		} else {
			if (fr) {
				ret += go(dep + 1, l + (l >= x ? 1 : 0), x, fl, fr);
			}
		}
	}
	return ret;
}

BigInt solve(int n)
{
	::n = n;
	memset(seen, false, sizeof(seen));
	return go(1, 0, 1, true, true);
}

int main()
{
	int n;
	while (cin >> n) {
		cout << solve(n) << endl;
	}
}

