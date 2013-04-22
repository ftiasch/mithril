#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn  =   100005;

int n,m;
vector<int> adj[maxn];

int father[maxn],diff[maxn],minimal[maxn];

inline int find(int x)
{
    if (x==father[x]) return x;
    int t = father[x];
    father[x]=find(t);
    diff[x]^=diff[t];
    return father[x];
}

inline int solve()
{
    for (int i=0;i<n;++i){
        father[i]=i;
        diff[i]=0;
    }
    
    for (int i=1;i<n;++i){
//printf("i = %d\n",i);
        vector< pair<int,int> > color;
        for (int j=0;j<adj[i].size();++j){
            int comp = find(adj[i][j]);
            int c = diff[adj[i][j]];
//printf("    %d,%d\n",comp,c);
            color.push_back( make_pair(comp, c) );
        }
        sort(color.begin(),color.end());
        color.erase(unique(color.begin(),color.end()),color.end());
        for (int j=1;j<color.size();++j){
            if (color[j].first==color[j-1].first){
                return i;
            }
        }
                
        vector<int> dominate;
        for (int j=0;j<color.size();++j){
            dominate.push_back(minimal[color[j].first]);
        }
        sort(dominate.begin(),dominate.end());

        int cnt[2]={0,0}, self = i & 1, other = self ^ 1;
        for (int j=0;j<dominate.size();++j){
            int cur = dominate[j] & 1;
            if (cur == other) {
                if (cnt[self] || cnt[other]) {
                    return i;
                }
            }
            ++cnt[cur];
        }
        minimal[i] = i;
        for (int j=0;j<color.size();++j) {
            father[color[j].first] = i;
            diff[color[j].first] = color[j].second ^ 1;
            minimal[i] = min( minimal[i], minimal[color[j].first] );
        }
    }
    return n;
}

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        --a;--b;
        if (a<b) swap(a,b);
        adj[a].push_back(b);
    }
    int answer = solve();
    if (answer < n && answer % 2 == 0){
        printf("Bob %d\n",answer + 1);
    }else if (answer < n && answer % 2 == 1){
        printf("Alice %d\n",answer+1);
    }else{
        puts("Tie");
    }
    return 0;
}
