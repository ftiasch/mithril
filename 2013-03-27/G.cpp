#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const char CODE[4] = {'N', 'O', 'P', 'Q'};

std::map <std::vector <int>, int> states;

int get_code(std::vector <int> piles) {
    std::sort(piles.begin(), piles.end(), std::greater <int>());
    while (!piles.empty() && piles.back() == 0) {
        piles.pop_back();
    }
    if (piles.empty()) {
        return 2;
    }
    if (states.find(piles) == states.end()) {
        int &ret = states[piles];
        ret = 3;
        bool all_0 = true;
        bool all_1 = true;
        for (int i = 0; i < (int)piles.size(); ++ i) {
            for (int j = 1; j <= piles[i]; ++ j) {
                piles[i] -= j;
                int tmp = get_code(piles);
                if (tmp == 2) {
                    ret = 0;
                }
                all_0 &= tmp == 0;
                all_1 &= tmp == 1;
                piles[i] += j;
            }
        }
        if (ret == 3) {
            if (all_0) {
                ret = 1;
            }
            if (all_1) {
                ret = 2;
            }
        }
    }
    return states[piles];
}

std::vector <std::vector <int> > choices;

void generate(int n, int last, std::vector <int> piles) {
    if (n) {
        for (int i = 1; i <= n && i <= last; ++ i) {
            piles.push_back(i);
            generate(n - i, i, piles);
            piles.pop_back();
        }
    } else {
        choices.push_back(piles);
    }
}

struct Data {
    std::vector <int> a, b;

    Data(std::vector <int> _a, std::vector <int> _b): a(_a), b(_b) {
    }
};

Data* memory[4][4][4];

int get_map(char x) {
    for (int i = 0; i < 4; ++ i) {
        if (CODE[i] == x) {
            return i;
        }
    }
    assert(false);
}

void print(std::vector <int> v) {
    if (v.empty()) {
        puts("0");
    } else {
        foreach (iter, v) {
            printf("%d ", *iter);
        }
        puts("");
    }
}

int main() {
    for (int i = 1; i <= 20; ++ i) {
        generate(i, i, std::vector <int>());
    }
int total = 0;
    for (int i = 0; i < 30; ++ i) {
        for (int j = i + 1; j < 100; ++ j) {
            std::vector <int> piles;
            int sum = 0;
            foreach (iter, choices[i]) {
                piles.push_back(*iter);
                sum += *iter;
            }
            foreach (iter, choices[j]) {
                piles.push_back(*iter);
                sum += *iter;
            }
            int p = get_code(choices[i]);
            int q = get_code(choices[j]);
            if (sum <= 20) {
                int r = get_code(piles);
                if (memory[p][q][r] == NULL) {
total ++;
                    memory[p][q][r] = new Data(choices[i], choices[j]);
                }
            }
        }
    }
    char buffer[4];
    scanf("%s", buffer);
    int p = get_map(buffer[0]);
    int q = get_map(buffer[1]);
    int r = get_map(buffer[2]);
    if (memory[p][q][r] == NULL) {
        puts("NO");
    } else {
        puts("YES");
        print(memory[p][q][r]->a);
        print(memory[p][q][r]->b);
    }
    return 0;
}
