#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 200000 + 1;

int n, g[N], b[N];
char type[N];


int main() {
    scanf("%d", &n);
    memset(g, 0, sizeof(g));
    memset(b, 0, sizeof(b));
    for (int i = 1; i < n; ++ i) {
        char buffer[2];
        scanf("%s", buffer);
        type[i] = *buffer;
        if (type[i] == 'd') {
            scanf("%d", g + i);
        } else {
            scanf("%d", b + i);
        }
    }
    priority_queue <pair <int, int> > heap;
    for (int i = 1; i < n - 1; ++ i) {
        if (type[i] == 'd') {
            heap.push(make_pair(-g[i], i));
        } else {
            while (heap.size() >= b[i]) {
                heap.pop();
            }
        }
    }
    if (heap.size() < b[n - 1]) {
        puts("-1");
    } else {
        int sum = 0;
        vector <int> choices;
        while (!heap.empty()) {
            pair <int, int> ret = heap.top();
            heap.pop();
            sum -= ret.first;
            choices.push_back(ret.second);
        }
        sort(choices.begin(), choices.end());
        printf("%d\n%d\n", sum, (int)choices.size());
        for (int i = 0; i < (int)choices.size(); ++ i) {
            printf("%d%c", choices[i] + 1, i == (int)choices.size() - 1 ? '\n': ' ');
        }
    }
    return 0;
}
