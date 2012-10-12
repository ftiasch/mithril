#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#define PB push_back
#define MP make_pair

typedef long long LL;

const int maxn  =   50;


int n,ind[1<<21];
LL L,R,w[maxn],v[maxn];
LL sw[1<<16],sv[1<<16];

int main()
{
    cin >> n >> L >> R;
    for (int i=0;i<n;++i){
        cin >> w[i] >> v[i];
    }
    
    int half=n/2;
    sw[0]=0;
    sv[0]=0;
    for (int i=0;i<20;++i){
        ind[1<<i]=i;
    }
    for (int mask=1;mask<1<<half;++mask){
        int lowbit=mask&-mask;
        int i=ind[lowbit];
        sw[mask]=sw[mask^lowbit]+w[i];
        sv[mask]=sv[mask^lowbit]+v[i];
    }
    vector<pair<pair<LL,LL>,int> > bak;
    for (int i=0;i<1<<half;++i){
        bak.PB(MP(MP(sw[i],sv[i]),i));
    }
    sort(bak.begin(),bak.end());
    
    int p=0;
    for (int i=0;i<bak.size();++i){
        if (i==0 || bak[i].first.second>bak[p-1].first.second){
            bak[p++]=bak[i];
        }
    }
    bak.resize(p);
    
    for (int mask=1;mask<1<<n-half;++mask){
        int lowbit=mask&-mask;
        int i=ind[lowbit];
        sw[mask]=sw[mask^lowbit]+w[i+half];
        sv[mask]=sv[mask^lowbit]+v[i+half];
    }
    
    long long best=-1;
    long long bestp=0;
    for (int mask=0;mask<1<<n-half;++mask){
        long long w=sw[mask];
        long long l=L-w,r=R-w;
        if (l<0) l=0;
        if (l<=r){
            int index=upper_bound(bak.begin(),bak.end(),MP(MP(r+1,-1LL),-1))-bak.begin()-1;
            if (index>=0 && index<bak.size()){
                if (bak[index].first.first<=r && bak[index].first.first>=l){
                    long long tmp=sv[mask]+bak[index].first.second;
                    if (tmp>best){
                        best=tmp;
                        bestp=((LL)mask<<half)|bak[index].second;
                    }
                }
            }
        }
    }
    
    if (best==-1){
        puts("0");
    }else{
        printf("%d\n",__builtin_popcount(bestp));
        for (int i=0;i<n;++i){
            if (bestp>>i&1){
                printf("%d",i+1);
                bestp^=1LL<<i;
                if (bestp==0) puts("");
                else printf(" ");
            }
        }
    }
    
    return 0;
}

