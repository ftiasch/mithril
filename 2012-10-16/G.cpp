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

#define WAYS (24)

int dx[WAYS], dy[WAYS], dz[WAYS];

struct Triple {
    int numbers[3];

    Triple() {}

    Triple(int a, int b, int c) {
        numbers[0] = a;
        numbers[1] = b;
        numbers[2] = c;
    }

    Triple perm(int A, int B, int C) const {
        return Triple(numbers[A], numbers[B], numbers[C]);
    }

    bool operator==(const Triple &o) const {
        return numbers[0] == o.numbers[0] && numbers[1] == o.numbers[1] && numbers[2] == o.numbers[2];
    }

};

istream &operator>>(istream &in, Triple &a)
{
    return in >> a.numbers[0] >> a.numbers[1] >> a.numbers[2];
}

vector<pair<Triple, vector<Triple> > > prepared;

void addCase(const Triple &a, string s)
{
    istringstream ssin(s);
    vector<Triple> ans;
    for (Triple ai; ssin >> ai; ans.push_back(ai));
    for (int A = 0; A < 3; A++) {
        for (int B = 0; B < 3; B++) {
            for (int C = 0; C < 3; C++) {
                if (A != B && B != C && A != C) {
                    Triple a2 = a.perm(A, B, C);
                    vector<Triple> ans2 = ans;
                    for (int i = 0; i < ans2.size(); i++) {
                        ans2[i] = ans2[i].perm(A, B, C);
                    }
                    prepared.push_back(make_pair(a2, ans2));
                }
            }
        }
    }
}

void prepare()
{
    addCase(Triple(2, 3, 5), "1 1 1 1 2 3 2 2 1 2 1 3 2 2 5 2 3 3 1 1 3 1 2 1 1 3 3 1 1 2 1 3 1 2 1 1 2 3 2 1 3 4 1 1 5 2 3 5 2 1 4 2 2 2 1 2 4 1 3 2 2 3 4 2 1 5 1 3 5 1 1 4 1 2 2 2 2 4 2 1 2 2 3 1 2 2 3 1 2 5");
    addCase(Triple(2, 5, 5), "1 1 1 1 2 3 1 1 5 1 3 4 1 1 3 1 2 1 1 3 3 1 1 2 1 2 4 1 3 2 1 4 4 1 2 5 2 2 3 1 4 3 1 2 2 1 1 4 2 1 2 2 2 4 2 4 5 2 3 3 2 4 1 2 2 2 2 1 4 2 3 5 1 5 5 2 5 3 1 5 1 2 3 1 2 5 2 1 5 4 1 4 2 2 4 4 2 2 5 1 4 5 1 5 3 1 4 1 2 2 1 2 1 3 2 3 2 1 5 2 2 5 4 2 4 2 2 3 4 2 1 5 1 3 5 2 5 5 2 4 3 2 5 1 1 3 1 2 1 1");
    addCase(Triple(3, 5, 5), "1 1 1 1 2 3 1 1 5 1 3 4 1 1 3 1 2 1 1 3 3 1 1 2 1 2 4 1 3 2 1 4 4 1 2 5 2 2 3 1 4 3 1 2 2 1 1 4 1 3 5 1 5 4 1 4 2 2 2 2 2 1 4 2 3 3 1 3 1 1 5 2 2 3 2 2 1 1 3 1 3 2 1 5 2 3 4 2 1 3 2 2 1 1 4 1 1 5 3 1 4 5 2 2 5 2 4 4 2 5 2 2 3 1 1 5 1 2 5 3 1 5 5 2 3 5 2 4 3 2 5 1 3 3 1 3 1 2 3 2 4 3 4 5 3 3 3 3 1 4 2 1 2 2 2 4 2 4 5 3 2 5 3 4 4 3 5 2 2 5 4 2 4 2 3 2 2 3 4 1 3 5 3 2 5 5 3 3 5 3 5 4 3 4 2 3 2 1 2 4 1 3 4 3 3 5 1 3 3 2 3 1 1 3 2 3 3 1 5 3 3 4 3 5 5");
    addCase(Triple(4, 5, 5), "1 1 1 1 2 3 1 1 5 1 3 4 1 1 3 1 2 1 1 3 3 1 1 2 1 2 4 1 3 2 1 4 4 1 2 5 2 2 3 1 4 3 1 2 2 1 1 4 1 3 5 1 5 4 1 4 2 2 2 2 2 1 4 2 3 3 1 3 1 1 5 2 2 3 2 2 1 1 3 1 3 2 1 5 2 3 4 2 1 3 2 2 1 1 4 1 1 5 3 1 4 5 2 2 5 2 4 4 2 5 2 2 3 1 1 5 1 2 5 3 1 5 5 2 3 5 2 4 3 2 2 4 2 1 2 3 1 4 3 2 2 2 4 2 2 5 4 3 3 4 3 1 5 3 2 3 3 1 1 3 3 2 3 2 4 3 1 2 3 3 1 2 5 1 3 5 3 2 5 5 3 3 5 3 4 3 2 4 1 3 2 1 3 3 3 3 4 1 4 2 1 4 1 3 4 2 5 3 4 5 4 4 3 4 5 1 4 3 2 3 5 2 4 5 4 4 4 2 3 4 4 3 2 5 4 4 5 4 2 4 4 1 2 4 3 1 3 5 1 4 5 3 3 5 5 4 3 5 4 1 4 4 2 2 4 4 1 4 3 3 4 5 2 3 5 4 3 4 2 4 4 4 2 4 5 4 5 5 4 3 4 4 1 5 4 2 3 4 1 1");
    addCase(Triple(5, 5, 5), "1 1 1 1 2 3 1 1 5 1 3 4 1 1 3 1 2 1 1 3 3 1 1 2 1 2 4 1 3 2 1 4 4 1 2 5 2 2 3 1 4 3 1 2 2 1 1 4 1 3 5 1 5 4 1 4 2 2 2 2 2 1 4 2 3 3 1 3 1 1 5 2 2 3 2 2 1 1 3 1 3 2 1 5 2 3 4 2 1 3 2 2 1 1 4 1 1 5 3 1 4 5 2 2 5 2 4 4 2 5 2 2 3 1 1 5 1 2 5 3 1 5 5 2 3 5 2 4 3 2 2 4 2 1 2 3 1 4 3 2 2 2 4 2 2 5 4 3 3 4 3 1 5 3 2 3 3 1 1 3 3 2 3 2 4 3 1 2 3 3 1 2 5 1 3 5 3 2 5 5 3 3 5 3 4 3 2 4 1 3 2 1 3 3 3 3 2 5 2 4 5 4 3 5 3 5 5 4 5 3 3 5 1 4 3 1 4 1 2 4 2 4 3 4 4 3 5 2 4 3 2 4 1 1 4 2 3 4 1 5 4 3 4 3 5 4 3 4 2 4 2 2 4 1 4 4 3 3 4 2 1 3 4 1 4 4 3 3 4 5 5 5 5 5 3 4 4 5 4 4 4 2 5 4 4 5 5 2 5 3 1 4 5 1 5 5 3 4 5 5 5 3 5 5 1 4 5 2 2 5 4 1 5 3 3 5 1 2 5 2 4 5 4 5 4 2 5 4 4 4 4 5 2 5 5 4 5 4 2 5 2 3 5 1 5 4 1 3 5 1 1 5 3 2 5 5 1 5 4 3 4 4 1 5 2 1 5 1 3 5 2 5 4 4 5");
    int cnt = 0;
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            if (abs(x) == abs(y)) {
                continue;
            }
            for (int z = -2; z <= 2; z++) {
                if (abs(x) == abs(z) || abs(y) == abs(z)) {
                    continue;
                }
                assert(cnt < WAYS);
                dx[cnt] = x;
                dy[cnt] = y;
                dz[cnt] = z;
                cnt ++;
            }
        }
    }
    assert(cnt == WAYS);
}

