#include <cassert>
#include <cctype>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int validate(int n) {
	return 0 <= n && n <= 9999;
}

int r_1, r_2;
char r_3;

void apply() {
	if (r_3 == '+') {
		r_1 = r_1 + r_2;
	} else if (r_3 == '-') {
		r_1 = r_1 - r_2;
	} else if (r_3 == '*') {
		r_1 = r_1 * r_2;
	} else if (r_3 == ' ') {
		r_1 = r_2;
	} else {
		assert(false);
	}
	r_2 = 0;
}

int evaluate(string expression) {
	r_1 = r_2 = 0;
	r_3 = ' ';
	for (int i = 0; i < (int)expression.size(); ++ i) {
		if (isdigit(expression[i])) {
			r_2 = r_2 * 10 + expression[i] - '0';
		} else if (expression[i] == '=') {
			apply();
		} else {
			apply();
			r_3 = expression[i];
		}
		if (!validate(r_1) || !validate(r_2)) {
			return -1;
		}
	}
	return r_1;
}

int main() {
	string expression;
	while (cin >> expression) {
		int ret = evaluate(expression);
		if (ret == -1) {
			puts("E");
		} else {
			printf("%d\n", ret);
		}
	}
	return 0;
}
