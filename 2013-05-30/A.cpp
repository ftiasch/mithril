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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

set<string> out;

inline void print(string x)
{
    if (x != "?") {
        printf(" %s", x.c_str());
        return;
    }
    if (out.size() == 0) {
        printf(" IMPOSSIBLE");
        return;
    }
    printf(" ");
    if (out.size() > 1) {
        printf("{");
    }
    bool first = true;
    FOR (iter, out) {
        if (first) {
            first = false;
        } else {
            printf(", ");
        }
        printf("%s", iter->c_str());
    }
    if (out.size() > 1) {
        printf("}");
    }
}

inline bool check(string a, string b)
{
    if (a == "?" || b == "?") {
        return true;
    }
    return a == b;
}

inline string gen(int a, int b, int c)
{
    if (a > b) {
        swap(a, b);
    }
    #define A 0
    #define B 1
    #define O 2
    
    string ret = "";
    if (a == A && b != B) {
        ret += "A";
    } else if (a == A && b == B) {
        ret += "AB";
    } else if (a == B){
        ret += "B";
    } else {
        ret += "O";
    }
    
    if (c) {
        ret += "+";
    } else {
        ret += "-";
    }
    
    #undef A
    #undef B
    #undef O
    
    return ret;
}

int main()
{
    string father, mother, child;
    for (int test = 1;cin >> father >> mother >> child; ++ test) {
        if (father == "E") {
            break;
        }
        out.clear();
        for (int f1 = 0; f1 < 3; ++ f1) {
            for (int f2 = 0; f2 < 3; ++ f2) {
                for (int f3 = 0; f3 < 2; ++ f3) {
                    if (check(gen(f1, f2, f3), father)) {
                        for (int m1 = 0; m1 < 3; ++ m1) {
                            for (int m2 = 0; m2 < 3; ++ m2) {
                                for (int m3 = 0; m3 < 3; ++ m3) {
                                    if (check(gen(m1, m2, m3), mother)) {
                                        for (int c3 = 0; c3 <= (f3 | m3); ++ c3) {
                                            if (check(gen(f1, m1, c3), child)) {
                                                if (father == "?") {
                                                    out.insert(gen(f1, f2, f3));
                                                } else if (mother == "?") {
                                                    out.insert(gen(m1, m2, m3));
                                                } else {
                                                    out.insert(gen(f1, m1, c3));
                                                }
                                            }
                                            if (check(gen(f1, m2, c3), child)) {
                                                if (father == "?") {
                                                    out.insert(gen(f1, f2, f3));
                                                } else if (mother == "?") {
                                                    out.insert(gen(m1, m2, m3));
                                                } else {
                                                    out.insert(gen(f1, m2, c3));
                                                }
                                            }
                                            if (check(gen(f2, m1, c3), child)) {
                                                if (father == "?") {
                                                    out.insert(gen(f1, f2, f3));
                                                } else if (mother == "?") {
                                                    out.insert(gen(m1, m2, m3));
                                                } else {
                                                    out.insert(gen(f2, m1, c3));
                                                }
                                            }
                                            if (check(gen(f2, m2, c3), child)) {
                                                if (father == "?") {
                                                    out.insert(gen(f1, f2, f3));
                                                } else if (mother == "?") {
                                                    out.insert(gen(m1, m2, m3));
                                                } else {
                                                    out.insert(gen(f2, m2, c3));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("Case %d:", test);
        print(father);
        print(mother);
        print(child);
        puts("");
    }
}

