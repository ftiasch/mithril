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

const int maxn = 10000;
const int maxk = 10;

int p3[11];
vector<int> scores[59049];

int readMask()
{
    int n, ret = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int ai;
        scanf("%d", &ai);
        ret |= 1 << ai - 1;
    }
    return ret;
}

int n, k, m;

int score[maxn], mask[maxn];

int main()
{
    p3[0] = 1;
    for (int i = 0; i < maxk; i++) {
        p3[i + 1] = p3[i] * 3;
    }
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", score + i);
        score[i] *= -1;
        mask[i] = readMask();
        for (int msk = 0; msk < 1 << k; msk++) {
            int mask3 = 0;
            for (int j = 0; j < k; j++) {
                if (msk >> j & 1) {
                    mask3 += p3[j] * (mask[i] >> j & 1);
                } else {
                    mask3 += p3[j] * 2;
                }
            }
            scores[mask3].push_back(score[i]);
        }
    }
    for (int i = 0; i < p3[k]; i++) {
        sort(scores[i].begin(), scores[i].end());
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int id, msk;
        scanf("%d", &id);
        id --;
        msk = readMask();
        int mask3 = 0;
        for (int j = 0; j < k; j++) {
            if (msk >> j & 1) {
                mask3 += p3[j] * (mask[id] >> j & 1);
            } else {
                mask3 += p3[j] * 2;
            }
        }
        int num = lower_bound(scores[mask3].begin(), scores[mask3].end(), score[id]) - scores[mask3].begin();
        printf("%d\n", num + 1);
    }
}
