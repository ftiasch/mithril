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

struct Tree
{
    int leftBirds;
    vector<int> birds;
    int rightBirds;
    
    int weights;

    inline int totalBirds() {
        return leftBirds + birds.size() + rightBirds;
    }
};

int opt[1 << 10];
int prev[1 << 20];

int solve(int totalBirds, const vector<Tree> &trees, vector<int> &ans)
{
    int n = trees.size();
    memset(opt, -1, sizeof(opt[0]) * n);
    memset(prev, -1, sizeof(prev[0]) * n);
    int ret = -1;
    for (int i = 0; i < n; i++) {
        if (trees[i].leftBirds == 0) {
            if (opt[i] < trees[i].weights) {
                opt[i] = trees[i].weights;
                prev[i] = -2;
            }
        }
        if (opt[i] < 0) {
            continue;
        }
        if (trees[i].rightBirds == 0) {
            if (ret < 0 || opt[i] > opt[ret]) {
                ret = i;
            }
        }
        for (int j = i + 1; j < n; j++) {
            if (trees[i].rightBirds + trees[j].leftBirds == totalBirds) {
                if (opt[j] < opt[i] + trees[j].weights) {
                    opt[j] = opt[i] + trees[j].weights;
                    prev[j] = i;
                }
            }
        }
    }
    ans.clear();
    if (ret < 0) {
        return 0;
    }
    int ptr = ret;
    while (ptr >= 0) {
        for (int i = 0; i < trees[ptr].birds.size(); i++) {
            ans.push_back(trees[ptr].birds[i]);
        }
        ptr = prev[ptr];
    }
    return opt[ret];
}

int main()
{
    int n;
    vector<Tree> trees;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int li, ri, wi;
        scanf("%d%d%d", &li, &ri, &wi);
        if (trees.empty() || trees.back().leftBirds != li || trees.back().rightBirds != ri) {
            Tree tree;
            tree.leftBirds = li;
            tree.birds.clear();
            tree.rightBirds = ri;
            tree.weights = 0;
            trees.push_back(tree);
        }
        trees.back().birds.push_back(i);
        trees.back().weights += wi;
    }
    vector<int> birdCounts;
    for (int i = 0; i < trees.size(); i++) {
        birdCounts.push_back(trees[i].totalBirds());
    }
    sort(birdCounts.begin(), birdCounts.end());
    birdCounts.erase(unique(birdCounts.begin(), birdCounts.end()), birdCounts.end());
    int ans = 0;
    vector<int> ansBirds;
    for (int i = 0; i < birdCounts.size(); i++) {
        vector<Tree> t;
        for (int j = 0; j < trees.size(); j++) {
            if (trees[j].totalBirds() == birdCounts[i]) {
                t.push_back(trees[j]);
            }
        }
        vector<int> birds;
        int res = solve(birdCounts[i], t, birds);
        if (res > ans) {
            ans = res;
            ansBirds = birds;
        }
    }
    printf("%d\n", ans);
    set<int> S(ansBirds.begin(), ansBirds.end());
    vector<int> birds;
    for (int i = 0; i < n; i++) {
        if (!S.count(i)) {
            birds.push_back(i);
        }
    }
    printf("%d", birds.size());
    for (int i = 0; i < birds.size(); i++) {
        printf(" %d", birds[i] + 1);
    }
    puts("");
}
