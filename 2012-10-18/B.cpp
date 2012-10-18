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

const int maxn = 1024;

char input[maxn][maxn];

void flip(char &ch)
{
    ch ^= '0';
    ch ^= '1';
}

int main()
{
    int n, cas = 0;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = n - 1; i >= 0; i--) {
            scanf("%s", input[i]);
        }
        for (int i = 0; i + 1 < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (input[i][j] == '1') {
                    flip(input[i][j]);
                    flip(input[i+1][j]);
                    flip(input[i+1][j+1]);
                }
            }
        }
        string s = input[n - 1];
        for (int i = 0; i + 2 < s.size(); i++) {
            if (s[i] == '1') {
                flip(s[i]);
                flip(s[i + 1]);
                flip(s[i + 2]);
            }
        }
        printf("Triangle %d %s be filled.\n", ++cas, s.find('1') == -1 ? "can" : "cannot");
    }
}

