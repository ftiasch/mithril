#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;

struct node
{
    int dx,dy,x,y;
    LL len,cost;
    node(){}
    node(int dx,int dy,LL len,int x,int y):dx(dx),dy(dy),x(x),y(y),len(len)
    {
        cost=dy*x+(-dx)*y;
    }
};

const int maxn  =   2005;

vector<node> e;
int n,x[maxn],y[maxn];

inline bool cmp(const node &a,const node &b)
{
    return a.dx<b.dx || a.dx==b.dx && a.dy<b.dy || a.dx==b.dx && a.dy==b.dy && a.len<b.len
        || a.dx==b.dx && a.dy==b.dy && a.len==b.len && a.cost<b.cost;
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%d%d",&x[i],&y[i]);
    }
    for (int i=0;i<n;++i){
        for (int j=0;j<i;++j){
            int dx=x[i]-x[j],dy=y[i]-y[j];
            if (dx==0 && dy==0) continue;
            LL len=dx*(LL)dx+(LL)dy*dy;
            int d=__gcd(abs(dx),abs(dy));
            dx/=d;
            dy/=d;
            if (dx<0) dx=-dx,dy=-dy;
            else if (dx==0){
                if (dy<0) dy=-dy;
            }
            e.push_back(node(dx,dy,len,x[i],y[i]));
        }
    }
    sort(e.begin(),e.end(),cmp);
    
    LL ans=0;
    for (int i=0;i<e.size();++i){
        int j=i;
        while (j<e.size() && e[i].dx==e[j].dx && e[i].dy==e[j].dy && e[i].len==e[j].len) ++j;
        
        LL s=0;
        for (int k=i;k<j;++k){
            int l=k;
            while (l<j && e[l].cost==e[k].cost) ++l;
            ans+=(l-k)*s;
            s+=l-k;
            k=l-1;
        }
        
        i=j-1;
    }
    assert(ans%2==0);
    cout << ans/2 << endl;
    return 0;
}

