#include <cstdio>
#include <cstring>
#include <utility>
#include <stack>

const int N = 200000;

int n, a[N];
double answer[N];
long long sum[N + 1];

double average(int i, int j) {
    return (double)(sum[i] - sum[j + 1]) / (j - i + 1);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    sum[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        sum[i] = sum[i + 1] + a[i];
    }
    std::stack <std::pair <int, int> > stack;
    for (int i = 0; i < n; ++ i) {
        int from = i;
        while (!stack.empty() && average(stack.top().first, stack.top().second) > average(from, i)) {
            from = stack.top().first;
            stack.pop();
        }
        stack.push(std::make_pair(from, i));
    }
    while (!stack.empty()) {
        double a = average(stack.top().first, stack.top().second);
        for (int i = stack.top().first; i <= stack.top().second; ++ i) {
            answer[i] = a;
        }
        stack.pop();
    }
    for (int i = 0; i < n; ++ i) {
        printf("%.8f%c", answer[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
