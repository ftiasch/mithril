#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 300;

int n, x[N], y[N];

long long square(long long x) {
    return x * x;
}

long long getDistance(int i, int j) {
    return square(x[i] - x[j]) + square(y[i] - y[j]);
}

long long d[N][N];

unsigned long long MAGIC = 0xabcdef;

unsigned long long makeTriple(long long a, long long b, long long c) {
    if (b > c) {
        swap(b, c);
    }
    if (a > b) {
        swap(a, b);
    }
    if (b > c) {
        swap(b, c);
    }
    return (a * MAGIC + b) * MAGIC + c;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", x + i, y + i);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            d[i][j] = getDistance(i, j);
        }
    }
    vector <unsigned long long> triangles;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            for (int k = 0; k < j; ++ k) {
                triangles.push_back(makeTriple(d[i][j],
                            d[j][k], 
                            d[k][i]));
            }
        }
    }
    sort(triangles.begin(), triangles.end());
    long long result =0 ;
    for (int i = 0; i < (int)triangles.size(); ++ i) {
        int j = i;
        while (j < (int)triangles.size() && triangles[i] == triangles[j]) {
            j ++;
        }
        long long size = j - i;
        result += size * (size - 1) / 2;
        i = j - 1;
    }
    cout << result << endl;
    return 0;
}
