#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn  =   100005;

int tree[maxn*3+10],a[maxn],n,pos[maxn];

inline int lowbit(int x)
{
    return x&-x;
}

inline int getsum(int x,int n)
{
    int res=0;
    for (;x>0;x-=lowbit(x)){
        res+=tree[x];
    }
    return res;
}

inline void add(int x,int n,int delta)
{
    for (;x<=n;x+=lowbit(x)){
        tree[x]+=delta;
    }
}

int main()
{
    scanf("%d",&n);
    vector<int> bak;
    for (int i=0;i<n;++i){
        scanf("%d",&a[i]);
        bak.push_back(a[i]);
    }
    bak.push_back(0);
    sort(bak.begin(),bak.end());
    bak.erase(unique(bak.begin(),bak.end()),bak.end());
    
    int N=bak.size()*2+1+n+2;
    for (int i=0;i<n;++i){
        a[i]=lower_bound(bak.begin(),bak.end(),a[i])-bak.begin();
    }
    int last=N;
    for (int i=bak.size()-1;i>=0;--i){
        if (bak[i]){
            pos[i]=last--;
            add(pos[i],N,1);
        }
        if (i>0 && bak[i]-1>=bak[i-1]+1){
            add(last,N,bak[i]-1-bak[i-1]);
            --last;
        }
    }
    
    for (int i=0;i<n;++i){
        if (i) printf(" ");
        printf("%d",getsum(pos[a[i]],N));
        
        add(pos[a[i]],N,-1);
        pos[a[i]]=last--;
        add(pos[a[i]],N,1);
    }
    puts("");
    
    return 0;
}

