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

const int maxn = 9;

int n, m, colors;

int conn[maxn][maxn];

bool checkPerm(int perm[])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (conn[i][j] != conn[perm[i]][perm[j]]) {
                return false;
            }
        }
    return true;
}

int solvePerm(int perm[])
{
    static bool visited[maxn];
    memset(visited, false, sizeof(visited));
    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            ret ++;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = perm[j];
            }
        }
    }
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &colors);
    memset(conn, 0, sizeof(conn));
    for (int i = 0; i < m; i++) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        ai--, bi--;
        conn[ai][bi] ++;
        conn[bi][ai] ++;
    }
    int perm[maxn];
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    long long sum = 0, cnt = 0;
    do {
        if (checkPerm(perm)) {
            cnt ++;
            int num = solvePerm(perm);
            long long mul = 1;
            while (num --) {
                mul *= colors;
            }
            sum += mul;
        }
    } while (next_permutation(perm, perm + n));
    assert(sum % cnt == 0);
    cout << sum / cnt << endl;
}
