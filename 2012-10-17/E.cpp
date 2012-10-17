#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <algorithm>
using namespace std;

const int N = 1000;

int n, m, startTime[N];
deque <int> roomOrder[N];

bool byStartTime(int i, int j) {
    return startTime[i] < startTime[j];
}

int lastVisited[N];
vector <int> roomBuffer[N];
deque <int> roomQueue[N];

vector <int> events;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

void addEvent(int t, int p, int r) {
    roomBuffer[r].push_back(p);
    if (lastVisited[r] != t) {
        lastVisited[r] = t;
        events.push_back(r);
    }
}

map <int, int> queueSize;

int main() {
    freopen("medical.in", "r", stdin);
    freopen("medical.out", "w", stdout);
    scanf("%d%d", &n, &m);
    deque <int> peopleOrder;
    for (int i = 0; i < n; ++ i) {
        peopleOrder.push_back(i);
        scanf("%d", startTime + i);
        int k;
        scanf("%d", &k);
        while (k --) {
            int x;
            scanf("%d", &x);
            roomOrder[i].push_back(-- x);
        }
    }
    sort(peopleOrder.begin(), peopleOrder.end(), byStartTime);
    memset(lastVisited, -1, sizeof(lastVisited));
    int currentTime = 0;
    int result = 0;
    while (!events.empty() || !peopleOrder.empty() || !queueSize.empty()) {
//printf("%d\n", currentTime);
        while (!peopleOrder.empty() && startTime[peopleOrder.front()] == currentTime) {
            int p = peopleOrder.front();
            peopleOrder.pop_front();
            addEvent(currentTime, p, roomOrder[p].front());
//printf(">> %d, %d\n", p, roomOrder[p].front());
            roomOrder[p].pop_front();
        }
        foreach (iter, events) {
            int r = *iter;
            sort(roomBuffer[r].begin(), roomBuffer[r].end());
            foreach (p, roomBuffer[r]) {
                roomQueue[r].push_back(*p);
                queueSize[r] ++;
            }
            roomBuffer[r].clear();
        }
//for (int i = 0; i < m; ++ i) {
//    printf("%d: ", i);
//    foreach (iter, roomQueue[i]) {
//        printf("%d, ", *iter);
//    }
//    puts("");
//}
//puts("");
        events.clear();
        vector <int> eraseQueue;
        foreach (iter, queueSize) {
            int r = iter->first;
            int p = roomQueue[r].front();
            roomQueue[r].pop_front();
            if (roomOrder[p].empty()) {
                result = currentTime + 1;
            } else {
                addEvent(currentTime + 1, p, roomOrder[p].front());
                roomOrder[p].pop_front();
            }
            if (!(-- iter->second)) {
                eraseQueue.push_back(iter->first);
            }
        }
        foreach (iter, eraseQueue) {
            queueSize.erase(*iter);
        }
        currentTime ++;
    }
    printf("%d\n", result);
    return 0;
}
