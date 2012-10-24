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

struct Space
{
    long long A, B, C;

    //x >= A, y >= B, 2 * x + 3 * y == C
    
    Space(long long size = 0) {
        assert(size != 1);
        C = size;
        A = 0, B = 0;
        while (A * 2 <= size && (size - A * 2) % 3 != 0) {
            A ++;
        }
        while (B * 3 <= size && (size - B * 3) % 2 != 0) {
            B ++;
        }
        assert(A * 2 + B * 3 <= size);
    }

    Space(long long A, long long B, long long C) : A(A), B(B), C(C) {}

    Space operator+(const Space &o) const {
        return Space(A + o.A, B + o.B, C + o.C);
    }

    Space operator*(long long scale) const {
        return Space(A * scale, B * scale, C * scale);
    }

    bool contains(const Space &s) const {
        long long nA = max(A, s.A), nB = max(B, s.B);
        return C >= s.C && nA * 2 + nB * 3 <= C;
    }

};

ostream &operator<<(ostream &out, const Space &s)
{
    return out << "(" << s.A << " " << s.B << " " << s.C << ")";
}

int n, r;

int main()
{
    scanf("%d%d", &n, &r);
    Space sum = 0, R = r, R1 = r - 1;
    for (int i = 0; i < n; i++) {
        int ai;
        scanf("%d", &ai);
        sum = sum + ai;
    }
    long long lo = 0, hi = 1LL << 40;
    while (lo < hi) {
        long long mid = lo + hi >> 1;
        bool found = false;
        for (int i = 0; i <= mid; i++) {
            if ((R * (mid - i) + R1 * i).contains(sum)) {
                found = true;
                break;
            }
        }
        if (found) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << endl;
}
