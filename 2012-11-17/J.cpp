#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define PB push_back

typedef long long LL;

const int maxn  =   35;

int n;
LL L,S[maxn],R[maxn];
vector<LL> a[maxn];

inline void dfs(vector<LL> &b,int step,int n,LL sum)
{
    if (step==n){
        b.PB(sum);
        return;
    }
    for (int i=0;i<a[step].size();++i){
        dfs(b,step+1,n,sum+a[step][i]);
    }
}

inline void update(LL &a,LL b)
{
    if (abs(a-L)>abs(b-L) || abs(a-L)==abs(b-L) && a>b){
        a=b;
    }
}

int main()
{
    freopen("splitter.in","r",stdin);
    freopen("splitter.out","w",stdout);

    cin >> n >> L;
    LL sum=0;
    for (int i=0;i<n;++i){
        cin >> R[i];
        sum+=R[i];
    }
    for (int i=0;i<n;++i){
        cin >> S[i];
    }
    

    for (int i=0;i<n;++i){
        LL CR=R[i]*L/sum;
        if (R[i]*L%sum==0 && CR%S[i]==0){
            a[i].PB(CR);
        }else{
            LL k=CR/S[i];
            a[i].PB(k*S[i]);
            a[i].PB((k+1)*S[i]);
        }
    }
    
    vector<LL> left,right;
    dfs(left,0,n/2,0);
    dfs(right,n/2,n,0);
    
    LL ans=0;
    sort(left.begin(),left.end());
    for (int i=0;i<right.size();++i){
        //small
        int index=upper_bound(left.begin(),left.end(),L-right[i])-left.begin()-1;
        if (index>=0 && index<left.size()){
            update(ans,right[i]+left[index]);
        }
        ++index;
        if (index>=0 && index<left.size()){
            update(ans,right[i]+left[index]);
        }
    }
    cout << ans << endl;
    return 0;
}

