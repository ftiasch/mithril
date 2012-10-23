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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

vector<string> readLine()
{
    static char buf[1 << 20];
    gets(buf);
    for (int i = 0; buf[i]; i++) {
        if (!isalpha(buf[i])) {
            buf[i] = ' ';
        } else {
            buf[i] = tolower(buf[i]);
        }
    }
    istringstream ssin(buf);
    vector<string> ret;
    for (string word; ssin >> word; ret.push_back(word));
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

int spamCnt, goodCnt, messageCnt, threshold;

map<string, int> spam, good;

bool isSpam(const string &word)
{
    int spamHits = 0, goodHits = 0;
    if (spam.count(word)) {
        spamHits = spam[word];
    }
    if (good.count(word)) {
        goodHits = good[word];
    }
    if (spamHits == 0 && goodHits == 0) {
        return false;
    }
    return spamHits >= goodHits;
}

int main()
{
    scanf("%d%d%d%d", &spamCnt, &goodCnt, &messageCnt, &threshold);
    readLine();
    for (int i = 0; i < spamCnt; i++) {
        vector<string> line = readLine();
        FOR (word, line) {
            spam[*word] ++;
        }
    }
    for (int i = 0; i < goodCnt; i++) {
        vector<string> line = readLine();
        FOR (word, line) {
            good[*word] ++;
        }
    }
    for (int i = 0; i < messageCnt; i++) {
        vector<string> line = readLine();
        int spamHits = 0;
        FOR (word, line) {
            if (isSpam(*word)) {
                spamHits ++;
            }
        }
        if (spamHits * 100 >= line.size() * threshold) {
            puts("spam");
        } else {
            puts("good");
        }
    }
}
