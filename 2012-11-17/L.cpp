#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int n, max_k;

typedef long double LD;

bool found;
vector <int> ns;

bool is_prime(int p) {
    if (p < 2) {
        return false;
    }
    for (int i = 2; i * i <= p; ++ i) {
        if (p % i == 0) {
            return false;
        }
    }
    return true;
}

vector <int> global;

void dfs(int i, int low, int left, double sum) {
    if (found || sum < -1e-9) {
        return;
    }
    if (i < max_k) {
        for (int k = low; (max_k - i) * k <= left && (max_k - i) + 1e-8>= k * sum; ++ k) {
            ns[i] = k;
            dfs(i + 1, k, left - k, sum - 1.0 / k);
        }
    } else if (left == 0 && fabs(sum) < 1e-9) {
        global.clear();
        for (int i = 0; i < max_k; ++ i) {
            global.push_back(ns[i]);
        }
        found = true;
    }
}

vector <int> search(int n) {
    max_k = 1;
    while (max_k * max_k <= n) {
        ns.resize(max_k);
        found = false;
        dfs(0, 1, n, 1.0);
        if (found) {
            return global;
        }
        max_k ++;
    }
    return vector <int>();
}

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end() ;++ i)
vector <int> multiply(const vector <int> &v, int k) {
    vector <int> vs;
    foreach (iter, v) {
        vs.push_back(*iter * k);
    }
    return vs;
}

void gcd(int a, int b, int c, int &x, int &y) {
    if (b == 0) {
        x = c / a;
        y = 0;
        return ;
    }
    gcd(b, a % b, c, y, x);
    y -= a / b * x;
}

vector <int> solve(int n) {
    if (n <= 200) {
        return search(n);
    }
    if (n % 2 == 0) {
        vector <int> ret = multiply(solve((n - 2) / 2), 2);
        ret.push_back(2);
        return ret;
    }
    if (n % 3 == 0) {
        vector <int> ret = multiply(solve((n - 6) / 3), 3);
        ret.push_back(3);
        ret.push_back(3);
        return ret;
    }
    int x, y;
    gcd(2, 3, n - 6, x, y);
    while (x < 50) {
        x += 3;
        y -= 2;
    }
    while (y < 50) {
        y += 2;
        x -= 3;
    }
    vector <int> ret = multiply(solve(x), 2);
    vector <int> ret_2 = multiply(solve(y), 3);
    int size = ret_2.size();
    for (int i = 0; i < size; ++ i) {
        ret.push_back(ret_2[i]);
    }
    ret.push_back(6);
    return ret;
} 

int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    scanf("%d", &n);
    vector <int> ret = solve(n);
    if (ret.empty()) {
        puts("Epic fail");
    } else {
        printf("%d\n", (int)ret.size());
        for (int i = 0; i < ret.size(); ++ i) {
            printf("%d ", ret[i]);
        }
        puts("");
    }
    return 0;
}
