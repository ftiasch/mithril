#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10000;

int maxX, maxY, n, x[N][2], y[N][2];

int main() {
    scanf("%d%d%d", &maxX, &maxY, &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d%d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
        if (x[i][0] > x[i][1]) {
            swap(x[i][0], x[i][1]);
        }
        if (y[i][0] > y[i][1]) {
            swap(y[i][0], y[i][1]);
        }
    }
    int maxCover = -1;
    int maxArea = 0;
    for (int curX = 0; curX < maxX; ++ curX) {
        vector <pair <int, int> > events;
        events.push_back(make_pair(0, 0));
        events.push_back(make_pair(maxY, 0));
        for (int i = 0; i < n; ++ i) {
            if (x[i][0] <= curX && curX < x[i][1]) {
                events.push_back(make_pair(y[i][0], 1));
                events.push_back(make_pair(y[i][1], -1));
            }
        }
        sort(events.begin(), events.end());
        int cover = events[0].second;
        for (int i = 1; i < (int)events.size(); ++ i) {
            if (events[i - 1].first < events[i].first) {
                if (cover > maxCover) {
                    maxCover = cover;
                    maxArea = 0;
                }
                if (cover == maxCover) {
                    maxArea += events[i].first - events[i - 1].first;
                }
            }
            cover += events[i].second;
        }
    }
    printf("%d\n%d\n", maxCover, maxArea);
    return 0;
}
