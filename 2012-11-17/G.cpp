#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

const int N = 100;
const int M = 100000;

int n, m;
string pattern, text;
vector <string> patterns;

int next[N >> 1][M];

#define SIZE(s) (int)s.size()

char raw[N + M + M + 1];
int fail[N + M + M + 1];
bool match[N + M + M + 1];

int main() {
    freopen("pattern.in", "r", stdin);
    freopen("pattern.out", "w", stdout);
    cin >> pattern >> text;
    n = SIZE(pattern);
    m = SIZE(text);
    for (int i = 0; i < n; ++ i) {
        if (pattern[i] == '*') {
            pattern[i] = ' ';
        }
    }
    text += text;
    stringstream sin(pattern);
    {
        string buffer;
        while (sin >> buffer) {
            patterns.push_back(buffer);
        }
    }
    memset(next, -1, sizeof(next));
    for (int k = 0; k < SIZE(patterns); ++ k) {
        string &pattern = patterns[k];
        int size = 0;
        for (int i = 0; i < SIZE(pattern); ++ i) {
            raw[size ++] = pattern[i];
        }
        memset(match, 0, sizeof(match));
        match[size - 1] = true;
        raw[size ++] = '*';
        int start = size;
        for (int i = 0; i < m << 1; ++ i) {
            raw[size ++] = text[i];
        }
        memset(fail, -1, sizeof(fail));
        for (int i = 1; i < size; ++ i) {
            int p = i - 1;
            while (p != -1 && fail[i] == -1) {
                p = fail[p];
                if (raw[p + 1] == raw[i]) {
                    fail[i] = p + 1;
                }
            }
            if (fail[i] != -1) {
                match[i] |= match[fail[i]];
            }
        }
        int next_match = -1;
        for (int i = (m << 1) - 1; i >= 0; -- i) {
            int j = start + i + SIZE(pattern) - 1;
            if (j < size && match[j]) {
                next_match = i;
            }
            next[k][i % m] = next_match == -1 ? -1 : next_match % m;
        }
    }
    int answer = 0;
    if (SIZE(patterns) == 0) { // *
        answer = m;
    } else {
        bool valid = true;
        for (int i = 0; i < SIZE(patterns); ++ i) {
            for (int j = 0; j < m; ++ j) {
                valid &= next[i][j] != -1;
            }
        }
        if (valid) {
            for (int start = 0; start < m; ++ start) {
                int id = 0;
                int begin = start;
                bool valid = true;
                if (pattern[0] != ' ') {
                    if (next[0][begin] == begin) {
                        id ++;
                        begin += SIZE(patterns[0]);
                    } else {
                        valid = false;
                    }
                }
                while (valid && id < SIZE(patterns)) {
                    int delta = next[id][begin % m] - begin % m;
                    if (delta < 0) {
                        delta += m;
                    }
                    begin += delta + SIZE(patterns[id]);
                    id ++;
                }
                valid &= begin <= start + m;
                if (valid) {
                    if (pattern[SIZE(pattern) - 1] != ' ') {
                        if (SIZE(patterns) == 1 && pattern[0] != ' ') {
                            valid &= begin == start + m;
                        } else {
                            int ret = (start + m - SIZE(patterns.back())) % m;
                            valid &= next[patterns.size() - 1][ret] == ret;
                        }
                    }
                }
                if (valid) {
                    answer ++;
                } else {
                    //printf("* %d\n", start);
                }
            }
        }
    }
    printf("%d\n", answer);
    return 0;

}
