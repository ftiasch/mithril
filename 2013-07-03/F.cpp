#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>

const int N = 1000000;

int n, k, a[N];

bool check(int limit) {
	int left = 0;
	for (int i = 0; i < 2 * k * n; ++ i) {
		if (i + 1 < 2 * k * n && a[i + 1] - a[i] <= limit) {
			left ++;
			if (left == n) {
				return true;
			}
			i ++;
		}
		if (2 * k * left < i + 1) {
			return false;
		}
	}
	return true;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < 2 * k * n; ++ i) {
		scanf("%d", a + i);
	}
	std::sort(a, a + n * 2 * k);
	int low = 0;
	int high = 1000000000;
	while (low < high) {
		int middle = low + high >> 1;
		if (check(middle)) {
			high = middle;
		} else {
			low = middle + 1;
		}
	}
	printf("%d\n", high);
	return 0;
}
