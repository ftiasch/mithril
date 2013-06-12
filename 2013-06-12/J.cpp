#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <algorithm>

#define SIZE(v) (int)(v).size()
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

using std::string;

std::string RULES[][2] = {{"B-D-o", "Black"},
                          {"B-ddo", "Blue"},
                          {"bbD-o", "Chocolate"},
                          {"bbddo", "Lilac"},
                          {"--D-O", "Red"},
                          {"--ddO", "Cream"},

                          {"B-D-oo", "Black"},
                          {"B-ddoo", "Blue"},
                          {"bbD-oo", "Chocolate"},
                          {"bbddoo", "Lilac"},
                          {"--D-OO", "Red"},
                          {"--ddOO", "Cream"},
                          {"B-D-Oo", "Black-Red Tortie"},
                          {"B-ddOo", "Blue-Cream Tortie"},
                          {"bbD-Oo", "Chocolate-Red Tortie"},
                          {"bbddOo", "Lilac-Cream Tortie"},
                        };

struct Cat {
    int b, d, o, sex;

    Cat(int b, int d, int o, int sex) : b(b), d(d), o(o), sex(sex) {}

    string name() const {
        std::string _name = to_string();
        for (int i = 0; i < 16; ++ i) {
            if (SIZE(RULES[i][0]) == SIZE(_name)) {
                int m = SIZE(_name);
                bool valid = true;
                for (int j = 0; j < m; ++ j) {
                    if (RULES[i][0][j] != '-') {
                        valid &= RULES[i][0][j] == _name[j];
                    }
                }
                if (valid) {
                    return RULES[i][1];
                }
            }
        }
        return "";
    }

    Cat &normalize() {
        if (b == 2) {
            b ^= 3;
        }
        if (d == 2) {
            d ^= 3;
        }
        if (o == 2) {
            o ^= 3;
        }
        return *this;
    }

    string to_string() const {
        string ret = "";
        for (int i = 0; i < 2; ++ i) {
            if (b >> i & 1) {
                ret += 'B';
            } else {
                ret += 'b';
            }
        }
        for (int i = 0; i < 2; ++ i) {
            if (d >> i & 1) {
                ret += 'D';
            } else {
                ret += 'd';
            }
        }
        for (int i = 0; i < 1 + sex; ++ i) {
            if (o >> i & 1) {
                ret += 'O';
            } else {
                ret += 'o';
            }
        }
        return ret;
    }
};

std::vector <Cat> fathers, mothers;
std::map <string, double> answer;

int main() {
    std::string mother_name, father_name;
    getline(std::cin, mother_name);
    getline(std::cin, father_name);
    for (int b = 0; b < 4; ++ b) {
        for (int d = 0; d < 4; ++ d) {
            for (int o = 0; o < 4; ++ o) {
                for (int s = 0; s < 2; ++ s) {
                    if (!s && o >= 2) {
                        continue;
                    }
                    Cat cat(b, d, o, s);
                    if (s) {
                        if (cat.name() == mother_name) {
                            mothers.push_back(cat);
//printf("M %s\n", cat.to_string().c_str());
                        }
                    } else {
                        if (cat.name() == father_name) {
                            fathers.push_back(cat);
//printf("F %s\n", cat.to_string().c_str());
                        }
                    }
                }
            }
        }
    }
    foreach (f, fathers) {
        foreach (m, mothers) {
            for (int fb = 0; fb < 2; ++ fb) {
                int FB = f->b >> fb & 1;
                for (int mb = 0; mb < 2; ++ mb) {
                    int MB = m->b >> mb & 1;
                    for (int fd = 0; fd < 2; ++ fd) {
                        int FD = f->d >> fd & 1;
                        for (int md = 0; md < 2; ++ md) {
                            int MD = m->d >> md & 1;
                            for (int fo = 0; fo < 2; ++ fo) {
                                int FO = f->o >> fo & 1;
                                for (int mo = 0; mo < 2; ++ mo) {
                                    int MO = m->o >> mo & 1;
                                    Cat cat(FB << 1 | MB,
                                            FD << 1 | MD,
                                            FO << 1 | MO,
                                            fo ^ 1);
                                    answer[cat.normalize().name()] += (1.0 / fathers.size()) * (1.0 / mothers.size()) / 64;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::vector <std::pair <double, string> > final;
    foreach (iter, answer) {
        final.push_back(std::make_pair(-iter->second, iter->first));
    }
    std::sort(final.begin(), final.end());
    //std::reverse(final.begin(), final.end());
    foreach (iter, final) {
        printf("%s %.12f\n", iter->second.c_str(), -iter->first);
    }
    return 0;
}
