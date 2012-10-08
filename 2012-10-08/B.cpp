#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000;

int n;
deque <int> stacks[N];
int counter[N];
long long cost[N], income[N];

void find(int k) {
    counter[k] = cost[k] = income[k] = 0;
    while (income[k] <= 0 && counter[k] < (int)stacks[k].size()) {
        income[k] += stacks[k][counter[k] ++];
        cost[k] = min(cost[k], income[k]);
    }
}

int main() {
    freopen("cards.in", "r", stdin);
    freopen("cards.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        int k;
        scanf("%d", &k);
        while (k --) {
            int x;
            scanf("%d", &x);
            stacks[i].push_back(x);
        }
    }
    priority_queue<pair <int, int> > heap;
    for (int i = 0; i < n; ++ i) {
        find(i);
        if (income[i] > 0) {
            heap.push(make_pair(cost[i], i));
        }
    }
    long long score = 0;
    while (!heap.empty()) {
        int k = heap.top().second;
        heap.pop();
        if (score + cost[k] < 0) {
            break;
        }
        score += income[k];
        while (counter[k] --) {
            stacks[k].pop_front();
        }
        find(k);
        if (income[k] > 0) {
            heap.push(make_pair(cost[k], k));
        }
    }
    cout << score << endl;
    return 0;
}
