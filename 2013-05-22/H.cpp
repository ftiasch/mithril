#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int maxn = 100000;
 
int cnt[maxn + 1];
long long answer[300];
 
struct Pair
{
    int i, a;
    Pair(int i, int a):i(i),a(a) {
    }
};
 
vector<Pair> record[maxn + 1];
 
inline bool operator < (const Pair &a, const Pair &b)
{
    return a.a < b.a;
}
 
inline bool operator == (const Pair &a, const Pair &b)
{
    return a.a == b.a;
}
 
int main()
{
    freopen("mosaicism.in", "r", stdin);
    freopen("mosaicism.out", "w", stdout);
     
    int n, a[300];
    scanf("%d", &n);
    vector<Pair> event;
    for (int i = 0; i < n; ++ i) {
        int m;
        scanf("%d", &m);
        for (int j = 0; j < m; ++ j) {
            scanf("%d", &a[j]);
            for (int k = 0; k < j; ++ k) {
                int x = a[j], y = a[k];
                if (x > y) {
                    swap(x, y);
                }
                record[x].push_back(Pair(i, y));
            }
            ++ cnt[a[j]];
        }
    }
     
    for (int a = 1; a <= maxn; ++ a) {
        vector<Pair> &event = record[a];
        sort(event.begin(), event.end());
        for (int i = 0; i < event.size(); ++ i) {
            int j = i;
            while (j < event.size() && event[i] == event[j]) {
                ++ j;
            }
            int ab = j - i;
            int ca = cnt[a];
            for (int k = i; k < j; ++ k) {
                int onlyA = ca - ab;
                int onlyB = cnt[event[k].a] - ab;
                answer[event[k].i] += onlyA * onlyB;
            }
             
            i = j - 1;
        }
    }
     
     
    for (int i = 0; i < n; ++ i) {
        cout << answer[i] << endl;
    }
    return 0;
}
