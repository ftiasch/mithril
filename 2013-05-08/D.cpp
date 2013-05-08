#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100;

int memory[N][N][N];

int go(vector <long long> piles) {
    std::sort(piles.begin(), piles.end(), std::greater <int>());
    piles.erase(std::unique(piles.begin(), piles.end()), piles.end());
    while ((int)piles.size() < 3) {
        piles.push_back(0);
    }
    int &ret = memory[piles[0]][piles[1]][piles[2]];
    if (ret == -1) {
        ret = 0;
        for (int i = 0; i < 3; ++ i) {
            if (piles[i]) {
                vector <long long> newPiles(piles);
                newPiles[i] --;
                if (!go(newPiles)) {
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

int solve(vector <long long> piles) {
    std::sort(piles.begin(), piles.end());
    if (piles.size() == 1) {
        return piles[0] % 2;
    } else if (piles.size() == 2) {
        if (piles[0] == 1 && piles[1] % 2 == 0) {
            return 1;
        }
        if (piles[0] + 1 == piles[1] && piles[0] % 2 == 0) {
            return 1;
        }
        return piles[1] % 2 != piles[0] % 2;
    } else {
        if (piles[0] == 1 && piles[1] % 2 == piles[2] % 2) {
            return 1;
        }
        if (piles[0] + 1 == piles[1] && piles[1] + 1 == piles[2]) {
            return 1;
        }
        if (piles[0] + 1 == piles[1] && piles[0] % 2 == piles[2] % 2) {
            return 1;
        }
        if (piles[1] + 1 == piles[2] && piles[0] % 2 == piles[1] % 2) {
            return 1;
        }
        long long a = piles[0];
        long long b = piles[2] - piles[1];
        return a % 2 != b % 2;
//printf("%d %d\n",a,b);
        if (a == 1) {
            return b % 2;
        }
        if (a & 1) {
            return b < 1;
        } else {
            return b < 2;
        }
    }
}

int main() {
    memset(memory, -1, sizeof(memory));
    int n = N;
/*    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            for (int k = 0; k < j; ++ k) {
                vector <long long> piles;
                if (i) {
                    piles.push_back(i);
                }
                if (j) {
                    piles.push_back(j);
                }
                if (k) {
                    piles.push_back(k);
                }
                if (go(piles) != solve(piles)) {
                    printf("%d, %d, %d, %d\n", k, j, i, go(piles));
                    assert(false);
                }
            }
        }
    }
    puts("AC");*/
    vector<long long> piles;
    cin >> n;
    long long x;
    for (int i=0;i<n;++i){
        cin >> x;
        piles.push_back(x);
    }
    printf("%d\n",solve(piles)?1:2);
    return 0;
}
