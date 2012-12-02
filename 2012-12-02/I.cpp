#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

long long d, b, t, p;

long long udivide(long long p, long long q)
{
	return (p + q - 1) / q;
}

long long solve(long long s)
{
	return udivide(t * (b - d), s);
}

int main()
{
	while (cin >> d >> b >> t >> p) {
		long long lo = 1, hi = d * p; 
		long long target = solve(hi);
		while (lo < hi) {
			long long mid = lo + hi >> 1;
			if (solve(mid) == target) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
		cout << lo << endl;
	}
}
