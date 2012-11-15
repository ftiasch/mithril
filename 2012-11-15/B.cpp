#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int n;

vector <int> read_ints() {
    vector <int> v(n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &v[i]);
    }
    return v;
}

const int N = 100000 + 1;

int counter[N];

long long count_inversion(vector <int> v) {
    memset(counter, 0, sizeof(counter));
    long long answer = 0;
    for (int i = 0; i < n; ++ i) {
        for (int k = v[i]; k <= n; k += k & -k) {
            answer += counter[k];
        }
        for (int k = v[i]; k >= 1; k -= k & -k) {
            counter[k] ++;
        }
    }
    return answer;
}

int main() {
    scanf("%d", &n);
    long long a = count_inversion(read_ints());
    long long b = count_inversion(read_ints());
    puts((a - b) % 2 == 0 ? "Possible" : "Impossible");
    return 0;
}
