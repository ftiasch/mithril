#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int N = 100000;

int n, m, a[N];
vector <int> values;

int get_id(int a) {
	return lower_bound(values.begin(), values.end(), a) - values.begin();
}

pair <int, int> optimum[N], prefix[N], suffix[N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
		values.push_back(a[i]);
	}
	sort(values.begin(), values.end());
	values.erase(unique(values.begin(), values.end()), values.end());
	for (int i = n - 1; i >= 0; -- i) {
		optimum[i] = make_pair(0, i);
		for (int k = upper_bound(values.begin(), values.end(), a[i] - m) - values.begin() - 1; k >= 0; k -= ~k & k + 1) {
			optimum[i] = max(optimum[i], prefix[k]);
		}
		for (int k = lower_bound(values.begin(), values.end(), a[i] + m) - values.begin(); k < n; k += ~k & k + 1) {
			optimum[i] = max(optimum[i], suffix[k]);
		}
		optimum[i].first ++;
		pair <int, int> new_pair = make_pair(optimum[i].first, i);
		int id = get_id(a[i]);
		for (int k = id; k < n; k += ~k & k + 1) {
			prefix[k] = max(prefix[k], new_pair);
		}
		for (int k = id; k >= 0; k -= ~k & k + 1) {
			suffix[k] = max(suffix[k], new_pair);
		}
	}
	int start = max_element(optimum, optimum + n) - optimum;
	printf("%d\n", optimum[start].first);
	while (optimum[start].second != start) {
		printf("%d ", a[start]);
		start = optimum[start].second;
	}
	printf("%d\n", a[start]);
	return 0;
}
