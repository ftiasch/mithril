#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const long long LIMIT = 4LL * 1000000000LL;
const int maxn = 1 << 18;

int mobius[maxn];

long long get(long long n, int d)
{
	long long ret = 0;
	for (int i = 2; ; i++) {
		if (mobius[i] == 0) {
			continue;
		}
		long long left = n;
		for (int j = 0; j < d; j++) {
			left /= i;
		}
		if (left == 0) {
			break;
		}
		ret += mobius[i] * left;
	}
	return ret;
}

int main()
{
	for (int i = 2; i < maxn; i++) {
		int delta = 1 - mobius[i];
		mobius[i] = delta;
		for (int j = i * 2; j < maxn; j += i) {
			mobius[j] += delta;
		}
	}
	int tests;
	cin >> tests;
	while (tests --) {
		int d, n;
		cin >> d >> n;
		long long lo = 1, hi = LIMIT;
		while (lo < hi) {
			long long mid = (lo + hi) / 2;
			if (get(mid, d) >= n) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
		cout << lo << endl;
	}
}

