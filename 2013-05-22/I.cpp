#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
 
const int maxn = 100;
const int limit = 1000000000;
 
int need, answer[maxn];
vector<int> factor[maxn];
 
inline void gen(vector<int> &factor, int step, int mul, int* answer)
{
    if (need <= 0) {
        return;
    }
    if (step == factor.size()) {
        answer[-- need] = mul;
        return;
    }
    for (;(long long)mul * factor[step] <= limit;) {
        mul *= factor[step];
        gen(factor, step + 1, mul, answer);
    }
}
 
inline bool isPrime(int x)
{
    if (x <= 1) {
        return false;
    }
    for (int i = 2; i * i <= x; ++ i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
 
int main()
{
    freopen("reconstruction.in", "r", stdin);
    freopen("reconstruction.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int half = n / 2;
    int size = half / 2;
    int m = 0;
    for (int i = 0; i < n; i += size) {
        ++ m;
    }
    if (n == 7) {
        -- m;
    }
     
    for (int i = 0; i < n ; ++ i) {
        answer[i] = 1;
    }
     
    vector<pair<int, int> > edge;
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < i ; ++ j) {
            edge.push_back(make_pair(i, j));
        }
    }
    random_shuffle(edge.begin(), edge.end());
    vector<int> prime;
    for (int i = 2; prime.size() < edge.size(); ++ i) {
        if (isPrime(i)) {
            prime.push_back(i);
        }
    }
    for (int i = 0; i < edge.size(); ++ i) {
        factor[edge[i].first].push_back(prime[i]);
        factor[edge[i].second].push_back(prime[i]);
    }
     
    for (int i = 0; i < m; ++ i) {
        need = min(n - i * size, size);
        if (n == 7 && i + 1 == m) {
            need = 2;
        }
        gen(factor[i], 0, 1, answer + (i * size));
    }
     
    for (int i = 0; i < n; ++ i) {
        printf("%d\n", answer[i]);
    }
     
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            if (__gcd(answer[i], answer[j]) == 1) {
                puts("WA!!");
                while (1);
            }
        }
    }
    for (int i = 0; i < prime.size(); ++ i) {
        int cnt = 0;
        for (int j = 0; j < n; ++ j) {
            if (answer[j] % prime[i] == 0) {
                ++ cnt;
            }
        }
        if (cnt > n / 2) {
            printf("WA 2!!");
            vector<int> a;
            printf("%d\n", a[0]);
        }
    }
     
    return 0;
}
