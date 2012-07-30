#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn  =   10005;
const int maxk  =   15;
const int maxt  =   15;

struct node
{
    int A[maxn][maxk];
    int src[maxn][2];
    int out[maxn];
    int n;
}level[maxt];

int n,K,t;
vector<int> backup[1<<10];

int main()
{
    scanf("%d%d%d",&n,&K,&t);
    level[0].n=n;
    for (int i=0;i<n;++i){
        for (int j=0;j<K;++j)
            scanf("%d",&level[0].A[i][j]);
    }
    
    for (int l=1;l<=t;++l){
        level[l].n=0;
        for (int mask=0;mask<1<<K;++mask)
            backup[mask].clear();
        for (int i=0;i<level[l-1].n;++i){
            int mask=0;
            for (int j=0;j<K;++j){
                mask<<=1;
                if (level[l-1].A[i][j]>>l-1 & 1) mask|=1;
            }
            backup[mask].push_back(i);
        }
        
        for (int mask=0;mask<1<<K;++mask){
            while (backup[mask].size()){
                int i=backup[mask].back();
                backup[mask].pop_back();
                
                int complement=mask;
                if (backup[complement].size()>0){
                    int j=backup[complement].back();
                    backup[complement].pop_back();
                    
                    for(int k=0;k<K;++k){
                        level[l].A[level[l].n][k]=level[l-1].A[i][k]+level[l-1].A[j][k];
                        level[l].src[level[l].n][0]=i;
                        level[l].src[level[l].n][1]=j;
                    }
                    ++level[l].n;
                }
            }
        }
    }
    
    for (int l=0;l<=t;++l){
        for (int i=0;i<level[l].n;++i)
            level[l].out[i]=0;
    }
    for (int i=0;i<level[t].n;++i) level[t].out[i]=i+1;
    for (int l=t;l>0;--l){
        for (int i=0;i<level[l].n;++i){
            int x=level[l].src[i][0];
            int y=level[l].src[i][1];
            level[l-1].out[x]=level[l].out[i];
            level[l-1].out[y]=level[l].out[i];
        }
    }
    
    puts("YES");
    for (int i=0;i<level[0].n;++i) printf("%d\n",level[0].out[i]);
    
    return 0;
}

