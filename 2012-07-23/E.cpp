#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <set>
using namespace std;

const int maxParty  =   25;
const int maxSeat   =   205;

struct Party
{
    string partyName;
    int C,V;
    vector<string> name;
    Party(){}
    inline void read()
    {
        cin >> partyName >> C >> V;
        name.resize(C);
        for (int i=0;i<C;++i){
            cin >> name[i];
        }
    }
}party[maxParty];

map<string,int> cnt;
set<string> isSel;
vector<string> out;

struct Constituency
{
    int C;
    vector< pair<int,pair<string,string> > > name;//vote, name, party
    
    Constituency(){}
    inline void read()
    {
        cin >> C;
        name.resize(C);
        for (int i=0;i<C;++i)
            cin >> name[i].second.first >> name[i].second.second >> name[i].first;
        sort(name.begin(),name.end());
        reverse(name.begin(),name.end());
        ++cnt[name[0].second.second];
        isSel.insert(name[0].second.first);
        out.push_back(name[0].second.first);
    }
}constituency[maxSeat];

bool valid[maxParty];

int integer[maxParty],fraction[maxParty];

inline bool cmp(const int &i,const int &j)
{
    return fraction[i]>fraction[j] || (fraction[i]==fraction[j] && integer[i]>integer[j]);
}

int main()
{
    int n,m;
    cin >> n >> m;
    int total=0;
    for (int i=0;i<m;++i){
        party[i].read();
        total+=party[i].V;
    }
    for (int i=0;i<n/2;++i){
        constituency[i].read();
    }
    
    memset(valid,false,sizeof(valid));
    int s=0;
    for (int i=0;i<m;++i){
        int win=cnt[party[i].partyName];
        if (win>=3 || party[i].V*100>=total*5){
            valid[i]=true;
            s+=party[i].V;
        }
    }
    
    vector<int> id;
    int sold=0;
    for (int i=0;i<m;++i)
    if (valid[i]){
        integer[i]=n*(long long)party[i].V/s;
        fraction[i]=n*(long long)party[i].V%s;
        id.push_back(i);
        sold+=integer[i];
    }
    sort(id.begin(),id.end(),cmp);
    
    for (int i=0;i<id.size();++i){
        int u=id[i],seat=integer[u];
        if (sold<n){
            ++seat;
            ++sold;
        }
        int iter=0;
        while (cnt[party[u].partyName]<seat){
            --seat;
            while (isSel.count(party[u].name[iter])) ++iter;
            isSel.insert(party[u].name[iter]);
            out.push_back(party[u].name[iter]);
        }
    }
    
    sort(out.begin(),out.end());
    printf("%d\n",(int)out.size());
    for (int i=0;i<out.size();++i)
        printf("%s\n",out[i].c_str());
    
    return 0;
}


