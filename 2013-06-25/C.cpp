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

const int maxn = 100000;

char symbols[][10] = {
    "H", "He",
    "Li", "Be", "B", "C", "N", "O", "F", "Ne",
    "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
    "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
    "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe",
    "Cs", "Ba", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn",
    "Fr", "Ra", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Fl", "Lv",
    "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu",
    "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr",
    ""
};

int n = 0;
int len[222];

char str[maxn];
int m;
bool flag[maxn];

int main()
{
    while (symbols[n][0]) {
        len[n] = strlen(symbols[n]);
        n ++;
    }
    int tests = 0;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%s", str);
        m = strlen(str);
        flag[m] = true;
        for (int i = m - 1; i >= 0; i--) {
            flag[i] = false;
            for (int j = 0; j < n; j++) {
                if (i + len[j] <= m && flag[i + len[j]]) {
                    bool valid = true;
                    for (int k = 0; k < len[j]; k++) {
                        if (str[i + k] != tolower(symbols[j][k])) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        flag[i] = true;
                        break;
                    }
                }
            }
        }
        puts(flag[0] ? "YES" : "NO");
    }
}
