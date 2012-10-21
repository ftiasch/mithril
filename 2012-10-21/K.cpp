#include <iomanip>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

int n;
string text, buffer;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

typedef unsigned long long ULL;

const ULL MAGIC = 217;

void format(string &s) {
    foreach (iter, s) {
        if (isalpha(*iter)) {
            *iter = tolower(*iter);
        } else {
            *iter = ' ';
        }
    }
}

ULL getHash(string &s) {
    ULL result = 0;
    foreach (iter, s) {
        result = result * MAGIC + *iter;
    }
    return result;
}

vector <pair <ULL, ULL> > queries;
set <pair <ULL, ULL> > querySet;

map <ULL, int> wordMap;
map <pair <ULL, ULL>, int> pairMap;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    getline(cin, buffer);
    for (int i = 0; i < n; ++ i) {
        getline(cin, buffer);
        text += " ";
        text += buffer;
    }
    format(text);
    int m;
    cin >> m;
    set <ULL> magics;
    for (int i = 0; i < m; ++ i) {
        cin >> buffer;
        format(buffer);
        magics.insert(getHash(buffer));
    }
    cin >> m;
    while (m --) {
        string a, b;
        cin >> a >> b;
        format(a);
        format(b);
        pair <ULL, ULL> ret = make_pair(getHash(a), getHash(b));
        if (ret.first > ret.second) {
            swap(ret.first, ret.second);
        }
        queries.push_back(ret);
        querySet.insert(ret);
    }
    stringstream strstr(text);
    string last;
    int wordCount = 0;
    while (strstr >> buffer) {
        if (magics.count(getHash(buffer))) {
            continue;
        }
        wordMap[getHash(buffer)] ++;
        wordCount ++;
        if (last != "") {
            pair <ULL, ULL> ret = make_pair(getHash(last), getHash(buffer));
            if (ret.first > ret.second) {
                swap(ret.first, ret.second);
            }
            if (querySet.count(ret)) {
                pairMap[ret] ++;
            }
        }
        last = buffer;
    }
    int pairCount = wordCount - 1;
    foreach (iter, queries) {
        if (!pairMap.count(*iter)) {
            cout << "0.0" << endl;
        } else {
            double d = (double)pairMap[*iter] / pairCount;
            d *= (double)wordCount / wordMap[iter->first];
            d *= (double)wordCount / wordMap[iter->second];
            cout << setprecision(15) << d << endl;
        }
    }
    return 0;
}
