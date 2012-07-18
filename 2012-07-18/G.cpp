// Problem G -- The Most Relevant Pattern   
// Author: Xiaoxu Guo
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 4001;

char text[N];

typedef unsigned long long ULL;

const int MAGIC = 37;

struct Triple {
    ULL hashCode;
    int begin, length;
    
    Triple(ULL hashCode = 0ULL, int begin = 0, int length = 0): hashCode(hashCode), begin(begin), length(length) {}
};

bool operator <(const Triple &a, const Triple &b) {
    return a.hashCode < b.hashCode;
}

int mark[26], markCount;
vector <Triple> segments;

int main() {
    scanf("%s", text);
    int n = strlen(text);
    for (int i = 0; i < n; ++ i) {
        ULL currentHashCode = 0ULL;
        markCount = 0;
        memset(mark, -1, sizeof(mark));
        for (int j = i; j < n; ++ j) {
            int token = text[j] - 'a';
            if (mark[token] == -1) {
                mark[token] = ++ markCount;
            }
            currentHashCode *= MAGIC;
            currentHashCode += mark[token];
            segments.push_back(Triple(currentHashCode, i, j - i + 1));
        }
    }
    sort(segments.begin(), segments.end());
    int result = 0;
    Triple choice;
    for (int begin = 0; begin < (int)segments.size(); ++ begin) {
        int end = begin;
        while (end < (int)segments.size() && segments[begin].hashCode == segments[end].hashCode) {
            end ++;
        }
        if ((end - begin) * segments[begin].length > result) {
            result = (end - begin) * segments[begin].length;
            choice = segments[begin];
        }
        begin = end - 1;
    }
    for (int i = 0; i < choice.length; ++ i) {
        printf("%c", text[choice.begin + i]);
    }
    puts("");
    return 0;
}
