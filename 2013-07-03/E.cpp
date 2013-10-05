#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using std::vector;

const int N = 1000;

int b, s, n;
char buffer[22];

char type[N];
int value[N], next_e[N];

const int M = 13;

int m;

int get_id(int x, int y) {
	return x * m + y;
}

typedef long long LL;

struct Result {
	int first, last;
	LL total;
	vector <LL> count;

	Result() : first(-1), last(-1), total(0), count(m * m, 0) {
	}

	Result &repeat(int n) {
		for (int i = 0; i < m * m; ++ i) {
			count[i] *= n;
		}
		if (first != -1 && last != -1) {
			count[get_id(last, first)] += n - 1;
		}
		total *= n;
		return *this;
	}
};

Result operator + (const Result &a, const Result &b) {
	Result c;
	c.first = a.first != -1 ? a.first : b.first;
	c.last = b.last != -1 ? b.last : a.last;
	c.total = a.total + b.total;
	for (int i = 0; i < m * m; ++ i) {
		c.count[i] = a.count[i] + b.count[i];
	}
	if (a.last != -1 && b.first != -1) {
		c.count[get_id(a.last, b.first)] ++;
	}
	return c;
}

int new_id[M];
LL maximum[1 << M], sum[1 << M];

Result parse(int l, int r) {
	if (l >= r) {
		return Result();
	}
	if (type[l] == 'V') {
		Result ret;
		ret.first = ret.last = new_id[value[l]];
		ret.total = 1;
		return ret + parse(l + 1, r);
	}
	int e = next_e[l];
	return parse(l + 1, e).repeat(value[l]) + parse(e + 1, r);
}

int max_m;

const LL INF = 100000000000000000LL;

LL solve(Result res) {
	sum[0] = 0;
	LL total = 0;
	int all = (1 << m) - 1;
	for (int mask = 1; mask < 1 << m; ++ mask) {
		sum[mask] = 0;
		for (int i = 0; i < m; ++ i) {
			if (mask >> i & 1) {
				for (int j = 0; j < m; ++ j) {
					if (mask >> j & 1) {
						sum[mask] += res.count[get_id(i, j)];
					}
				}
			}
		}
		if (mask == all) {
			total = sum[mask];
		}
		if (__builtin_popcount(mask) > s) {
			sum[mask] = -INF;
		}
	}
	for (int mask = 0; mask < 1 << m; ++ mask) {
		maximum[mask] = -INF;
	}
	maximum[0] = 0;
	for (int i = 1; i < b; ++ i) {
		for (int mask = (1 << m) - 1; mask >= 0; -- mask) {
			for (int sub = mask; sub; sub = (sub - 1) & mask) {
				maximum[mask] = std::max(maximum[mask], maximum[mask ^ sub] + sum[sub]);
			}
		}
	}
	return res.total + 1 + total - maximum[all];
}


int main() {
	scanf("%d%d", &b, &s);
	n = 0;
	while (scanf("%s", buffer) == 1) {
		type[n] = *buffer;
		if (type[n] != 'E') {
			sscanf(buffer + 1, "%d", value + n);
		}
		n ++;
	}
	vector <int> values;
	for (int i = 0; i < n; ++ i) {
		if (type[i] == 'V') {
			values.push_back(value[i]);
		}
	}
	std::sort(values.begin(), values.end());
	values.erase(std::unique(values.begin(), values.end()), values.end());
	max_m = values.size();
	for (int i = 0; i < n; ++ i) {
		if (type[i] == 'V') {
			value[i] = std::lower_bound(values.begin(), values.end(), value[i]) - values.begin();
		}
	}
	std::stack <int> stack;
	for (int i = n - 1; i >= 0; -- i) {
		if (type[i] == 'E') {
			stack.push(i);
		}
		if (type[i] == 'R') {
			next_e[i] = stack.top();
			stack.pop();
		}
	}
//for (int i = 0; i < max_m; ++ i) {
//	new_id[i] = i;
//}
//m = 4;
//Result ret = parse(3, 8);
//printf("%d %d %lld\n", ret.first, ret.last, ret.total);
//for (int i = 0; i < m; ++ i) {
//	for (int j = 0; j < m; ++ j) {
//		printf("%lld ", ret.count[get_id(i, j)]);
//	}
//	puts("");
//}
//return 0;
	if (max_m <= s) {
		m = max_m;
		for (int i = 0; i < max_m; ++ i) {
			new_id[i] = 0;
		}
		std::cout << parse(0, n).total << std::endl;
	} else {
		long long answer = INF;
		for (int mask = 0; mask < 1 << max_m; ++ mask) {
			if (__builtin_popcount(mask) == s) {
//printf("%d\n", mask);
				int new_count = 0;
				memset(new_id, -1, sizeof(new_id));
				m = 0;
				for (int i = 0; i < max_m; ++ i) {
					if (~mask >> i & 1) {
						m ++;
						new_id[i] = new_count ++;
					}
				}
//Result ret = parse(0, n);
//printf("%d %d %lld\n", ret.first, ret.last, ret.total);
//for (int i = 0; i < m; ++ i) {
//	for (int j = 0; j < m; ++ j) {
//		printf("%lld ", ret.count[get_id(i, j)]);
//	}
//	puts("");
//}
				answer = std::min(answer, solve(parse(0, n)));
			}
		}
		std::cout << answer << std::endl;
	}
	return 0;
}
