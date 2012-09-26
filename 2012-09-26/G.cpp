#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 400;
const int V = N * 2;

int n, m;
double low, high, a[N][N];

const double INF = 1e100;

const int Q = 1024*2;

double graph[V][V];
int inCount[V];
bool visit[V];
double dist[V];
int queue[Q];


int main() {
    while (scanf("%d%d%lf%lf", &n, &m, &low, &high) == 4) {
        low = log(low);
        high = log(high);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf("%lf", &a[i][j]);
                a[i][j] = log(a[i][j]);
            }
        }
        for (int i = 0; i < n + m; ++ i) {
            for (int j = 0; j < n + m; ++ j) {
                graph[i][j] = INF;
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                graph[i][n + j] = a[i][j] - low;
            }
        }
        for (int j = 0; j < m; ++ j) {
            for (int i = 0; i < n; ++ i) {
                graph[n + j][i] = high - a[i][j];
            }
        }
        memset(inCount, 0, sizeof(inCount));
        memset(visit, 0, sizeof(visit));
        memset(dist, 0, sizeof(dist));
        int tail = 0;
        for (int i = 0; i < n + m; ++ i) {
            queue[tail ++] = i;
        }
        bool found = false;
        int head = 0;
        int limit = n + m;
        while (head != tail && !found) {
            int i = queue[head];
            head = (head + 1) & 2047;
            visit[i] = false;            
            int st=0,ed=n;
            if (i<n){
            	st=n;
            	ed=n+m;
			}
            for (int j = st; j < ed; ++ j) {
                if (dist[i] + graph[i][j] + 1e-8 < dist[j]) {
                    dist[j] = dist[i] + graph[i][j];
                    if (!visit[j]) {
                        visit[j] = true;
                        if (dist[queue[head]] > dist[j] + 1e-8) {
                        	--head;
                        	if (head<0) head=2047;
                        	queue[head]=j;
                        }else{
	                        queue[tail] = j;
	                        tail = (tail + 1) & 2047;
	                    }
	                    
                        if ((++inCount[j]) >= limit) {
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
//printf("%lf %lf %lf %lf\n",dist[0],dist[1],dist[n],dist[n+1]);
//printf("%lf %lf\n",log(2),log(3));
//printf("%lf %lf\n",dist[n+1]+graph[n+1][1],dist[1]);
        puts(found? "NO": "YES");
    }
    return 0;
}
