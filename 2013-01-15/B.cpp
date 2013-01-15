#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <climits>
using namespace std;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int maxn = 10000;

int n;
int a[maxn], b[maxn];
int timeA[maxn], timeB[maxn];
int ansA[maxn], ansB[maxn];

int permA[maxn], permB[maxn];

bool byBminusA(int i, int j)
{
    return b[i] - a[i] < b[j] - a[j];
}

bool byAminusB(int i, int j)
{
    return a[i] - b[i] < a[j] - b[j];
}

bool byAplusB(int i, int j)
{
    return a[i] + b[i] < a[j] + b[j];
}

bool byA(int i, int j)
{
    return a[i] < a[j];
}

bool byB(int i, int j)
{
    return b[i] < b[j];
}

int perform()
{
    int usedA = 0, usedB = 0;
    int ptrA = 0, ptrB = 0;
    while (ptrA < n || ptrB < n) {
        if (ptrA < n && usedA < usedB || ptrB == n) {
            if (permA[ptrA] == permB[ptrB - 1]) {
                usedA = usedB;
            }
#define touchA() timeA[permA[ptrA]] = usedA, usedA += a[permA[ptrA++]]
#define touchB() timeB[permB[ptrB]] = usedB, usedB += b[permB[ptrB++]]
            touchA();
        } else if (ptrB < n && usedA > usedB || ptrA == n) {
            if (permB[ptrB] == permA[ptrA - 1]) {
                usedB = usedA;
            }
            touchB();
        } else {
            if (permA[ptrA] == permB[ptrB]) {
                if (rand() & 1) {
                    touchA();
                } else {
                    touchB();
                }
            } else {
                touchA();
                touchB();
            }
        }
    }
    return max(usedA, usedB);
}

int main()
{
    n = 10000;
    scanf("%d", &n);
    srand(time(0));
    int lowerBound = 0;
    for (int i = 0; i < n; i++) {
        a[i] = 1 + (rand() & 1023);
        b[i] = 1 + (rand() & 1023);
        scanf("%d%d", a + i, b + i);
        lowerBound = max(lowerBound, a[i] + b[i]);
        permA[i] = i;
    }
    lowerBound = max(lowerBound, accumulate(a, a + n, 0));
    lowerBound = max(lowerBound, accumulate(b, b + n, 0));
    fprintf(stderr, "%d\n", lowerBound);
    int ans = INT_MAX;
    double expireTime = clock() + CLOCKS_PER_SEC * 1.5;
    for (int i = 0; clock() < expireTime && ans > lowerBound; i++) {
        if (i < 2) {
            sort(permA, permA + n, byBminusA);
        } else if (i < 4) {
            sort(permA, permA + n, byAminusB);
        } else if (i < 6) {
            sort(permA, permA + n, byAplusB);
        } else if (i < 8) {
            sort(permA, permA + n, byA);
        } else if (i < 10) {
            sort(permA, permA + n, byB);
        } else {
            random_shuffle(permA, permA + n);
        }
        if (i & 1) {
            memcpy(permB + 1, permA, sizeof(*permA) * (n - 1));
            permB[0] = permA[n - 1];
        } else {
            memcpy(permB, permA, sizeof(*permA) * n);
            reverse(permB, permB + n);
        }
        int res = perform();
        if (res < ans) {
            ans = res;
            memcpy(ansA, timeA, sizeof(*ansA) * n);
            memcpy(ansB, timeB, sizeof(*ansB) * n);
        }
    }
    printf("%d\n", ans);
    //assert(ans == lowerBound);
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", ansA[i], ansB[i]);
    }
}
