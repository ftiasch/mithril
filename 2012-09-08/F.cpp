#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

const int maxn = 1 << 16;

int n;
int value[maxn];

struct node
{
    int a[6];
    inline void regular()
    {
        for (int i=0;i<6;++i)
        if (a[i]<0) a[i]=-1;
    }
};

inline bool operator <(const node &a,const node &b)
{
    for (int i=0;i<6;++i){
        if (a.a[i]!=b.a[i]) return a.a[i]<b.a[i];
    }
    return false;
}

set<node> vis;

inline bool bfs()
{
    if (n == 0) {
        return true;
    }
    vis.clear();
    node a;
    a.a[0]=n-1;
    a.a[1]=n-2;
    a.a[2]=n-3;
    a.a[3]=n-4;
    a.a[4]=n-5;
    a.a[5]=n-6;
    a.regular();
    queue<node> q;
    q.push(a);
    vis.insert(a);
    while (!q.empty()) {
        node cur=q.front();
        q.pop();
        
        for (int i=1;i<6;++i){
            if (cur.a[i]>=0 && value[cur.a[0]]==value[cur.a[i]]){
                node next;
                int k=0;
                for (int j=1;j<6;++j){
                    if (i!=j){
                        next.a[k++]=cur.a[j];
                    }
                }
                int x=cur.a[5]-1;
                while (k<6){
                    next.a[k++]=x--;
                }
                next.regular();
                if (next.a[0]<0) return true;
                if (vis.insert(next).second){
                    q.push(next);
                }
            }
        }
    }
    return false;
}

int main()
{
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%d", value + i);
        }
        printf("%d\n",bfs());
    }
}
