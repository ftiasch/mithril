#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

#define SIZE(v) (int)(v).size()
#define ALL(v) (v).begin(), (v).end()

const int N = 20;

int n;
long long answer[N];
std::vector <long long> sums;

void generate(int i, int count, long long sum) {
    if (i < n) {
        generate(i + 1, count, sum);
        generate(i + 1, count - 1, sum - answer[i]);
        generate(i + 1, count + 1, sum + answer[i]);
    } else {
        if (count == 1 && sum >= 0) {
            sums.push_back(sum);
        }
    }
}

int main() {
    answer[0] = 1;
    answer[1] = 2;
    n = 2;
    while (n < N) {
        sums.clear();
        sums.push_back(0LL);
        generate(0, 0, 0LL);
        std::sort(ALL(sums));
        sums.erase(std::unique(ALL(sums)), sums.end());
        answer[n] = 0;
        while (answer[n] < SIZE(sums) && answer[n] == sums[answer[n]]) {
            answer[n] ++;
        }
        n ++;
    }
    for (int i = 0; i < N; ++ i) {
        printf("%lld, ", answer[i]);
    }
    puts("");
    return 0;
}
