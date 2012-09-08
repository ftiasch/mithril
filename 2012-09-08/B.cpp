#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 100000;

int n;
pair <pair <int, int>, int> events[N << 1];

const int ALICE = 1;
const int BOB = 0;

int main() {
    int testCount;
    scanf("%d", &testCount);
    while (testCount > 0) {
        testCount --;
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &events[i].first.first, &events[i].first.second);
            events[i].second = ALICE;
        }
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &events[n + i].first.first, &events[n + i].first.second);
            events[n + i].second = BOB;
        }
        sort(events, events + (n + n));
        int result = 0;
        multiset <int> keys;
        for (int i = 0; i < n + n; ++ i) {
            if (events[i].second == ALICE) {
                multiset <int> :: iterator iter = keys.upper_bound(events[i].first.second);
                if (iter != keys.begin()) {
                    iter --;
                    result ++;
                    keys.erase(iter);
                }
            } else {
                keys.insert(events[i].first.second);
            }
        }
        printf("%d\n", result);
    }
    return 0;
}
