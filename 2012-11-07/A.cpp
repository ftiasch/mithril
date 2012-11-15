#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000;

char matrix[N][N + 1];


int solve(vector <int> &count) {
    int n = count.size();
    int average = 0;
    for (int i = 0; i < n; ++ i) {
        average += count[i];
    }
    if (average % n != 0) {
        return -1;
    }
    average /= n;
    int result = INT_MAX;
    for (int i = 0; i < n; ++ i) {
        int need = 0;
        int sum = 0;
        for (int j = 0; j < n; ++ j) {
            sum += count[j];
            sum -= average;
            need += abs(sum);
        }
        result = min(result, need);
        rotate(count.begin(), count.begin() + 1, count.end());
    }
    return result;
}

int main() {
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf("%s", matrix[i]);
        }
        vector <int> rowCount(n, 0), columnCount(m, 0);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                rowCount[i] += matrix[i][j] == '1';
                columnCount[j] += matrix[i][j] == '1';
            }
        }
        int rowAnswer = solve(rowCount);
        int columnAnswer = solve(columnCount);
        printf("Case %d: ", t);
        if (rowAnswer == -1) {
            if (columnAnswer == -1) {
                printf("impossible");
            } else {
                printf("column %d", columnAnswer);
            }
        } else {
            if (columnAnswer == -1) {
                printf("row %d", rowAnswer);
            } else {
                printf("both %d", rowAnswer + columnAnswer);
            }
        }
        cout << endl;
    }
    return 0;
}

