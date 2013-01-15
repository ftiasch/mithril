#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>

using namespace std;

int n, m, k, seeds[1000 + 1], a, b, c;
deque <pair <int, int> > queue;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    scanf("%d%d%d", &a, &b, &c);
    for (int i = 1; i <= k; ++ i) {
        scanf("%d", seeds + i);
    }
    long long answer = 0;
    int pre, now;
    for (int i = 1; i <= n; ++ i) {
        int new_value = i <= k ? seeds[i] : a * pre + b * now + c;
        while (!queue.empty() && queue.back().second >= new_value) {
            queue.pop_back();
        }
        queue.push_back(make_pair(i, new_value));
        while (i - queue.front().first >= m) {
            queue.pop_front();
        }
        if (i >= m) {
            answer += queue.front().second;
        }
        pre = now, now = new_value;
        if (i == k) {
            pre = seeds[i - 1], now = seeds[i];
        } 
    }
    std::cout << answer << std::endl;
    return 0;
}
