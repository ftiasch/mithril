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

const double eps = 1e-8;

#define DET(x1, y1, x2, y2) ((x1) * (y2) - (x2) * (y1))

struct Point
{
    double x, y, z;

    Point(){}
    Point(double x, double y, double z) : x(x), y(y), z(z){}

    bool operator<(const Point &o) const {
        return x + eps < o.x || x < o.x + eps &&
            (y + eps < o.y || y < o.y + eps && z + eps < o.z);
    }

    inline double dot(const Point &o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    inline Point det(const Point &o) const {
        return Point(DET(y, z, o.y, o.z), DET(z, x, o.z, o.x), DET(x, y, o.x, o.y));
    }

    void read() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
};

vector<Point> face[1000];
int faceCount;

map<pair<Point,Point>, vector<int> > mapping;

int main()
{
    int cases;
    while (scanf("%d", &cases) == 1 && cases) {
        double ans = 0;
        while (cases --) {
            double sum = 0;
            scanf("%d", &faceCount);
            for (int i = 0; i < faceCount; i++) {
                int verticeCount;
                scanf("%d", &verticeCount);
                face[i].resize(verticeCount);
                for (int j = 0; j < verticeCount; j++) {
                    face[i][j].read();
                }
            }
            mapping.clear();
            for (int i = 0; i < faceCount; i++) {
                int n = face[i].size();
                for (int j = 0; j < n; j++) {
                    int k = (j + 1) % n;
                    mapping[make_pair(face[i][j], face[i][k])].push_back(i * 2 + 0);
                    mapping[make_pair(face[i][k], face[i][j])].push_back(i * 2 + 1);
                }
            }
            FOR (it, mapping) {
                assert(it->second.size() == 2);
            }
            vector<int> visited(faceCount, -1);
            visited[0] = 1;
            queue<int> Q;
            Q.push(0);
            while (!Q.empty()) {
                int p = Q.front();
                Q.pop();
                int n = face[p].size();
                for (int i = 0; i < n; i++) {
                    int j = (i + 1) % n;
                    const vector<int> &ref = mapping[visited[p] == 0 ? make_pair(face[p][i], face[p][j]) : make_pair(face[p][j], face[p][i])];
                    int target = ref[0] ^ ref[1] ^ (p * 2 + visited[p]) ^ 1;
                    if (visited[target >> 1] < 0) {
                        visited[target >> 1] = target & 1;
                        Q.push(target >> 1);
                    } else {
                        assert(visited[target >> 1] == (target & 1));
                    }
                }
            }
            for (int i = 0; i < faceCount; i++) {
                assert(visited[i] >= 0);
                if (visited[i]) {
                    reverse(face[i].begin(), face[i].end());
                }
                for (int j = 1; j + 1 < face[i].size(); j++) {
                    int k = j + 1;
                    sum += face[i][0].dot(face[i][j].det(face[i][k]));
                }
            }
            ans += fabs(sum / 6);
        }
        printf("%.2f\n", fabs(ans));
    }
}
