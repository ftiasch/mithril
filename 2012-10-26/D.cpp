#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 30;

int n;
char source[N + 1], target[N + 1];

typedef unsigned long long ULL;

const ULL MAGIC = 217;

ULL power[N + 1];

void dfs(char *s, int depth, ULL hash, vector <ULL> &hashes) {
    hashes.push_back(hash);
    if (depth >= 2) {
        return;
    }
    for (int sum = 0; sum <= n - 1 << 1; ++ sum) {
        for (int i = sum >> 1, j = sum - i; i >= 0 && j < n; -- i, ++ j) {
            hash -= s[i] * power[i];
            hash -= s[j] * power[j];
            swap(s[i], s[j]);
            hash += s[i] * power[i];
            hash += s[j] * power[j];
            dfs(s, depth + 1, hash, hashes);
        }
        for (int i = sum >> 1, j = sum - i; i >= 0 && j < n; -- i, ++ j) {
            hash -= s[i] * power[i];
            hash -= s[j] * power[j];
            swap(s[i], s[j]);
            hash += s[i] * power[i];
            hash += s[j] * power[j];
        }
    }
}

vector <ULL> sourceSide, targetSide;

int main() {
    scanf("%s%s", source, target);
    n = strlen(source);
    power[0] = 1;
    for (int i = 1; i < n; ++ i) {
        power[i] = power[i - 1] * MAGIC;
    }
    ULL init = 0;
    for (int i = 0; i < n; ++ i) {
        init += power[i] * source[i];
    }
    dfs(source, 0, init, sourceSide);
    init = 0;
    for (int i = 0; i < n; ++ i) {
        init += power[i] * target[i];
    }
    dfs(target, 0, init, targetSide);
    sort(sourceSide.begin(), sourceSide.end());
    sort(targetSide.begin(), targetSide.end());
    bool found = false;
    for (int i = 0, j = 0; i < (int)sourceSide.size() && j < (int)targetSide.size() && !found; ++ i) {
        while (j < (int)targetSide.size() && sourceSide[i] > targetSide[j]) {
            j ++;
        }
        if (j < (int)targetSide.size() && sourceSide[i] == targetSide[j]) {
            found = true;
        }
    }
    puts(found ? "Similar" : "Different");
    return 0;
}
