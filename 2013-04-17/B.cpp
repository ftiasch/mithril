#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

unsigned memory[1 << 30 - 5];
unsigned visit[1 << 30 - 5];

std::vector <unsigned> choices;

int get_id(int x, int y) {
    return x * 6 + y;
}

bool by_popcount(unsigned x, unsigned y) {
    return __builtin_popcount(x) > __builtin_popcount(y);
}

bool solve(unsigned mask) {
    if (visit[mask >> 5] >> (mask & 31) & 1) {
        return memory[mask >> 5] >> (mask & 31) & 1;
    }
    visit[mask >> 5] |= 1U << (mask & 31);
    foreach (iter, choices){
        unsigned new_mask = mask & ~*iter;
        if (mask == new_mask) {
            continue;
        }
        if (!solve(new_mask)) {
            memory[mask >> 5] |= 1U << (mask & 31);
            return true;
        }
    }
    return false;
}

int main() {
    for (int r_1 = 0; r_1 < 5; ++ r_1) {
        for (int r_2 = r_1; r_2 < 5; ++ r_2) {
            for (int c_1 = 0; c_1 < 6; ++ c_1) {
                for (int c_2 = c_1; c_2 < 6; ++ c_2) {
                    if (r_1 == r_2 || c_1 == c_2) {
                        unsigned mask = 0;
                        for (int x = r_1; x <= r_2; ++ x) {
                            for (int y = c_1; y <= c_2; ++ y) {
                                mask |= 1U << get_id(x, y);
                            }
                        }
                        choices.push_back(mask);
                    }
                }
            }
        }
    }
    std::sort(choices.begin(), choices.end(), by_popcount);
    int test_count;
    std::cin >> test_count;
    while (test_count --) {
        int mask = (1U << 30) - 1;
        while (true) {
            foreach (iter, choices){
                unsigned new_mask = mask & ~*iter;
                if (mask == new_mask) {
                    continue;
                }
                if (!solve(new_mask)) {
                    for (int r_1 = 0; r_1 < 5; ++ r_1) {
                        for (int r_2 = r_1; r_2 < 5; ++ r_2) {
                            for (int c_1 = 0; c_1 < 6; ++ c_1) {
                                for (int c_2 = c_1; c_2 < 6; ++ c_2) {
                                    if (r_1 == r_2 || c_1 == c_2) {
                                        unsigned mask = 0;
                                        for (int x = r_1; x <= r_2; ++ x) {
                                            for (int y = c_1; y <= c_2; ++ y) {
                                                mask |= 1U << get_id(x, y);
                                            }
                                        }
                                        if (mask == *iter) {
                                            std::cout << r_1 + 1 << " " <<  c_1 + 1 << " " << r_2 + 1 << " " << c_2 + 1 << std::endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    mask = new_mask;
                    break;
                }
            }
            std::string cmd;
            std::cin >> cmd;
            if (cmd[0] == 'G') {
                break;
            }
            int r_1, c_1, r_2, c_2;
            std::cin >> r_1 >> c_1 >> r_2 >> c_2;
            for (int i = r_1; i <= r_2; ++ i) {
                for (int j = c_1; j <= c_2; ++ j) {
                    mask &= ~(1U << get_id(i, j));
                }
            }
        }
    }
    return 0;
}
