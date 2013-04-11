#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int maxn  =   100000 * 2 + 5;
const int inf   =   1000000000;

queue<int> q;
int dist[maxn],pre[maxn];

int tree[maxn*4][2];

inline void merge(int root[2],int left[2],int right[2])
{
    for (int i=0;i<2;++i){
        root[i]=max(left[i],right[i]);
    }
}

inline void build(int num,int l,int r)
{
    if (l==r){
        tree[num][0]=tree[num][1]=-inf;
        dist[l]=tree[num][l&1]=inf;
        return;
    }
    int mid=(l+r)/2;
    build(num*2,l,mid);
    build(num*2+1,mid+1,r);
    merge(tree[num],tree[num*2],tree[num*2+1]);
}

inline void insert(int num,int l,int r,int odd,int ll,int rr,int delta,int pr)
{
    if (ll>rr || r<ll || l>rr || tree[num][odd]<=delta){
        return;
    }
    if (l==r){
        dist[l]=delta;
        pre[l]=pr;
        q.push(l);
        tree[num][l&1]=delta;
        return;
    }
    int mid=(l+r)/2;
    insert(num*2,l,mid,odd,ll,rr,delta,pr);
    insert(num*2+1,mid+1,r,odd,ll,rr,delta,pr);
    merge(tree[num],tree[num*2],tree[num*2+1]);
}

int main()
{
    int K,M;
    scanf("%d%d",&K,&M);
    build(1,0,M);
    insert(1,0,M,0,0,0,0,-1);
    
    while (q.size()){
        int L=q.front();
//printf("%d: %d\n",L,dist[L]);
        q.pop();
        
        insert(1,0,M,(L+K)&1,L+K-2*min(L,K),min(L+K-2*max(L+K-M,0),M),dist[L]+1,L);
    }
    
    if (dist[M]==inf){
        puts("-1");
    }else{
        printf("%d\n",dist[M]);
        if (dist[M]<10){
            int len=0,cur=M,path[20];
            while (cur!=0){
                path[len++]=cur;
                cur=pre[cur];
            }
            vector<int> one,zero;
            for (int i=1;i<=M;++i){
                zero.push_back(i);
            }
            while (cur!=M){
                int next=path[--len];
                
                int overlap = (cur+K-next)/2;
                vector<int> out;
                for (int i=0;i<overlap;++i){
                    out.push_back(one.back());
                    one.pop_back();
                }
                for (int i=overlap;i<K;++i){
                    out.push_back(zero.back());
                    zero.pop_back();
                }
                for (int i=0;i<overlap;++i){
                    zero.push_back(out[i]);
                }
                for (int i=overlap;i<K;++i){
                    one.push_back(out[i]);
                }
                
                sort(out.begin(),out.end());
                for (int i=0;i<out.size();++i){
                    if (i) printf(" ");
                    printf("%d",out[i]);
                }
                puts("");
                
                cur=next;
            }
        }
    }
    
    return 0;
}

