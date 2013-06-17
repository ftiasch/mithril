#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

using std::cin;
using std::vector;
using std::pair;

const int N = 100000;

long long x;
int n, k[N];
long long q[N], power[19];

vector <int> boxes[19];
vector <int> opened;

int main() {
    freopen("exact.in", "r", stdin);
    freopen("exact.out", "w", stdout);
    power[0] = 1;
    for (int i = 1; i <= 18; ++ i) {
        power[i] = power[i - 1] * 10;
    }
    cin >> x >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> k[i] >> q[i];
        boxes[k[i]].push_back(i);
    }
    long long left = 0;
    std::priority_queue <pair <long long, int > > avails;
    for (int i = 0; i <= 18; ++ i) {
        long long a = (x / power[i] % 10) * power[i];
        foreach (iter, boxes[i]) {
            avails.push(std::make_pair(q[*iter] * power[k[*iter]], *iter));
        }
        while (left < a) {
            if (avails.empty()) {
                puts("-1");
                return 0;
            }
            pair <long long, int> ret = avails.top();
            avails.pop();
            left += ret.first;
            opened.push_back(ret.second);
        }
        left -= a;
    }
    printf("%d\n", (int)opened.size());
    for (int i = 0; i < (int)opened.size(); ++ i) {
        printf("%d%c", opened[i] + 1, " \n"[i == (int)opened.size() - 1]);
    }
    return 0;
}
