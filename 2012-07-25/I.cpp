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

const int maxn = 1 << 20;

char str[maxn];

typedef char *pchar;

pchar ptr;

bool readGoo(pchar &ptr)
{
    if (*ptr != 'D' && *ptr != 'E') {
        return false;
    }
    ptr ++;
    if (*ptr != 'F') {
        return false;
    }
    ptr ++;
    while (*ptr == 'F') {
        ptr ++;
    }
    if (*ptr == 'G') {
        ptr ++;
        return true;
    }
    return readGoo(ptr);
}

bool readPoo(pchar &ptr)
{
    if (*ptr != 'A') {
        return false;
    }
    ptr ++;
    if (*ptr == 'H') {
        ptr ++;
        return true;
    }
    if (*ptr == 'B') {
        ptr ++;
        if (!readPoo(ptr)) {
            return false;
        }
        if (*ptr != 'C') {
            return false;
        }
        ptr ++;
        return true;
    }
    if (!readGoo(ptr)) {
        return false;
    }
    if (*ptr != 'C') {
        return false;
    }
    ptr ++;
    return true;
}

void testGoo(const char *s, bool result)
{
    strcpy(str, s);
    assert((readGoo(ptr = str) && ptr) == result);
}

void testPoo(const char *s, bool result)
{
    strcpy(str, s);
    assert((readPoo(ptr = str) && ptr) == result);
}

void quickcheck()
{
    testGoo("DFG", true);
    testGoo("EFG", true);
    testGoo("DFFFFFG", true);
    testGoo("DFEFFFFG", true);
    testPoo("AH", true);
    testPoo("ABAHC", true);
    testPoo("ABABAHCC", true);
    testPoo("ADFGC", true);
    testPoo("ABAEFGCC", true);
    testPoo("ADFDFGC", true);
}

int main()
{
    quickcheck();
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        scanf("%s", str);
        ptr = str;
        if (readPoo(ptr) && readGoo(ptr) && !*ptr) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
}

