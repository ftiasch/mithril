#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
using namespace std;

const long long limit = (1LLU << 63) - 1;

bool isPrime(int n)
{
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return n >= 2;
}

int prime[64], primes;

int num[64];

long long get(long long a, long long p)
{
	long long ret = 0;
	while (a /= p) {
		ret += a;
	}
	return ret;
}

map<long long,long long> M;

void add(const vector<int> &f, long long val)
{
	long long res = 1;
	long long left = limit;
	for (int i = 0; i < 64; i++) {
		long long num = 0;
		for (int j = 0; j < f.size(); j++) {
			if (f[j] > 0) {
				num += get(f[j], prime[i]);
			} else {
				num -= get(-f[j], prime[i]);
			}
		}
		assert(num >= 0);
		for (int j = 0; j < num; j++) {
			res *= prime[i];
			left /= prime[i];
		}
	}
	if (left > 0) {
		if (M.count(res)) {
			M[res] = min(M[res], val);
		} else {
			M[res] = val;
		}
	}
}

void dfs(int pos, long long left, long long mul)
{
	if (left == 0) {
		return;
	}
	if (pos == 64) {
		vector<int> f;
		int sum = 0;
		for (int i = 0; i < 64; i++) {
			if (num[i] > 1) {
				f.push_back(-num[i]);
			}
			sum += num[i];
		}
		f.push_back(sum);
		add(f, mul);
		return;
	}
	for (int i = 0; left && (pos == 0 || i <= num[pos - 1]); i++) {
		num[pos] = i;
		dfs(pos + 1, left, mul);
		left /= prime[pos];
		mul *= prime[pos];
	}
}

int main()
{
	primes = 0;
	for (int i = 2; primes < 64; i ++) {
		if (isPrime(i)) {
			prime[primes ++] = i;
		}
	}
	dfs(0, limit, 1);
	M[1] = 2;
	long long input;
	while (cin >> input) {
		if (M.count(input)) {
			cout << input << " " << M[input] << endl;
		} else {
			cout << input << " Impossible" << endl;
		}
	}
}
