#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int maxn  =   105*2;

bool neq[maxn][maxn];
int father[maxn],a[maxn],b[maxn],oa[maxn],ob[maxn];
int n,lt,ls;
char op[maxn][5];
set<int> ban;
vector<int> bak1,bak2;

inline int getfather(int x)
{
    if (father[x]==x) return x;
    return father[x]=getfather(father[x]);
}

inline void check(int delta)
{
    if (delta<0 || delta+ls>lt || ban.count(delta)) return;
    int l=delta+1,r=delta+ls;
    for (int i=0;i<bak1.size()+bak2.size();++i){
        father[i]=i;
    }

    for (int i=0;i<n;++i){
        a[i]=lower_bound(bak1.begin(),bak1.end(),oa[i])-bak1.begin();
        b[i]=lower_bound(bak2.begin(),bak2.end(),ob[i])-bak2.begin();
        if (op[i][0]=='='){
            father[getfather(a[i])]=getfather(b[i]+bak1.size());
        }
        if (ob[i]>=l && ob[i]<=r){
            int index=lower_bound(bak1.begin(),bak1.end(),ob[i]-delta)-bak1.begin();
            if (index>=0 && index<bak1.size() && bak1[index]==ob[i]-delta){
                father[getfather(index)]=getfather(b[i]+bak1.size());
            }
        }
    }

    for (int i=0;i<n;++i){
        if (op[i][0]=='!'){
            if (getfather(a[i])==getfather(b[i]+bak1.size()) || oa[i]+delta==ob[i]){
                ban.insert(delta);
//printf("delta=  %d\n",delta);
                return;
            }
        }
    }
}

int main()
{
    freopen("shifts.in","r",stdin);
    freopen("shifts.out","w",stdout);
    
    scanf("%d%d%d",&n,&ls,&lt);
    for (int i=0;i<n;++i){
        scanf("%d%s%d",&oa[i],op[i],&ob[i]);
        bak1.push_back(oa[i]);
        bak2.push_back(ob[i]);
    }
    sort(bak1.begin(),bak1.end());
    bak1.erase(unique(bak1.begin(),bak1.end()),bak1.end());
    sort(bak2.begin(),bak2.end());
    bak2.erase(unique(bak2.begin(),bak2.end()),bak2.end());
    
    for (int i=0;i<bak1.size()+bak2.size();++i){
        father[i]=i;
    }

    for (int i=0;i<n;++i){
        a[i]=lower_bound(bak1.begin(),bak1.end(),oa[i])-bak1.begin();
        b[i]=lower_bound(bak2.begin(),bak2.end(),ob[i])-bak2.begin();
        if (op[i][0]=='='){
            father[getfather(a[i])]=getfather(b[i]+bak1.size());
        }
    }
    for (int i=0;i<n;++i){
        if (op[i][0]=='!'){
            if (getfather(a[i])==getfather(b[i]+bak1.size())){
                puts("0");
                return 0;
            }
        }
    }
    
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j){
            check(ob[j]-oa[i]);
        }
    }
    
    printf("%d\n",lt-ls+1-ban.size());

    return 0;
}