int vis[5][5][5];
int flag[5][5][5], flags;
int Q[5*5*5][3], head, tail;

int X, Y, Z;

bool check(int dep, int x, int y, int z)
{
    flags++;
    head = tail = 0;
    Q[tail][0] = x, Q[tail][1] = y, Q[tail][2] = z, tail++;
    flag[x][y][z] = flags;
    while (head < tail) {
        x = Q[head][0];
        y = Q[head][1];
        z = Q[head][2];
        head ++;
        for (int i = 0; i < WAYS; i++) {
            int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
            if (nx < 0 || nx >= X || ny < 0 || ny >= Y || nz < 0 || nz >= Z) {
                continue;
            }
            if (vis[nx][ny][nz] >= 0 || flag[nx][ny][nz] == flags) {
                continue;
            }
            flag[nx][ny][nz] = flags;
            Q[tail][0] = nx, Q[tail][1] = ny, Q[tail][2] = nz, tail++;
        }
    }
    return dep + tail == X * Y * Z + 1;
}

bool search(int dep, int x, int y, int z)
{
    if ((dep & 3) == 1 && !check(dep, x, y, z)) {
        return false;
    }
    vis[x][y][z] = dep;
    if (dep == X * Y * Z) {
        return true;
    }
    for (int i = 0; i < WAYS; i++) {
        int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
        if (nx < 0 || nx >= X || ny < 0 || ny >= Y || nz < 0 || nz >= Z) {
            continue;
        }
        if (vis[nx][ny][nz] >= 0) {
            continue;
        }
        if (search(dep + 1, nx, ny, nz)) {
            return true;
        }
    }
    vis[x][y][z] = -1;
    return false;
}

bool solve(int X, int Y, int Z)
{
    ::X = X, ::Y = Y, ::Z = Z;
    memset(vis, -1, sizeof(vis));
    return search(1, 0, 0, 0);
}

int main()
{
    prepare();
    int X, Y, Z;
    scanf("%d%d%d", &X, &Y, &Z);
    Triple triple(X, Y, Z);
    for (int i = 0; i < prepared.size(); i++) {
        if (triple == prepared[i].first) {
            puts("YES");
            for (int j = 0; j < prepared[i].second.size(); j++) {
                Triple &ref = prepared[i].second[j];
                printf("%d %d %d\n", ref.numbers[0], ref.numbers[1], ref.numbers[2]);
            }
            return 0;
        }
    }
    if (!solve(X, Y, Z)) {
        puts("NO");
    } else {
        puts("YES");
        for (int i = 1; i <= X * Y * Z; i++) {
            for (int x = 0; x < X; x++) {
                for (int y = 0; y < Y; y++) {
                    for (int z = 0; z < Z; z++) {
                        if (vis[x][y][z] == i) {
                            printf("%d %d %d\n", x + 1, y + 1, z + 1);
                        }
                    }
                }
            }
        }
    }
}
