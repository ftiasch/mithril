// Problem A -- You’re in the Army Now
// Author: Jingbo Shang
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

const int maxn  =   100005;
char line[10000000];

int n,m,k,id[maxn],a[maxn];
vector<string> out[maxn];

inline void check(bool fl)
{
    if (!fl){
        vector<int> a;
        printf("%d\n",a[0]);
    }
}

struct Soldier
{
    string name;
    vector<int> prio;
    int attack;
    
    Soldier(){}
    inline void read()
    {
        gets(line);
        name="";
        prio.clear();
        for (int i=0;line[i];++i)
        if (line[i]>='0' && line[i]<='9'){
            int s=0,t=i-1;
            while (s<=t && line[s]==' ') ++s;
            while (s<=t && line[t]==' ') --t;
            for (int j=s;j<=t;++j) name+=line[j];
            string buf="";
            for (int j=i;line[j];++j) buf+=line[j];
            stringstream in(buf);
            in >> attack;
            int n;
            in >> n;
            prio.resize(n);
            for (int j=0;j<n;++j){
                in >> prio[j];
            }
            break;
        }
        
        check(name.size()>0 && name.size()<=20);
        for (int i=0;i<name.size();++i){
            bool ok=false;
            if (name[i]>='a' && name[i]<='z') ok=true;
            if (name[i]>='A' && name[i]<='Z') ok=true;
            if (name[i]==' ') ok=true;
            check(ok);
        }
        check(attack>0 && attack<=1000000000);
        check(prio.size()>0 && prio.size()<=k);
        for (int i=0;i<prio.size();++i){
            check(prio[i]>=1 && prio[i]<=m);
        }
    }
}soldier[maxn];

inline bool cmp(const int &i,const int &j)
{
    return soldier[i].attack>soldier[j].attack;
}

inline bool cmpString(const string &a,const string &b)
{
    for (int i=0;i<a.size() && i<b.size();++i){
        char c1=a[i];
        char c2=b[i];
        if (c1>='A' && c1<='Z') c1=c1-'A'+'a';
        if (c2>='A' && c2<='Z') c2=c2-'A'+'a';
        
        if (c1==c2){
            if (a[i]!=b[i]) return a[i]<b[i];
        }else{
            return c1<c2;
        }
    }
    return a.size()<b.size();
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for (int i=1;i<=m;++i){
        scanf("%d",&a[i]);
    }
    gets(line);
    
    for (int i=0;i<n;++i){
        soldier[i].read();
        id[i]=i;
    }
    
    sort(id,id+n,cmp);
    for (int i=0;i+1<n;++i)
        check(soldier[id[i]].attack!=soldier[id[i+1]].attack);    
    for (int i=0;i<n;++i){
        int u=id[i];
        Soldier &s=soldier[u];
        
        for (int j=0;j<s.prio.size();++j){
            int arm=s.prio[j];
            if (a[arm]>0){
                --a[arm];
                out[arm].push_back(s.name);
                goto Break;
            }
        }
        Break:;
    }
    
    for (int i=1;i<=m;++i){
        sort(out[i].begin(),out[i].end(),cmpString);
        for (int j=0;j<out[i].size();++j)
            printf("%s\n",out[i][j].c_str());
        if (i<m) printf("\n");
    }
    return 0;
}
