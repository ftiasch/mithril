#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

long long solveBF(int lo, int hi)
{
	long long ret = 0;
	for (int a = lo; a <= hi; a++) {
		for (int b = a; b <= hi; b++) {
			for (int c = b; c <= hi; c++) {
				if (a + b > c) {
					ret ++;
				}
			}
		}
	}
	return ret;
}

inline long long consum(int a, int b)
{
	if (a > b) {
		swap(a, b);
	}
	return (long long)(a + b) * (b - a + 1) / 2;
}

long long solve(int lo, int hi)
{
	long long ret = 0;
	for (int c = lo; c <= hi; c++) {
		int mid = (c + 1) / 2;
		if (lo <= mid) {
			ret += consum(lo, mid);
		}
		int left = max(lo, mid + 1);
		if (left <= c) {
			ret += consum(c + 1 - left, c + 1 - c);
		}
	}
	return ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T --) {
		int lo, hi;
		scanf("%d%d", &lo, &hi);
		if (lo > hi) {
			swap(lo, hi);
		}
		cout << solve(lo, hi) << endl;
	}
}
