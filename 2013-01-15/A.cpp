#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>

using std::make_pair;

const int N = 100000;
const int M = 10000;

const int OPENING = 0;
const int CLOSED = 1;

int n, m, weight[M << 1], brackets[N << 1], reverse_map[M << 1];

int encode(int type) {
    return (abs(type) - 1 << 1) | (type < 0);
}

int decode(int type) {
    return ((type >> 1) + 1) * ((type & 1) == OPENING ? 1 : -1);
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d%d", &n, &m);
        std::vector <int> orders;
        for (int i = 0; i < m << 1; ++ i) {
            int type;
            scanf("%d", &type);
            weight[encode(type)] = i;
            reverse_map[i] = encode(type);
        }
        for (int i = 0; i < n << 1; ++ i) {
            int type;
            scanf("%d", &type);
            brackets[i] = encode(type);
        }
        for (int i = 0; i < m; ++ i) {
            orders.push_back(weight[i << 1]);
        }
        std::sort(orders.begin(), orders.end());
        std::stack <int> stack;
        int valid_position = -1;
        int valid_weight = INT_MAX;
        for (int i = 0; i < n << 1; ++ i) {
            int result_weight = INT_MAX;
            // OPENING
            std::vector <int> :: iterator iter = upper_bound(orders.begin(), orders.end(), weight[brackets[i]]);
            if (iter != orders.end() && (int)stack.size() + 1 <= (n << 1) - (i + 1)) {
                result_weight = std::min(result_weight, *iter);
            }
            // CLOSED
            if (!stack.empty() && weight[brackets[i]] < weight[stack.top() ^ 1]) {
                result_weight = std::min(result_weight, weight[stack.top() ^ 1]);
            }
            if (result_weight != INT_MAX) {
//printf("%d -> %d: %d\n", i, decode(reverse_map[brackets[i]]), decode(reverse_map[result_weight]));
                valid_position = i;
                valid_weight = result_weight;
            }
            if ((brackets[i] & 1) == OPENING) {
                stack.push(brackets[i]);
            } else {
                stack.pop();
            }
        }
        int start_position = 0;
        if (valid_position != -1) {
            brackets[valid_position] = reverse_map[valid_weight];
            start_position = valid_position + 1;
        }
        while (!stack.empty()) {
            stack.pop();
        }
        for (int i = 0 ; i < n << 1; ++ i) {
            if (i >= start_position) {
                int valid_weight = INT_MAX;
                if ((int)stack.size() + 1 <= (n << 1) - (i + 1)) {
                    valid_weight = std::min(valid_weight, orders.front());
                }
                if (!stack.empty()) {
                    valid_weight = std::min(valid_weight, weight[stack.top() ^ 1]);
                }
                assert(valid_weight != INT_MAX);
                brackets[i] = reverse_map[valid_weight];
            }
            if ((brackets[i] & 1) == OPENING) {
                stack.push(brackets[i]);
            } else {
                stack.pop();
            }
        }
        for (int i = 0; i < n << 1; ++ i) {
            printf("%d%c", decode(brackets[i]), i == (n << 1) - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
