#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

const string sets[12]   =   {"be","our","rum","will","dead","hook","ship","blood","sable","avenge","parrot","captain"};

string a[200],word[200];
vector<int> candidate[200];
int f[30],ans,ansf[30];

inline bool cmp(const int &i,const int &j)
{
    return candidate[i].size()<candidate[j].size() || candidate[i].size()==candidate[j].size() && a[i].size()>a[j].size();
}

inline int getSize(string a[],int n)
{
    bool vis[26];
    memset(vis,false,sizeof(vis));
    for (int i=0;i<n;++i){
        for (int j=0;j<a[i].size();++j){
            vis[a[i][j]-'a']=true;
        }
    }
    int res=0;
    for (int i=0;i<26;++i){
        res+=vis[i];
    }
    return res;
}

inline bool check(int f[],const string &a,const string &b,int mask)
{
    if (a.size()!=b.size()){
        return false;
    }
    int g[26];
    for (int i=0;i<26;++i){
        g[i]=f[i];
    }
    for (int i=0;i<a.size();++i){
        int c=a[i]-'a';
        int d=b[i]-'a';
        if (g[c]==-1){
            if (mask>>d&1){
                return false;
            }
            g[c]=d;
            mask|=1<<d;
        }else if (g[c]!=d){
            return false;
        }
    }
    return true;
}

inline void update(int g[],const string &a,const string &b,int &mask)
{
    for (int i=0;i<a.size();++i){
        int c=a[i]-'a';
        int d=b[i]-'a';
        g[c]=d;
        mask|=1<<d;
    }
}

int n,m,order[200],tmpn,selectMask;
string tmp[200];

inline int getIndex(const string &t)
{
    for (int i=0;i<12;++i){
        if (sets[i]==t) return i;
    }
    return -1;
}

inline void dfs(int step,int mask)
{
    if (ans>1) return;
    
    if (step==m){
        for (int i=0;i<tmpn;++i){
            string t="";
            for (int j=0;j<tmp[i].size();++j){
                t+=(char)(f[tmp[i][j]-'a']+'a');
            }
            int index=getIndex(t);
            if (index!=-1 && !(selectMask>>index&1)){
                return;
            }
        }
        ++ans;
        for (int i=0;i<26;++i){
            ansf[i]=f[i];
        }
        return;
    }
    
    int g[26],bak=mask;
    for (int i=0;i<26;++i){
        g[i]=f[i];
    }
    int u=order[step];
    for (int i=0;i<candidate[u].size();++i){
        if (check(f,word[candidate[u][i]],a[u],mask)){
            update(f,word[candidate[u][i]],a[u],mask);
            dfs(step+1,mask);
            for (int j=0;j<26;++j){
                f[j]=g[j];
            }
            mask=bak;
        }
    }
}

char ori[1000];

int main()
{
    gets(ori);
    stringstream in(ori);
    n=0;
    for (;in >> word[n];++n){
        tmp[n]=word[n];
    }
    tmpn=n;
    
    sort(word,word+n);
    n=unique(word,word+n)-word;
    
    ans=0;
    int tar=getSize(word,n);
    for (int stat=0;(stat<1<<12) && ans<2;++stat){
        m=0;
        for (int i=0;i<12;++i){
            if (stat>>i&1){
                a[m++]=sets[i];
            }
        }
        if (tar!=getSize(a,m)){
            continue;
        }
        
        memset(f,-1,sizeof(f));
        for (int i=0;i<m;++i){
            candidate[i].clear();
            for (int j=0;j<n;++j){
                if (check(f,word[j],a[i],0)){
                    candidate[i].push_back(j);
                }
            }
        }
        
        for (int i=0;i<m;++i){
            order[i]=i;
        }
        sort(order,order+m,cmp);
        selectMask=stat;
        dfs(0,0);
    }
    
    if (ans!=1){
        puts("Impossible");
    }else{
        for (int i=0;ori[i];++i){
            if (ori[i]>='a' && ori[i]<='z'){
                ori[i]=ansf[ori[i]-'a']+'a';
            }
        }
        puts(ori);
    }
    return 0;
}
