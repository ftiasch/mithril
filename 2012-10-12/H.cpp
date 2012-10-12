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

const double INF = 1e100;

int A, B, C, D;

double len[5][5][5][5];

int main()
{
    cin >> A >> B >> C >> D;
    memset(len, 0, sizeof(len));
    for (int it = 0; it < 1000; ++it) {
        for (int a = 0; a <= A; a++) {
            for (int b = 0; b <= B; b++) {
                for (int c = 0; c <= C; c++) {
                    for (int d = 0; d <= D; d++) {
                        if (a == A && b == B && c == C && d == D) {
                            continue;
                        }
                        int cnt[4] = {0, 0, 0, 0};
                        double sum[4] = {0.0, 0.0, 0.0, 0.0};
                        for (int da = -1; da <= 1; da++) {
                            if (a == 0 && da < 0 || a == A && da > 0) {
                                continue;
                            }
                            for (int db = -1; db <= 1; db++) {
                                if (b == 0 && db < 0 || b == B && db > 0) {
                                    continue;
                                }
                                for (int dc = -1; dc <= 1; dc++) {
                                    if (c == 0 && dc < 0 || c == C && dc > 0) {
                                        continue;
                                    }
                                    for (int dd = -1; dd <= 1; dd++) {
                                        if (d == 0 && dd < 0 || d == D && dd > 0) {
                                            continue;
                                        }
                                        double val = len[a + da][b + db][c + dc][d + dd];
                                        if (da == 1) {
                                            cnt[0] ++;
                                            sum[0] += val;
                                        }
                                        if (db == 1) {
                                            cnt[1] ++;
                                            sum[1] += val;
                                        }
                                        if (dc == 1) {
                                            cnt[2] ++;
                                            sum[2] += val;
                                        }
                                        if (dd == 1) {
                                            cnt[3] ++;
                                            sum[3] += val;
                                        }
                                    }
                                }
                            }
                        }
                        double best = INF;
                        for (int i = 0; i < 4; i++) {
                            best = min(best, sum[i] / cnt[i]);
                        }
                        len[a][b][c][d] = best + 1;
                    }
                }
            }
        }
    }
    printf("%.10f\n", len[0][0][0][0]);
}
