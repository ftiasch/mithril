#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1000000 + 1;

typedef long long LL;

int n, m, a[N];
LL sum[N];

int size, stack[N];

int solve(int limit) {
    sum[0] = 0;
    for (int i = 1; i <= n; ++ i) {
        sum[i] = sum[i - 1] + a[i] - limit;
    }
    int result = 0;
    size = 0;
    for (int i = 0; i <= n; ++ i) {
        if (size > 0 && sum[stack[size - 1]] <= sum[i]) {
            int low = 0;
            int high = size - 1;
            while (low < high) {
                int middle = (low + high) >> 1;
                if (sum[stack[middle]] <= sum[i]) {
                    high = middle;
                } else {
                    low = middle + 1;
                }
            }
            result = max(result, i - stack[high]);
        }
        if (size == 0 || sum[stack[size - 1]] > sum[i]) {
            stack[size ++] = i;
        }
    }
    return result;
}

int main() {
    scanf("%d%d", &n, &m);
    //n=1000000;
    //m=50;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
        //a[i]=rand()%1000000000+1;
    }
    while (m > 0) {
        m --;
        int limit;
        scanf("%d", &limit);
        //limit=rand()%1000000000+1;
        printf("%d%c", solve(limit), m == 0? '\n': ' ');
    }
    return 0;
}
