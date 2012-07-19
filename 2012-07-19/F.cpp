// Problem F -- Lock
// Author: Bin Jin
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

struct Block
{
    int x, y, z;

    Block(int x, int y, int z) : x(x), y(y), z(z) { }

    void rotX() {
        swap(y, z);
        y = -y;
    }

    void rotY() {
        swap(x, z);
        x = -x;
    }

    void rotZ() {
        swap(x, y);
        x = -x;
    }

    bool operator<(const Block &o) const {
        return x < o.x || x == o.x && (y < o.y || y == o.y && 
                z < o.z);
    }

    bool operator==(const Block &o) const {
        return x == o.x && y == o.y && z == o.z;
    }
};

struct Blocks
{
    vector<Block> blocks;

    int minX, minY, minZ;
    int maxX, maxY, maxZ;

    void rotX() {
        for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
            it->rotX();
        }
    }

    void rotY() {
        for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
            it->rotY();
        }
    }

    void rotZ() {
        for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
            it->rotZ();
        }
    }

    void normalize() {
        sort(blocks.begin(), blocks.end());
        maxX = maxY = maxZ = 0;
        minX = minY = minZ = 0;
        for (int i = (int)blocks.size() - 1; i >= 0; i--) {
            blocks[i].x -= blocks[0].x;
            blocks[i].y -= blocks[0].y;
            blocks[i].z -= blocks[0].z;
            minX = min(minX, blocks[i].x);
            minY = min(minY, blocks[i].y);
            minZ = min(minZ, blocks[i].z);
            maxX = max(maxX, blocks[i].x);
            maxY = max(maxY, blocks[i].y);
            maxZ = max(maxZ, blocks[i].z);
        }
    }

    Block &operator[](int p) {
        return blocks[p];
    }

    int size() const {
        return blocks.size();
    }

    const Block &operator[](int p) const {
        return blocks[p];
    }

    bool operator<(const Blocks &o) const {
        return blocks < o.blocks;
    }

    bool operator==(const Blocks &o) const {
        return blocks == o.blocks;
    }
};

Blocks base1()
{
    Blocks ret;
    ret.blocks.push_back(Block(0, 0, 0));
    ret.blocks.push_back(Block(0, 1, 0));
    ret.blocks.push_back(Block(0, 0, 1));
    return ret;
}

Blocks base2()
{
    Blocks ret;
    ret.blocks.push_back(Block(0, 0, 0));
    ret.blocks.push_back(Block(0, 0, 1));
    ret.blocks.push_back(Block(0, 1, 0));
    ret.blocks.push_back(Block(0, 0, -1));
    return ret;
}

Blocks base3()
{
    Blocks ret;
    ret.blocks.push_back(Block(0, 0, 0));
    ret.blocks.push_back(Block(0, 1, 0));
    ret.blocks.push_back(Block(0, 1, 1));
    ret.blocks.push_back(Block(0, 2, 1));
    return ret;
}

Blocks base4()
{
    Blocks ret;
    ret.blocks.push_back(Block(0, 0, 0));
    ret.blocks.push_back(Block(0, 1, 0));
    ret.blocks.push_back(Block(0, 2, 0));
    ret.blocks.push_back(Block(0, 0, 1));
    return ret;
}

Blocks base5()
{
    Blocks ret;
    ret.blocks.push_back(Block(0, 0, 0));
    ret.blocks.push_back(Block(0, 1, 0));
    ret.blocks.push_back(Block(0, 1, 1));
    ret.blocks.push_back(Block(1, 0, 0));
    return ret;
}

Blocks base6()
{
    Blocks ret;
    ret.blocks.push_back(Block(0, 0, 0));
    ret.blocks.push_back(Block(0, 1, 0));
    ret.blocks.push_back(Block(0, 1, 1));
    ret.blocks.push_back(Block(-1, 0, 0));
    return ret;
}

Blocks base7()
{
    Blocks ret;
    ret.blocks.push_back(Block(0, 0, 0));
    ret.blocks.push_back(Block(0, 0, 1));
    ret.blocks.push_back(Block(0, 1, 0));
    ret.blocks.push_back(Block(1, 0, 0));
    return ret;
}

vector<Blocks> prepared[7];

vector<Blocks> prepare(Blocks a)
{
    vector<Blocks> ret;
    for (int i = 0; i < 4; i++, a.rotX())
        for (int j = 0; j < 4; j++, a.rotY())
            for (int k = 0; k < 4; k++, a.rotZ()) {
                a.normalize();
                ret.push_back(a);
            }
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

void prepare()
{
    prepared[0] = prepare(base1());
    prepared[1] = prepare(base2());
    prepared[2] = prepare(base3());
    prepared[3] = prepare(base4());
    prepared[4] = prepare(base5());
    prepared[5] = prepare(base6());
    prepared[6] = prepare(base7());
}

const int MAXN = 20;

bool remaining[MAXN][MAXN][MAXN];
int ans[MAXN][MAXN][MAXN];

int X, Y, Z;

bool dfs(int x, int y, int z, int msk)
{
    while (!remaining[x][y][z]) {
        if (++z == Z) {
            z = 0;
            if (++y == Y) {
                y = 0;
                if (++x == X)
                    return (msk + 1) == (1 << 7);
            }
        }
    }
    for (int i = 0; i < 7; i++) {
        if (msk >> i & 1)
            continue;
        for (int j = 0; j < prepared[i].size(); j++) {
            const Blocks &ref = prepared[i][j];
            if (ref.maxX + x >= X || ref.maxY + y >= Y || ref.maxZ + z >= Z) {
                continue;
            }
            if (ref.minX + x < 0 || ref.minY + y < 0 || ref.minZ + z < 0) {
                continue;
            }
            bool valid = true;
            for (int k = 0; k < ref.size(); k++) {
                if (!remaining[x+ref[k].x][y+ref[k].y][z+ref[k].z]) {
                    valid = false;
                    break;
                }
            }
            if (!valid)
                continue;
            for (int k = 0; k < ref.size(); k++) {
                remaining[x+ref[k].x][y+ref[k].y][z+ref[k].z] = false;
                ans[x+ref[k].x][y+ref[k].y][z+ref[k].z] = i;
            }
            if (dfs(x, y, z, msk | 1 << i))
                return true;
            for (int k = 0; k < ref.size(); k++) {
                remaining[x+ref[k].x][y+ref[k].y][z+ref[k].z] = true;
            }
        }
    }
    return false;
}


int main()
{
    prepare();
    while (scanf("%d%d%d", &X, &Y, &Z) == 3) {
        memset(remaining, false, sizeof(remaining));
        for (int x = 0; x < X; x++) {
            for (int y = 0; y < Y; y++) {
                for (int z = 0; z < Z; z++) {
                    int axyz;
                    scanf("%d", &axyz);
                    if (axyz != 0) {
                        remaining[x][y][z] = true;
                    }
                }
            }
        }
        memset(ans, -1, sizeof(ans));
        if (!dfs(0, 0, 0, 0)) {
            vector<int> a(0);
            return a[10000];
            //puts("No Solution");
        } else {
            for (int i = 0; i < X; i++) {
                if (i > 0)
                    puts("");
                for (int j = 0; j < Y; j++) {
                    for (int k = 0; k < Z; k++)
                        printf("%d", ans[i][j][k]+1);
                    puts("");
                }
            }
        }
    }
}
