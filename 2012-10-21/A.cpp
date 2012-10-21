#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

const int N = 10000;

int n, m, score[N], mask[N];
vector <int> group[60000];
int pw3[120],ind[1<<12];
int real[1<<12];


int main() {
    pw3[0]=1;
    scanf("%d%d", &n, &m);
    for (int i=1;i<=m;++i){
        pw3[i]=pw3[i-1]*3;
    }
    for (int i=0;i<m;++i){
        ind[1<<i]=i;
    }
    
    for (int i = 0; i < n; ++ i) {
        scanf("%d", score + i);
        int k;
        scanf("%d", &k);
        mask[i]=0;
        real[0]=0;
        while (k --) {
            int x;
            scanf("%d", &x);
            x --;
            mask[i] |= 1 << x;
            real[0]+=pw3[x];
        }
        for (int cover=1;cover<1<<m;++cover){
            int lowbit=cover&-cover;
            int u=ind[lowbit];
            real[cover]=real[cover^lowbit]-pw3[u]*(mask[i]>>u&1)+pw3[u]*2;
        }
        for (int cover=0;cover<1<<m;++cover){
            group[real[cover]].push_back(score[i]);
        }
    }
    
    for (int i=0;i<60000;++i){
        sort(group[i].begin(),group[i].end());
        reverse(group[i].begin(),group[i].end());
    }
    
    int q;
    scanf("%d", &q);
    while (q --) {
        int id, k;
        scanf("%d%d", &id, &k);
        id --;
        int real = pw3[m]-1;
        while (k --) {
            int x;
            scanf("%d", &x);
            x --;
            real-=pw3[x]*2;
            real+=pw3[x]*(mask[id]>>x&1);
        }
        vector <int> &v = group[real];
        int m = (int)v.size();
        int low = 0;
        int high = m+1;
        while (low + 1 < high) {
            int middle = (low + high) >> 1;
            if (v[middle-1] > score[id]) {
                low = middle;
            } else {
                high = middle;
            }
        }
        int result = low+1;
        printf("%d\n", result);
    }
    return 0;
}
