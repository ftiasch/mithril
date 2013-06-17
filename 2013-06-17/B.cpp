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
using namespace std;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

#define PUTS(s) puts(s); fflush(stdout);

//#define LOCAL

int n, C;
int value, newValue;

#ifdef LOCAL
int w[20], mask, newMask;
#endif

int samples = 0;
map<int,int> counter;

void initialize()
{
#ifdef LOCAL
    int seed;
    scanf("%d", &seed);
    srand(seed);
    n = 20;
    value = 0;
    printf("N = %d\n", n);
    for (int i = 0; i < n; i++) {
        w[i] = (unsigned)rand() % 100000000 + 1;
        value += w[i];
    }
    C = value / 2;
    printf("C = %d\n", C);
    sort(w, w + n);
    for (int i = 0; i < n; i++) {
        printf("w[%d] = %d\n", i, w[i]);
    }
    mask = (1 << n) - 1;
#else
    scanf("%d%d%d", &n, &C, &value);
    PUTS("accept");
#endif
}

int read()
{
#ifdef LOCAL
    newMask = mask ^ 1 << ((unsigned)rand() % n);
    newValue = 0;
    for (int i = 0; i < n; i++) {
        if (newMask >> i & 1) {
            newValue += w[i];
        }
    }
#else
    scanf("%d", &newValue);
#endif
    samples ++;
    counter[abs(newValue - value)] ++;
    return newValue;
}

void accept()
{
#ifdef LOCAL
    value = newValue;
    mask = newMask;
#else
    PUTS("accept");
    value = newValue;
#endif
}

void decline()
{
#ifndef LOCAL
    PUTS("decline");
#endif
}

void stop()
{
#ifdef LOCAL
    printf("last = %d\n", newValue);
    printf("turns = %d\n", samples + 1);
#else
    PUTS("stop");
#endif
    exit(0);
}

int sum[1 << 20];

int main()
{
    initialize();
    while (samples < 700) {
        if (read() > value) {
            accept();
        } else {
            decline();
        }
    }
    vector<int> w;
    while (value != 0) {
        if (read() < value) {
            w.push_back(value - newValue);
            accept();
        } else {
            decline();
        }
    }
    /*while (samples < 850 || samples % n != 0) {
        read();
        decline();
    }
    int unit = samples / n;
    FOR (it, counter) {
        it->second -= unit;
        w.push_back(it->first);
    }
    while (w.size() < n) {
        int fst = -1, snd = -1;
        FOR (it, counter) {
            if (fst < 0 || it->second > snd) {
                fst = it->first;
                snd = it->second;
            }
        }
        w.push_back(fst);
        counter[fst] -= unit;
    }*/
    assert(w.size() == n);
    sort(w.begin(), w.end());
#ifdef LOCAL
    for (int i = 0; i < n; i++) {
        if (w[i] != ::w[i]) {
            puts("ERROR");
        }
    }
#endif
    sum[0] = 0;
    int targetMask = 0;
    for (int i = 1; i < 1 << n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) {
                sum[i] = sum[i ^ 1 << j] + w[j];
                break;
            }
        }
        if (sum[i] <= C && sum[i] > sum[targetMask]) {
            targetMask = i;
        }
    }
    int nowMask = 0;
    if (targetMask == 0) {
        read();
        accept();
        while (read() != 0) {
            decline();
        }
        stop();
    }
    while (true) {
        read();
        if (newValue < value) {
            decline();
            continue;
        }
        int delta = newValue - value;
        int pos = -1;
        for (int i = 0; i < n; i++) {
            if (~nowMask >> i & 1 && w[i] == delta) {
                pos = i;
                break;
            }
        }
        assert(pos >= 0);
        if (targetMask >> pos & 1) {
            nowMask |= 1 << pos;
            if (nowMask == targetMask) {
                stop();
            } else {
                accept();
            }
        } else {
            decline();
        }
    }
}
