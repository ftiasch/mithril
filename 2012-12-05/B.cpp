#include <cstdio>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

long long m;
int n;

typedef pair <int, int> Pair;
vector <Pair> offers;

bool by_ratio(const Pair &a, const Pair &b) {
	return a.second * b.first < b.second * a.first;
}

long long answer;

long long div2(long long a, long long b) {
	return (a + b - 1) / b;
}

void enumerate(int i, long long left, long long cost) {
	if (i < n) {
		for (int k = 0; k <= 100; ++ k) {
			enumerate(i + 1, left - offers[i].first * k, cost + offers[i].second * k);
		}
	} else {
		answer = min(answer, cost + div2(max(left, 0LL), offers[0].first) * offers[0].second);
	}
}

int main( ) {
	int test_count;
	cin >> test_count;
	while (test_count --) {
		cin >> m >> n;
		offers.clear();
		for (int i = 0; i < n; ++ i) {
			int a, p;
			cin >> a >> p;
			offers.push_back(make_pair(a, p));
		}
		sort(offers.begin(), offers.end(), by_ratio);
		answer = 1000000000000000000LL;
		enumerate(1, m, 0);
		cout << answer << endl;
	}
	return 0;
}

