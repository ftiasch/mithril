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

#include <ext/hash_map>
using namespace __gnu_cxx;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int inf = 1000000000;

string readString()
{
    string s;
    cin >> s;
    return s;
}

const int MAXT = 10;
const int MAXR = 10;
const int MAXA = 30;

int terrains;
map<string,int> terrainID;
string terrain[MAXT];

int races;
map<string,int> raceID;
struct Race {
    string name;
    vector<string> ability;

    void read(int id) {
        cin >> name;
        raceID[name] = id;
        int n;
        cin >> n;
        ability.resize(n);
        static char buf[1 << 10];
        fgets(buf, 1 << 10, stdin);
        FOR (it, ability) {
            fgets(buf, 1 << 10, stdin);
            *it = buf;
        }
    }

    int defence;
    int defenceOn[MAXT];
    int defenceNear[MAXT];
    int defenceVersus[MAXR];
    int attack;
    int attackOn[MAXT];
    int attackNear[MAXT];
    int attackVersus[MAXR];
    int points;
    int pointsOn[MAXT];
    int pointsForConquest;

    void parse() {
        FOR (line, ability) {
            istringstream ssin(*line);
            int value;
            string nextToken;
            ssin >> value;
            ssin >> nextToken;
            if (nextToken == "defence") {
                if (ssin >> nextToken) {
                    if (nextToken == "on") {
                        ssin >> nextToken;
                        defenceOn[terrainID[nextToken]] += value;
                    } else if (nextToken == "near") {
                        ssin >> nextToken;
                        defenceNear[terrainID[nextToken]] += value;
                    } else if (nextToken == "versus") {
                        ssin >> nextToken;
                        defenceVersus[raceID[nextToken]] += value;
                    } else {
                        assert(false);
                    }
                } else {
                    defence += value;
                }
            } else if (nextToken == "attack") {
                if (ssin >> nextToken) {
                    if (nextToken == "on") {
                        ssin >> nextToken;
                        attackOn[terrainID[nextToken]] += value;
                    } else if (nextToken == "near") {
                        ssin >> nextToken;
                        attackNear[terrainID[nextToken]] += value;
                    } else if (nextToken == "versus") {
                        ssin >> nextToken;
                        attackVersus[raceID[nextToken]] += value;
                    } else {
                        assert(false);
                    }
                } else {
                    attack += value;
                }
            } else if (nextToken == "points") {
                if (ssin >> nextToken) {
                    if (nextToken == "on") {
                        ssin >> nextToken;
                        pointsOn[terrainID[nextToken]] += value;
                    } else if (nextToken == "for") {
                        pointsForConquest += value;
                    } else {
                        assert(false);
                    }
                } else {
                    points += value;
                }
            } else {
                assert(false);
            }
        }
    }
} race[MAXR];

int areas;
struct Area {
    int terrainType;
    bool isBorder;
    int initialRace;
    int initialUnits;
    vector<int> adjacentArea;

    vector<int> adjacentTerrain;

    void read(int id) {
        terrainType = terrainID[readString()];
        isBorder = readString() == "border";
        initialRace = raceID[readString()];
        if (initialRace == -1) {
            initialUnits = 0;
        } else {
            cin >> initialUnits;
        }
        int n;
        cin >> n;
        adjacentArea.resize(n);
        FOR (it, adjacentArea) {
            cin >> *it;
            (*it)--;
        }
    }

} area[MAXA];

int yourUnits, yourRace;

int conquest(int target)
{
    const Area &targetArea = area[target];
    const Race &attackRace = race[yourRace];
    int now = 2 + targetArea.initialUnits;
    if (targetArea.initialRace >= 0) {
        const Race &defenceRace = race[targetArea.initialRace];
        now += defenceRace.defence;
        now += defenceRace.defenceOn[targetArea.terrainType];
        FOR (it, targetArea.adjacentTerrain) {
            now += defenceRace.defenceNear[*it];
        }
        now += defenceRace.defenceVersus[yourRace];
        now -= attackRace.attackVersus[targetArea.initialRace];
    }
    now -= attackRace.attack;
    now -= attackRace.attackOn[targetArea.terrainType];
    FOR (it, targetArea.adjacentTerrain) {
        now -= attackRace.attackNear[*it];
    }
    return max(now, 1);
}

int needUnits[MAXA];
int benifit[MAXA];

hash_map<int,int> memo[11];

int go(int units, int mask)
{
    if (memo[units].count(mask)) {
        return memo[units][mask];
    }
    int ret = 0;
    for (int i = 0; i < areas; i++) {
        if (mask >> i & 1) {
            continue;
        }
        if (needUnits[i] > units) {
            continue;
        }
        bool okay = false;
        if (mask == 0) {
            if (area[i].isBorder) {
                okay = true;
            }
        } else {
            FOR (it, area[i].adjacentArea) {
                if (mask >> *it & 1) {
                    okay = true;
                    break;
                }
            }
        }
        if (okay) {
            ret = max(ret, go(units - needUnits[i], mask | 1 << i) + benifit[i]);
        }
    }
    return memo[units][mask] = ret;
}

int main()
{
    cin >> terrains >> races >> areas >> yourUnits;
    for (int i = 0; i < terrains; i++) {
        cin >> terrain[i];
        terrainID[terrain[i]] = i;
    }
    for (int i = 0; i < races; i++) {
        race[i].read(i);
    }
    raceID["empty"] = -1;
    for (int i = 0; i < areas; i++) {
        area[i].read(i);
    }
    for (int i = 0; i < areas; i++) {
        set<int> tset;
        FOR (it, area[i].adjacentArea) {
            tset.insert(area[*it].terrainType);
        }
        area[i].adjacentTerrain.assign(tset.begin(), tset.end());
    }
    yourRace = raceID[readString()];
    for (int i = 0; i < races; i++) {
        race[i].parse();
    }
    for (int i = 0; i < areas; i++) {
        needUnits[i] = conquest(i);
        benifit[i] = 1 + race[yourRace].points;
        benifit[i] += race[yourRace].pointsOn[area[i].terrainType];
        if (area[i].initialRace >= 0) {
            benifit[i] += race[yourRace].pointsForConquest;
        }
    }
    printf("%d\n", go(yourUnits, 0));
}
