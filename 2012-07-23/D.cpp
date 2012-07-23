#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;

template <class T> 
vector <T> permute(vector <T> &v, const int p[4]) {
    vector <T> result(v);
    for (int i = 0; i < 4; ++ i) {
        result[p[(i + 1) % 4]] = v[p[i]];
    }
    return result;
}

int permute(int x, const int p[4]) {
    for (int i = 0; i < 4; ++ i) {
        if (p[i] == x) {
            return p[(i + 1) % 4];
        }
    }
    return x;
}

typedef vector <char> UnitCube;
typedef vector <UnitCube> Cube;

const int ROTATIONS[4][3][4] = {{{0, 1, 5, 4},
                                 {0, 4, 6, 2},
                                 {1, 5, 7, 3}},
                                {{0, 2, 5, 3},
                                 {0, 4, 5, 1},
                                 {2, 6, 7, 3}},
                                {{0, 3, 5, 2},
                                 {1, 5, 4, 0},
                                 {3, 7, 6, 2}},
                                {{0, 4, 5, 1},
                                 {0, 2, 6, 4},
                                 {1, 3, 7, 5}}};

const char ROTATION_NAMES[4] = {'N', 'E', 'W', 'S'};

const int COORDINATES[8][3] = {{0, 1, 1},
                               {0, 0, 1},
                               {1, 1, 1},
                               {1, 0, 1},
                               {0, 1, 0},
                               {0, 0, 0},
                               {1, 1, 0},
                               {1, 0, 0}};

const int DIRECTIONS[6][3] = {{0, 0, 1},
                              {-1, 0, 0},
                              {0, 1, 0},
                              {0, -1, 0},
                              {1, 0, 0},
                              {0, 0, -1}};

int go[8][6];

int getCoordinateID(int x, int y, int z) {
    for (int i = 0; i < 8; ++ i) {
        if (COORDINATES[i][0] == x && COORDINATES[i][1] == y && COORDINATES[i][2] == z) {
            return i;
        }
    }
    return -1;
}

char nextToken() {
    char buffer[2];
    scanf("%s", buffer);
    return *buffer;
}

set <pair <Cube, int> > states;

int main() {
    for (int i = 0; i < 8; ++ i) {
        for (int j = 0; j < 6; ++ j) {
            go[i][j] = getCoordinateID(COORDINATES[i][0] + DIRECTIONS[j][0],
                                       COORDINATES[i][1] + DIRECTIONS[j][1],
                                       COORDINATES[i][2] + DIRECTIONS[j][2]);
        }
    }
    int z_0 = nextToken() == 'T';
    int x_0 = nextToken() == 'S';
    int y_0 = nextToken() == 'E';
    int currentUnitCubeID = getCoordinateID(x_0, y_0, z_0);
    Cube currentCube;
    for (int i = 0; i < 8; ++ i) {
        UnitCube currentUnitCube(6);
        for (int j = 0; j < 6; ++ j) {
            currentUnitCube[j] = nextToken();
        }
        currentCube.push_back(currentUnitCube);
    }
    vector <char> ways;
    states.insert(make_pair(currentCube, currentUnitCubeID));
    while (currentUnitCubeID != -1) {
        char bottom = currentCube[currentUnitCubeID][5];
        if (bottom == 'R') {
            currentUnitCubeID = go[currentUnitCubeID][0];
        } else if (bottom == 'W') {
            if (go[currentUnitCubeID][5] == -1) {
                currentUnitCubeID = go[currentUnitCubeID][0];
            } else {
                currentUnitCubeID = go[currentUnitCubeID][5];
            }
        } else {
            int directionID = 1;
            while (currentCube[currentUnitCubeID][directionID] != 'W') {
                directionID ++;
            }
            if (bottom == 'Y') {
                currentUnitCubeID = go[currentUnitCubeID][directionID];
            }
            directionID --;
            currentUnitCubeID = permute(currentUnitCubeID, ROTATIONS[directionID][1]);
            currentUnitCubeID = permute(currentUnitCubeID, ROTATIONS[directionID][2]);
            currentCube = permute(currentCube, ROTATIONS[directionID][1]);
            currentCube = permute(currentCube, ROTATIONS[directionID][2]);
            for (int i = 0; i < 8; ++ i) {
                currentCube[i] = permute(currentCube[i], ROTATIONS[directionID][0]);
            }
            ways.push_back(ROTATION_NAMES[directionID]);
        }
        pair <Cube, int> newState = make_pair(currentCube, currentUnitCubeID);
        if (states.find(newState) == states.end()) {
            states.insert(newState);
        } else {
            puts("-1");
            return 0;
        }
    }
    printf("%d", (int)ways.size());
    for (int i = 0; i < (int)ways.size(); ++ i) {
        printf(" %c", ways[i]);
    }
    puts("");
    return 0;
}
