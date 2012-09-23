#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200;
const int L = 51;

int n;
string words[N];

struct Triple {
    int sid, begin, length;

    Triple(int sid = 0, int begin = 0, int length = 0): sid(sid), begin(begin), length(length) {}

    string value() const {
        return words[sid].substr(begin, length);
    }
};

bool operator <(const Triple &a, const Triple &b) {
    if (a.length == b.length) {
        return a.value() < b.value();
    }
    return a.length > b.length;
}

bool operator ==(const Triple &a, const Triple &b) {
    return a.value() == b.value();
}

vector <Triple> segments;
int id[N][L][L];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> words[i];
        for (size_t j = 0; j < words[i].size(); ++ j) {
            for (size_t k = 1; j + k <= words[i].size(); ++ k) {
                segments.push_back(Triple(i, j, k));
            }
        }
    }
    sort(segments.begin(), segments.end());
    vector <bool> win(segments.size(), false);
    vector <char> result;
    for (size_t begin = 0; begin < segments.size(); ++ begin) {
        size_t end = begin;
        while (end < segments.size() && segments[begin] == segments[end]) {
            end ++;
        }
        for (int i = begin; i < end; ++ i) {
            id[segments[i].sid][segments[i].begin][segments[i].length] = begin;
            if (segments[i].begin > 0 && !win[id[segments[i].sid][segments[i].begin - 1][segments[i].length + 1]]) {
                win[begin] = true;
            }
            if (segments[i].begin + segments[i].length < words[segments[i].sid].length() && !win[id[segments[i].sid][segments[i].begin][segments[i].length + 1]]) {
                win[begin] = true;
            }
            if (segments[i].length==words[segments[i].sid].length()){
                win[begin] = true;
            }
        }
        if (segments[begin].length == 1 && !win[begin]) {
            result.push_back(words[segments[begin].sid][segments[begin].begin]);
        }
        begin = end - 1;
    }
    /*for (size_t i = 0; i < segments.size(); ++ i) {
      printf("%d, %d, %d, %d\n", segments[i].sid, segments[i].begin, segments[i].length, (int)win[i]);
      }*/
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    if (result.empty()) {
        puts("Second");
    } else {
        puts("First");
        for (size_t i = 0; i < result.size(); ++ i) {
            printf("%c", result[i]);
        }
        puts("");
    }
    return 0;
}
