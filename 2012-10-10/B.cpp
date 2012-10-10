#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000;
const int M = 100000;

typedef long long LL;

struct Point {
    LL x, y, z;

    Point(LL x = 0, LL y = 0, LL z = 0): x(x), y(y), z(z) {}

    Point &operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        z -= o.z;
        return *this;
    }
};

Point operator -(Point a, const Point &b) {
    return a -= b;
}

Point det(const Point &a, const Point &b) {
    return Point(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z, 
                 a.x * b.y - a.y * b.x);
}

LL dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

LL volume(const Point &a, const Point &b, const Point &c) {
    return dot(det(a, b), c);
}

int n, m;
Point points[N];
vector <int> faces[M];
map <pair <int, int>, vector <int> > adjacent;

pair <int, int> make_ordered_pair(int a, int b) {
    return a < b ? make_pair(a, b) : make_pair(b, a);
}

bool known[M];

#define foreach(i, v) for (typeof((v).begin()) i = (v).begin(); \
        i != (v).end(); ++ i) 

int main() {
    freopen("bomb.in", "r", stdin);
    freopen("bomb.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        points[i] = Point(x, y, z);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++ i) {
        vector <int> &face = faces[i];
        face.resize(3);
        for (int j = 0; j < 3; ++ j) {
            scanf("%d", &face[j]);
            face[j] --;
        }
        for (int j = 0; j < 3; ++ j) {
            adjacent[make_ordered_pair(face[j], face[(j + 1) % 3])].push_back(i);
        }
    }
    memset(known, 0, sizeof(known));
    known[0] = true;
    queue <int> q;
    q.push(0);
    vector <long long> volumes;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vector <int> &face = faces[u];
        volumes.push_back(volume(points[face[0]], points[face[1]], points[face[2]]));
        for (int i = 0; i < 3; ++ i) {
            pair <int, int> edge = make_ordered_pair(face[i], face[(i + 1) % 3]);
            foreach(iter, adjacent[edge]) {
                int v = *iter;
                if (!known[v]) {
                    vector <int> &face2 = faces[v];
                    bool found = false;
                    for (int j = 0; j < 3; ++ j) {
                        found |= make_pair(face[i], face[(i + 1) % 3]) == make_pair(face2[j], face2[(j + 1) % 3]);
                    }
                    if (found) {
                        reverse(face2.begin(), face2.end());
                    }
                    q.push(v);
                    known[v] = true;
                }
            }
        }
    }
//for (int i = 0; i < m; ++ i) {
//    vector <int> &face = faces[i];
//    printf("%d, %d, %d\n", face[0], face[1], face[2]);
//}
//for (int i = 0; i < m; ++ i) {
//    cout << volumes[i] << endl;
//}
    long long answer = 0;
    sort(volumes.begin(), volumes.end());
    for (int i = 0, j = (int)volumes.size(); i < j; ) {
        if (answer < 0) {
            answer += volumes[-- j];
        } else { 
            answer += volumes[i ++];
        }
    }
    answer = abs(answer);
    cout << answer / 6 << ".";
    answer %= 6;
    char buffer[20];
    sprintf(buffer, "%.10f", (double)answer / 6);
    printf("%s\n", buffer + 2);
    return 0;
}
