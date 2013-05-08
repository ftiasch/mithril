#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()

int n;
std::vector <int> circles, squares;

long long same_count(std::vector <int> &sizes) {
    long long ret = 0;
    for (int i = 0; i < (int)sizes.size(); ++ i) {
        int j = i;
        while (j < (int)sizes.size() && sizes[i] == sizes[j]) {
            j ++;
        }
        ret += (long long)(j - i) * i;
        i = j - 1;
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        char buffer[22];
        scanf("%s", buffer);
        int size;
        sscanf(buffer + 1, "%d", &size);
        if (*buffer == 'C') {
            circles.push_back(size);
        } else {
            squares.push_back(size);
        }
    }
    std::sort(ALL(circles));
    std::sort(ALL(squares));
    long long answer = 0;
    answer += same_count(circles);
    answer += same_count(squares);
    for (int i = 0, j = 0; i < (int)circles.size(); ++ i) {
        while (j < (int)squares.size() && squares[j] * sqrt(2.0) < circles[i] * 2) {
            j ++;
        }
        answer += j;
    }
    for (int i = 0, j = 0; i < (int)squares.size(); ++ i) {
        while (j < (int)circles.size() && circles[j] * 2 < squares[i]) {
            j ++;
        }
        answer += j;
    }
    std::cout << answer << std::endl;
    return 0;
}
