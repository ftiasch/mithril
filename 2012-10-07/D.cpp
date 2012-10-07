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

const int maxn = 11111;
const int samples = 1024;

char str[maxn];
int n;

long long wys[4][maxn];

long long solve(const string &seq)
{
    for (int i = 0; i < 4; i++) {
        memset(wys[i], 0, sizeof(long long) * n);
    }
    for (int i = 0; i < n; i++) {
        if (seq[0] == str[i]) {
            wys[0][i] = 1;
        }
    }
    for (int i = 1; i < 4; i++) {
        char ch = seq[i];
        long long sum = 0;
        for (int j = 0; j < n; j++) {
            if (ch == str[j]) {
                wys[i][j] += sum;
            }
            sum += wys[i-1][j];
        }
    }
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        ret += wys[3][i];
    }
    return ret;
}

int main()
{
    freopen("percentage.in", "r", stdin);
    freopen("percentage.out", "w", stdout);
    srand(9927);
    scanf("%s", str);
    n = strlen(str);
    vector<string> sample;
    for (int i = 0; i < samples; i++) {
        int a[4];
        for (int j = 0; j < 4; j++) {
            a[j] = (unsigned)rand() % (n - j);
            for (int k = 0; k < j; k++) {
                if (a[j] >= a[k]) {
                    a[j] ++;
                }
            }
            sort(a, a + j + 1);
        }
        string s = "";
        for (int j = 0; j < 4; j++) {
            s += str[a[j]];
        }
        sample.push_back(s);
    }
    sort(sample.begin(), sample.end());
    sample.erase(unique(sample.begin(), sample.end()), sample.end());
    long long all = (long long)n * (n - 1) * (n - 2) * (n - 3) / 24;
    vector<long long> answers;
    for (int i = 0; i < sample.size(); i++) {
        answers.push_back(solve(sample[i]));
    }
    vector<pair<int,string> > outputs;
    long long sum = 0;
    for (int i = 0; i < sample.size(); i++) {
        int percentage = answers[i] * 100 / all;
        if (percentage > 0) {
            outputs.push_back(make_pair(-percentage, sample[i]));
            sum += answers[i];
        }
    }
    sort(outputs.begin(), outputs.end());
    for (int i = 0; i < outputs.size(); i++) {
        printf("%s %d%%\n", outputs[i].second.c_str(), -outputs[i].first);
    }
    if (sum != all) {
        printf("Others less than 1%%\n");
    }
}
