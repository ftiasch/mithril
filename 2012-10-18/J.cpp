#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10000;

int n, a[N], b[N], order[N];

int c[31][N + 1];

const int L = 4000;

struct BigInteger {
    int length;
    int digit[L];

    BigInteger() {
        length = 0;
        memset(digit, 0, sizeof(digit));
    }

    int &operator[](int i) {
        return digit[i];
    }

    int operator[](int i) const {
        return digit[i];
    }

    void reduce() {
        while (length > 0 && digit[length - 1] == 0) {
            length --;
        }
    }

    void print() {
        for (int i = length - 1; i >= 0; -- i) {
            printf("%d", digit[i]);
        }
    }
};

BigInteger operator +(const BigInteger &a, const BigInteger &b) {
    BigInteger c;
    c.length = max(a.length, b.length) + 1;
    int delta = 0;
    for (int i = 0; i < c.length; ++ i) {
        delta += a[i] + b[i];
        c[i] = delta % 10;
        delta /= 10;
    }
    c.reduce();
    return c;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    
    for (int i = 0; i < n; ++ i) {
        b[i] = a[i];
        order[i] = i;
    }
    int sum = 0;
    {
        int rank = 0;
        for (int k = 30; k >= 0; -- k) {
            int i = rank;
            while (i < n && !(b[i] >> k & 1)) {
                i ++;
            }
            if (i == n) {
                continue;
            }
            swap(b[i], b[rank]);
            for (int i = 0; i < n; ++ i) {
                if (i != rank && (b[i] >> k & 1)) {
                    b[i] ^= b[rank];
                }
            }
            rank ++;
        }
        for (int i = 0; i < rank; ++ i) {
            sum ^= b[i];
        }
    }
    for (int k = 30; k >= 0; -- k) {
        for (int i = 0; i < n; ++ i) {
            c[k][i] = a[i] >> k & 1;
            c[k][n] = sum >> k & 1;
        }
    }
    vector <int> ways;
    BigInteger result;
    {
        int rank = 0;
        for (int k = 0; k < n; ++ k) {
            int i = rank;
            while (i < 31 && !c[i][k]) {
                i ++;
            }
            if (i == 31) {
                continue;
            }
            for (int j = 0; j <= n; ++ j) {
                swap(c[i][j], c[rank][j]);
            }
            for (int i = 0; i < 31; ++ i) {
                if (i != rank && c[i][k]) {
                    for (int j = 0; j <= n; ++ j) {
                        c[i][j] ^= c[rank][j];
                    }
                }
            }
            rank ++;
        }
        for (int i = 0; i < rank; ++ i) {
            int j = 0;
            while (!c[i][j]) {
                j ++;
            }
            if (c[i][n]) {
                ways.push_back(j);
            }
        }
        int null = n - rank;
        result.length = 1;
        result[0] = 1;
        for (int i = 0; i < null; ++ i) {
            result = result + result;
        }
        if (sum == 0) {
            result[0] --;
        }
    }
    printf("%d ", sum);
    result.print();
    if (sum == 0) {
        printf(" %d\n%d\n", 1, 0);
    } else {
        printf(" %d\n", (int)ways.size());
        sort(ways.begin(), ways.end());
        for (int i = 0; i < (int)ways.size(); ++ i) {
            printf("%d%c", a[ways[i]], i == (int)ways.size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
