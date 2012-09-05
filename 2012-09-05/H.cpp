#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <cassert>
using namespace std;

const int maxn  =   50005;

struct node
{
    int a[6];
}p[maxn],separate[maxn*4];
int n,k,pivot;

struct rec
{
    int maxi[6],mini[6];
}tree[maxn*4];

const int inf   =   10001;

inline bool cmpEqu(const node &a,const node &b)
{
    for (int i=0;i<k;++i){
        if (a.a[i]!=b.a[i]){
            return false;
        }
    }
    return true;
}

inline bool cmp(const node &a,const node &b)
{
    for (int i=0,j=pivot;i<k;++i,++j){
        if (j==k) j=0;
        if (a.a[j]!=b.a[j]){
            return a.a[j]<b.a[j];
        }
    }
    return false;
}

inline void build(int num,int dep,int l,int r)
{
    if (dep==k) dep=0;
    pivot=dep;
    for (int i=0;i<k;++i){
        tree[num].maxi[i]=-inf;
        tree[num].mini[i]=inf;
    }
    for (int i=l;i<r;++i){
        for (int j=0;j<k;++j){
            tree[num].maxi[j]=max(tree[num].maxi[j],p[i].a[j]);
            tree[num].mini[j]=min(tree[num].mini[j],p[i].a[j]);
        }
    }
    if (l+1==r) return;
    int mid=(l+r)/2;
    nth_element(p+l,p+mid,p+r,cmp);
    separate[num]=p[mid];
    
    build(num*2,dep+1,l,mid);
    build(num*2+1,dep+1,mid,r);
}

inline int sqr(int x)
{
    return x*x;
}

inline int getDist(rec &a,node &b)
{
    int res=0;
    for (int i=0;i<k;++i){
        int x;
        if (b.a[i]>a.maxi[i]) x=a.maxi[i];
        else if (b.a[i]>=a.mini[i]) x=b.a[i];
        else x=a.mini[i];
        res+=sqr(b.a[i]-x);
    }
    return res;
}

inline int getDist(node &a,node &b)
{
    int res=0;
    for (int i=0;i<k;++i){
        res+=sqr(b.a[i]-a.a[i]);
    }
    return res;
}

priority_queue< pair<int,int> > heap;
node out[11];
int ansCnt;

inline void query(int num,int dep,int l,int r,node &point)
{
    if (heap.size()==ansCnt && getDist(tree[num],point)>=heap.top().first){
        return;
    }
    if (l+1==r){
        int d=getDist(p[l],point);
        pair<int,int> cur=make_pair(d,l);
        if (heap.size()==ansCnt){
            heap.pop();
        }
        heap.push(cur);
        return;
    }
    
    if (dep==k) dep=0;
    pivot=dep;
    int mid=(l+r)/2;
    bool x=cmp(point,separate[num]);
    if (x==1){
        query(num*2,dep+1,l,mid,point);
        query(num*2+1,dep+1,mid,r,point);
    }else{
        query(num*2+1,dep+1,mid,r,point);
        query(num*2,dep+1,l,mid,point);
    }
}

int main()
{
    for (;scanf("%d%d",&n,&k)==2;){
        for (int i=0;i<n;++i){
            for (int j=0;j<k;++j){
                scanf("%d",&p[i].a[j]);
            }
        }
        pivot=0;
        sort(p,p+n,cmp);
        n=unique(p,p+n,cmpEqu)-p;
        build(1,0,0,n);
//puts("built!");fflush(stdout);
        int q;
        for (scanf("%d",&q);q--;){
            node point;
            for (int i=0;i<k;++i){
                scanf("%d",&point.a[i]);
            }
            scanf("%d",&ansCnt);
            query(1,0,0,n,point);
            assert(heap.size()==ansCnt);
            printf("the closest %d points are:\n",ansCnt);
            while (heap.size()){
                out[heap.size()-1]=p[heap.top().second];
                heap.pop();
            }
            for (int i=0;i<ansCnt;++i){
                for (int j=0;j<k;++j){
                    if (j) printf(" ");
                    printf("%d",out[i].a[j]);
                }
                puts("");
            }
        }
    }
}

