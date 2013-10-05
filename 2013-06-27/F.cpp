#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
#include <cctype>
using namespace std;

const int limit = 10000000;

char line[1000000];

int main()
{
    int T, test = 1;
    for (scanf("%d", &T); T --; ++ test) {
        int k, w;
        scanf("%d%d", &k, &w);
        gets(line);
        int n = 0, last = 0;
        set<int> window;
        while (k --) {
            gets(line);
            vector<int> candidate;
            for (int i = 0; line[i]; ++ i) {
                if (isdigit(line[i])) {
                    int j = i, cur = 0;
                    while (isdigit(line[j])) {
                        cur = cur * 10 + line[j] - '0';
                        if (cur > limit) {
                            break;
                        }
                        if (cur > n) {
                            candidate.push_back(cur);
                        }
                        ++ j;
                    }
                }
            }
            sort(candidate.begin(), candidate.end());
            for (int i = 0; i < candidate.size(); ++ i) {
                int x = candidate[i];
                if (x <= n) {
                    continue;
                }
                if (x > n + w) {
                    break;
                }
                last = max(last, x);
                window.insert(x);
                while (window.count(n + 1)) {
                    ++ n;
                    window.erase(n);
                }
            }
        }
        printf("Case %d: %d %d\n", test, n, last);
    }
    return 0;
}

