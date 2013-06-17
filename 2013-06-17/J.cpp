#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 100000;

int vis[maxn], stamp, n, current;
vector<int> answer;
int a, b, c;

inline void go(int delta)
{
    if (abs(delta) == 1) {
        assert(a > 0);
        -- a;
    } else if (abs(delta) == 2) {
        assert(b > 0);
        -- b;
    } else if (abs(delta) == 3) {
        assert(c > 0);
        -- c;
    }
    current += delta;
    assert(current >= 0 && current <= n);
    assert(vis[current] != stamp);
    answer.push_back(current);
    vis[current] = stamp;
}

inline void go3(int target, int type)
{
    int src = current;
    //mod 3 = 0
    while (current + 3 <= target) {
        go(3);
    }
    if (type == 1) {
        go(-1); // mod 3 = 2
    } else {
        go(1); // mod 3 = 1
    }
    while (current - 3 > src) {
        go(-3);
    }
    if (type == 1) {
        go(-1); // mod 3 = 1
    } else {
        go(1); // mod 3 = 2
    }
    while (current + 3 <= target) {
        go(3);
    }
    assert(current == target);
}

int main()
{
    freopen("jumping.in", "r", stdin);
    freopen("jumping.out", "w", stdout);
    
    int T;
    for (scanf("%d", &T); T --;) {
        ++ stamp;
        
        scanf("%d%d%d", &a, &b, &c);
/*        a = rand() % 100 + 3;
        b = rand() % 100 + 3;
        c = rand() % 100 + 3;*/
        n = a + b + c;
        
        current = 0;
        vis[current] = stamp;
        answer.clear();
        answer.push_back(0);
        while (a > 3) {
            go(1);
        }
        
        while (c > 0) {
            int type = (c + 2) % 3;
            if (type != 0) {
                int target = current + c + 2;
                go3(target, type);
            } else {
                if (b >= 4) {
                    go(2);
                    go(3);
                    go(-2);
                    go(-2);
                    go(3);
                    go(2);
                } else {
                    go(1);
                    type = c % 3;
                    int target = current + c;
                    go3(target, type);
                    go(2);
                    go(3);
                    go(-2);
                    go(-2);
                    go(3);
                }
            }
        }
        
        if (a == 1) {
            int target = current + 1 + b;
            int src = current;
            while (current + 2 <= target) {
                go(2);
            }
            if (current + 1 <= target) {
                go(1);
            } else {
                go(-1);
            }
            while (current - 2 > src) {
                go(-2);
            }
        }
        
        assert(a + b + c == 0);
        for (int i = 0; i < answer.size(); ++ i) {
            printf("%d ", answer[i]);
        }
        puts("");
    }
    return 0;
}

