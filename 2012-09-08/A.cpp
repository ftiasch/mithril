#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

const int maxn  =   50005;

vector<long long> tree[11][11];
int A[maxn];

inline void add(vector<long long> &tree,int pos,int delta)
{
//printf("    add %d %d\n",pos,delta);
    for (int x=pos;x<tree.size();x+=x&-x){
        tree[x]+=delta;
    }
}

inline long long getSum(vector<long long> &tree,int pos)
{
    long long res=0;
    for (int x=pos;x>0;x-=x&-x){
        res+=tree[x];
    }
    return res;
}

int main()
{
    for (int n;scanf("%d",&n)==1;){
        for (int i=1;i<=10;++i){
            for (int j=0;j<i;++j){
                tree[i][j].resize(n/i+5);
                for (int k=0;k<tree[i][j].size();++k){
                    tree[i][j][k]=0;
                }
            }
        }
        for (int i=0;i<n;++i){
            scanf("%d",&A[i]);
            if (i) add(tree[1][0],i+1,A[i]-A[i-1]);
            else add(tree[1][0],i+1,A[i]);
        }
        int q;
        scanf("%d",&q);
        while (q--){
            int op,a,b,k,c;
            scanf("%d",&op);
            if (op==1){
                scanf("%d%d%d%d",&a,&b,&k,&c);
                --a;--b;
                add(tree[k][a%k],a/k+1,c);
                add(tree[k][a%k],a/k+(b-a)/k+2,-c);
            }else{
                scanf("%d",&a);
                --a;
                long long sum=0;
                for (k=1;k<=10;++k){
                    sum+=getSum(tree[k][a%k],a/k+1);
                }
                printf("%lld\n",sum);
            }
        }
    }
    return 0;
}

