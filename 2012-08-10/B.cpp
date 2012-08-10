#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int maxn  =   600;

char s[maxn];
int mc[maxn],list[maxn][maxn],len[maxn],ans,ansp[maxn],sel[maxn];
bool found,g[maxn][maxn];
vector<int> adj[maxn];
map<string,int> hash;
vector<string> arr;

inline void dfs(int size)
{
    int i,j,k;
    if (len[size]==0){
        if (size>ans){
            ans=size;
            found=true;
            for (i=0;i<ans;++i){
                ansp[i]=sel[i];
            }
        }
        return;
    }
    
    for (k=0;k<len[size] && !found;++k){
        if (size+len[size]-k<=ans) break;
        i=list[size][k];
        if (size+mc[i]<=ans) break;
        for (j=k+1,len[size+1]=0;j<len[size];++j)
        if (g[i][list[size][j]]) list[size+1][len[size+1]++]=list[size][j];
        
        sel[size]=i;
        dfs(size+1);
    }
}

int main()
{
    scanf("%s",s);
    int n=strlen(s);
    sort(s,s+n);
    do{
        string t=s;
        hash[t]=arr.size()+1;
        arr.push_back(t);
    }while (next_permutation(s,s+n));
    
    memset(g,true,sizeof(g));
    for (int i=0;i<arr.size();++i){
        string t=arr[i];
        for (int a=0;a<t.size();++a)
        if (t[a]=='A'){
            for (int b=0;b<t.size();++b)
            if (t[b]=='B'){
                for (int c=0;c<t.size();++c)
                if (t[c]=='C'){
                    string t1=t;
                    t1[a]='B';
                    t1[b]='C';
                    t1[c]='A';
                    adj[i+1].push_back(hash[t1]);
                    
                    t1[a]='C';
                    t1[b]='A';
                    t1[c]='B';
                    adj[i+1].push_back(hash[t1]);
                }
            }
        }
    }
    
    for (int i=1;i<=arr.size();++i){
        for (int j=0;j<adj[i].size();++j){
            g[i][adj[i][j]]=false;
            for (int k=0;k<adj[i].size();++k)
            if (j!=k){
                g[adj[i][j]][adj[i][k]]=false;
            }
        }
    }
    
    n=arr.size();
    mc[n]=ans=1;
    ansp[0]=n;
    for (int i=n-1;i>0;--i){
        found=false;
        len[1]=0;
        for (int j=i+1;j<=n;++j)
        if (g[i][j]) list[1][len[1]++]=j;
        
        sel[0]=i;
        dfs(1);
        mc[i]=ans;
    }
    
    printf("%d\n",ans);
    for (int i=0;i<ans;++i)
        printf("%s\n",arr[ ansp[i]-1 ].c_str());
    return 0;
}

