#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using std::make_pair;

const int N = 50000;

int n, text[N], count[N], rank[N], array[N], newRank[N][2], newArray[N];

int main() {
	while (scanf("%d", &n) == 1 && n) {
		std::vector <std::pair <int, int> > orders;
		for (int i = 0; i < n; ++ i) {
			scanf("%d", text + i);
			orders.push_back(make_pair(text[i], i));
		}
		std::sort(orders.begin(), orders.end());
		for (int i = 0; i < n; ++ i) {
			array[i] = orders[i].second;
		}
		for (int i = 0; i < n; ++ i) {
			rank[array[i]] = i ? rank[array[i - 1]] + (text[array[i]] != text[array[i - 1]]) : 0;
		}
		for (int length = 1; length < n; length <<= 1) {
			for (int i = 0; i < n; ++ i) {
				newRank[i][0] = rank[i];
				newRank[i][1] = rank[(i + length) % n];
			}
			memset(count, 0, sizeof(count));
			for (int i = 0; i < n; ++ i) {
				count[newRank[i][1]] ++;
			}
			for (int i = 1; i < n; ++ i) {
				count[i] += count[i - 1];
			}
			for (int i = n - 1; i >= 0; -- i) {
				newArray[-- count[newRank[i][1]]] = i;
			}
			memset(count, 0, sizeof(count));
			for (int i = 0; i < n; ++ i) {
				count[newRank[i][0]] ++;
			}
			for (int i = 1; i < n; ++ i) {
				count[i] += count[i - 1];
			}
			for (int i = n - 1; i >= 0; -- i) {
				array[-- count[newRank[newArray[i]][0]]] = newArray[i];
			}
			for (int i = 0; i < n; ++ i) {
				rank[array[i]] = i ? rank[array[i - 1]] + (newRank[array[i]][0] != newRank[array[i - 1]][0] || newRank[array[i]][1] != newRank[array[i - 1]][1]) : 0;
			}
		}
//for (int i = 0; i < n; ++ i) { for (int j = 0; j < n; ++ j) { printf("%d, ", text[(array[i] + j) % n]); } puts(""); }
		for (int i = 0; i < n; ++ i) {
			rank[array[i]] = i;
		}
		long long answer = 0;
		for (int i = 0, current = 0; i < n; ++ i) {
			if (rank[i]) {
				int j = array[rank[i] - 1];
				while (current < n && text[(i + current) % n] == text[(j + current) % n]) {
					current ++;
				}
//printf("-- %d\n", answer);
				answer += current;
				if (current) {
					current --;
				}
			}
		}
		std::cout << answer << std::endl;
	}
	return 0;
}
