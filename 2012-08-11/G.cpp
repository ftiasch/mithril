#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn  =   500005;

struct node
{
    int x,y;
}a[maxn];

struct Event
{
    int x,y,delta;
    Event(){}
    Event(int x,int y,int delta):x(x),y(y),delta(delta){}
};
vector<Event> e;

inline bool cmpy(const node &a,const node &b)
{
    return a.y<b.y || a.y==b.y && a.x<b.x;
}

inline bool cmpx(const node &a,const node &b)
{
    return a.x<b.x || a.x==b.x && a.y<b.y;
}

inline bool cmpEvent(const Event &a,const Event &b)
{
    return a.x<b.x;
}

vector<int> tree[maxn*4],baky,res;
int w,h,n;
long long ans[10];

inline void build(int num,int l,int r)
{
    tree[num].clear();
    for (int i=0;i<=2;++i) tree[num].push_back(0);
    tree[num][0]=r-l+1;
    if (l==r) return;
    int mid=(l+r)/2;
    build(num*2,l,mid);
    build(num*2+1,mid+1,r);
}

inline void merge(vector<int> &res,const vector<int> &a,const vector<int> &b)
{
    res.resize(3);
    for (int i=0;i<=2;++i)
        res[i]=(a[i]+b[i]);
    return;
}

inline void insert(int num,int l,int r,int pos,int delta)
{
    if (pos<baky[l] || pos>baky[r]) return;
    if (l==r){
        for (int i=0;i<=2;++i){
            if (tree[num][i]){
                tree[num][i+delta]=tree[num][i];
                tree[num][i]=0;
                break;
            }
        }
        return;
    }
    int mid=(l+r)/2;
    insert(num*2,l,mid,pos,delta);
    insert(num*2+1,mid+1,r,pos,delta);
    merge(tree[num],tree[num*2],tree[num*2+1]);
}

inline void query(int num,int l,int r,int ll,int rr)
{
    if (ll<=baky[l] && baky[r]<=rr){
        merge(res,res,tree[num]);
        return;
    }
    if (ll>baky[r] || rr<baky[l] || l==r){
        return;
    }
    int mid=(l+r)/2;
    query(num*2,l,mid,ll,rr);
    query(num*2+1,mid+1,r,ll,rr);
}

int main()
{
    scanf("%d%d%d",&w,&h,&n);
    baky.clear();
    for (int i=0;i<n;++i){
        scanf("%d%d",&a[i].x,&a[i].y);
        baky.push_back(a[i].y);
    }
    sort(baky.begin(),baky.end());
    baky.erase(unique(baky.begin(),baky.end()),baky.end());
    
    sort(a,a+n,cmpy);
    for (int i=0;i<n;++i){
        int j=i;
        while (j<n && a[j].y==a[i].y) ++j;
        
        if (0<a[i].x){
            e.push_back(Event(0,a[i].y,1));
            e.push_back(Event(a[i].x,a[i].y,-1));
        }
        for (int k=i;k+1<j;++k){
            if (a[k].x+1<a[k+1].x){
                e.push_back(Event(a[k].x+1,a[i].y,2));
                e.push_back(Event(a[k+1].x,a[i].y,-2));
            }
        }
        if (a[j-1].x<w){
            e.push_back(Event(a[j-1].x+1,a[i].y,1));
        }
        i=j-1;
    }
    
    sort(e.begin(),e.end(),cmpEvent);
    sort(a,a+n,cmpx);
    int last=-1;
    memset(ans,0,sizeof(ans));
    int eid=0;
int sjb=0;
    build(1,0,baky.size()-1);
//printf("%d\n",e.size());
    for (int i=0;i<n;){
//if (i%1000==0) printf("%d %d\n",i,sjb);
        while (eid<e.size() && e[eid].x<a[i].x){
//printf("%d %d %d\n",e[eid].x,e[eid].y,e[eid].delta);
            insert(1,0,baky.size()-1,e[eid].y,e[eid].delta);
            ++eid;
++sjb;
        }
        int len=a[i].x-last-1;
        
        if (len>0){
            int s=0;
            for (int i=0;i<=2;++i){
                ans[i]+=(long long)tree[1][i]*len;
                s+=tree[1][i];
            }
            int remain=h+1-s;
            ans[0]+=(long long)remain*len;
        }
        
        while (eid<e.size() && e[eid].x<=a[i].x){
//printf("%d %d %d\n",e[eid].x,e[eid].y,e[eid].delta);
            insert(1,0,baky.size()-1,e[eid].y,e[eid].delta);
            ++eid;
++sjb;
        }
        int j=i;
        while (j<n && a[j].x==a[i].x) ++j;
        if (a[i].y>0){
            res.resize(3);res[0]=res[1]=res[2]=0;
            query(1,0,baky.size()-1,0,a[i].y-1);
            vector<int> &t=res;
            int s=0;
            for (int i=0;i<=2;++i){
                ans[i+1]+=(long long)t[i];
                s+=t[i];
            }
            int remain=a[i].y-s;
            ans[0+1]+=(long long)remain;
++sjb;
        }
        for (int k=i;k+1<j;++k)
        if (a[k].y+1<a[k+1].y){
            res.resize(3);res[0]=res[1]=res[2]=0;
            query(1,0,baky.size()-1,a[k].y+1,a[k+1].y-1);
            vector<int> &t=res;
            int s=0;
            for (int i=0;i<=2;++i){
                ans[i+2]+=(long long)t[i];
                s+=t[i];
            }
            int remain=a[k+1].y-a[k].y-1-s;
            ans[0+2]+=(long long)remain;
++sjb;
        }
        if (a[j-1].y<h){
            res.resize(3);res[0]=res[1]=res[2]=0;
            query(1,0,baky.size()-1,a[j-1].y+1,h);
            vector<int> &t=res;
            int s=0;
            for (int i=0;i<=2;++i){
                ans[i+1]+=(long long)t[i];
                s+=t[i];
            }
            int remain=h-a[j-1].y-s;
            ans[0+1]+=(long long)remain;
++sjb;
        }
        
        last=a[i].x;
        i=j;
    }
    while (eid<e.size() && e[eid].x<=w){
        insert(1,0,baky.size()-1,e[eid].y,e[eid].delta);
        ++eid;
    }
    if (last<w){
        int len=w-last;
        if (len>0){
            int s=0;
            for (int i=0;i<=2;++i){
                ans[i]+=(long long)tree[1][i]*len;
                s+=tree[1][i];
            }
            int remain=h+1-s;
            ans[0]+=(long long)remain*len;
        }
    }
    
    for (int i=0;i<=4;++i){
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << endl;
    return 0;
}
