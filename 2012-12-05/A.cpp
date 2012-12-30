#include <cctype>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int get_value(char c) {
	if ('0' <= c && c <= '9') {
		return c - '0';
	}
	if ('A' <= c && c <= 'F') {
		return 10 + c - 'A';
	}
	assert(false);
}

char get_symbol(int n) {
	if (n < 10) {
		return '0' + n;
	}
	if (n < 16) {
		return 'A' + n - 10;
	}
	assert(false);
}

int to_dec(string s, int b) {
	int ret = 0;
	for (int i = 0; i < (int)s.size(); ++ i) {
		int v = get_value(s[i]);
		if (v >= b) {
			return -1;
		}
		ret = ret * b + v;
	}
	return ret;
}

string from_dec(int n, int b) {
	if (n == 0) {
		return "0";
	}
	string ret;
	while (n) {
		ret = string(1, get_symbol(n % b)) + ret;
		n /= b;
	}
	return ret;
}

int main() {
	int test_count;
	cin >> test_count;
	while (test_count --) {
		string a, b;
		cin >> a >> b;
		string answer;
		for (int base = 3; base <= 16; ++ base) {
//printf("base %d\n", base);
			int value_a = to_dec(a, base);
			int value_b = to_dec(b, base);
//printf("%d %d\n", value_a, value_b);
			if (value_a != -1 && value_b != -1) {
				string c_hex = from_dec(value_a + value_b, 16);
				int counter = 0;
				for (int i = 0; i < (int)c_hex.size(); ++ i) {
					if ('A' <= c_hex[i] && c_hex[i] <= 'F') {
						counter ++;
					}
				}
				if (counter & 1) {
					string c_dec = from_dec(value_a + value_b, 10);
					if (answer.empty() || c_dec < answer) {
						answer = c_dec;
					}
				}
			}
		}
		cout << answer << endl;
	}
	return 0;
}

