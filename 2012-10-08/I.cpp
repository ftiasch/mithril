#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int limit     =   100000+100;
const int maxlen    =   10000;

int pr[limit],len,f[limit+5];
vector<int> pos[limit],tree[maxlen*4];
int n,m;

inline void merge(vector<int> &a,const vector<int> &b,const vector<int> &c)
{
    int i=0,j=0;
    a.clear();
    while (i<b.size() || j<c.size()){
        if (i<b.size() && (j==c.size() || b[i]<c[j])){
            a.push_back(b[i++]);
        }else{
            a.push_back(c[j++]);
        }
    }
}

inline void build(int num,int l,int r)
{
    if (l==r){
        tree[num]=pos[l];
        sort(tree[num].begin(),tree[num].end());
        return;
    }
    int mid=(l+r)/2;
    build(num*2,l,mid);
    build(num*2+1,mid+1,r);
    merge(tree[num],tree[num*2],tree[num*2+1]);
    //tree[num].erase(unique(tree[num].begin(),tree[num].end()),tree[num].end());
}

inline int getCount(vector<int> &a,int l,int r)
{
    return upper_bound(a.begin(),a.end(),r)-lower_bound(a.begin(),a.end(),l);
}

inline int query(int num,int l,int r,int ll,int rr)
{
    if (l==r) return pr[l];
    int mid=(l+r)/2;
    int cnt=getCount(tree[num*2],ll,rr);
//printf("%d %d %d %d %d\n",l,r,ll,rr,cnt);
    if (cnt<mid-l+1) return query(num*2,l,mid,ll,rr);
    else return query(num*2+1,mid+1,r,ll,rr);
}

int main()
{
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    
    memset(f,-1,sizeof(f));
    for (int i=2;i<=limit;++i){
        if (f[i]==-1){
            if (i<=limit/i){
                for (int j=i*i;j<=limit;j+=i){
                    if (f[j]==-1){
                        f[j]=len;
                    }
                }
            }
            f[i]=len;
            pr[len++]=i;
        }
    }
//    printf("len=    %d, last=   %d\n",len,pr[len-1]);
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i){
        int x;
        scanf("%d",&x);
        while (x>1){
            int bak=f[x];
            while (f[x]==bak){
                x/=pr[bak];
            }
            pos[bak].push_back(i);
//printf("%d %d\n",bak,i);
        }
    }
    
    build(1,0,len-1);
    
    for (int i=0;i<m;++i){
        int l,r;
        scanf("%d%d",&l,&r);
        --l;--r;
        printf("%d\n",query(1,0,len-1,l,r));
    }
    return 0;
}

