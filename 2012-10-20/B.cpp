#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 50000;

int n;

int parent[N << 2];

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

void merge(int i, int j) {
    if (find(i) != find(j)) {
        parent[find(j)] = find(i);
    }
}

int edgeCount, firstEdge[N << 2], to[N << 2], nextEdge[N << 2];

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

int mapping[N];
bool used[N << 1];

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n << 2; ++ i) {
        parent[i] = i;
    }
    for (int i = 0; i < n; ++ i) {
        for (int x = 0; x < 2; ++ x) {
            int y, j;
            scanf("%d%d", &y, &j);
            j --;
            merge((i << 1) | x, (j + n << 1) | y);
        }
    }
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < n << 1; ++ i) {
        int u = find(i << 1);
        int v = find((i << 1) | 1);
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 0; i < n << 1; ++ i) {
        if (!used[i]) {
            vector <int> cycle(1, i << 1);
            used[i] = true;
            int p = i << 1;
            int start = to[p ^ 1];
            while (to[p] != start) {
                for (int iter = firstEdge[to[p]]; iter != -1; iter = nextEdge[iter]) {
                    if ((iter ^ p) != 1) {
                        cycle.push_back(iter);
                        p = iter;
                        break;
                    }
                }
                used[p >> 1] = true;
            }
            int counter = 0;
            foreach (iter, cycle) {
                if (*iter & 1) {
                    counter ++;
                } else {
                    counter --;
                }
            }
            int m = (int)cycle.size();
            if (counter != 0) {
                if (counter > 0) {
                    reverse(cycle.begin(), cycle.end());
                }
                for (int i = 0; i < m; ++ i) {
                    if (cycle[i] >> 1 < n) {
                        mapping[cycle[i] >> 1] = (cycle[(i + 1) % m] >> 1) - n;
                    }
                }
            } else {
                reverse(cycle.begin(), cycle.end());
                vector<int> a;
                a.resize(2*m);
                for (int i=0;i<m;++i){
                    if (cycle[i]&1){
                        a[i]=a[i+m]=-1;
                    }else{
                        a[i]=a[i+m]=1;
                    }
                }
                vector<int> s;
                s.resize(a.size()+1);
                s[0]=0;
                for (int i=0;i<a.size();++i){
                    s[i+1]=s[i]+a[i];
                }
                deque< pair<int,int> > q;
                int ptr=-1;
                for (int i=0;i<a.size();++i){
                    while (q.size() && q.back().second>s[i+1]) q.pop_back();
                    q.push_back(make_pair(i,s[i+1]));
                    while (q.size() && q.front().first+m<=i) q.pop_front();
                    if (i>=m-1 && q.size() && q.front().second>=s[i+1-m]){
                        ptr=i-m+1;
                        break;
                    }
                }
                if (ptr==-1){
                    puts("fuck");
                    while (1);
                }
                rotate(cycle.begin(), cycle.begin() + ptr, cycle.end());
                vector <int> stack;
/*puts("---");
for (int i=0;i<cycle.size();++i){
    printf("%d  ",cycle[i]&1);
}
puts("");*/
                for (int i = 0; i < m; ++ i) {

                    if ((cycle[i] & 1) == 0) {
                        stack.push_back(cycle[i] >> 1);
                    } else {
                        int a = stack.back();
                        stack.pop_back();
                        int b = cycle[i] >> 1;
                        if (a > b) {
                            swap(a, b);
                        }
                        mapping[a] = b - n;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d\n", mapping[i] + 1);
    }
    return 0;
}
