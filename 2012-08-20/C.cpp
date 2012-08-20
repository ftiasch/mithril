#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int n,L;
multiset<int> cheese;

int main()
{
    int T,test=1;
    for (scanf("%d",&T);test<=T;++test){
        scanf("%d%d",&L,&n);
        int pos=0,dir=1;
        long long ans=0;
        cheese.clear();
        for (int i=0;i<n;++i){
            int op,x;
            scanf("%d",&op);
            if (op==0){
                scanf("%d",&x);
                cheese.insert(x);
            }else{
                multiset<int>::iterator it=cheese.lower_bound(pos);
                multiset<int>::iterator l=it;
                bool change=false;
                if (l!=cheese.begin()){
                    --l;
                    if (it==cheese.end() || pos-(*l)<(*it)-pos || pos-(*l)==(*it)-pos && dir==-1){
                        if ((*l)<pos) dir=-1;
                        ans+=pos-(*l);
                        pos=*l;
                        change=true;
                        cheese.erase(l);
                    }
                }
                if (!change && it!=cheese.end()){
                    if ((*it)>pos) dir=1;
                    ans+=(*it)-pos;
                    pos=*it;
                    cheese.erase(it);
                }
            }
        }
        cout << "Case "<< test << ": " << ans << endl;
    }
    return 0;
}
