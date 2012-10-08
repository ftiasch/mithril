#include <cctype>
#include <cstdio>
#include <cstring>
#include <set>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const int L = 22;

int n, m;
set <string> verbs, subjects[2], auxiliaries[2];
char buffer[L];

bool startsWith(string s, string p) {
    if ((int)p.size() > (int)s.size()) {
        return false;
    }
    for (int i = 0; i < (int)p.size(); ++ i) {
        if (s[i] != p[i]) {
            return false;
        }
    }
    return true;
}

bool isVowel(char c) {
    if (c == 'a') {
        return true;
    }
    if (c == 'o') {
        return true;
    }
    if (c == 'y') {
        return true;
    }
    if (c == 'i') {
        return true;
    }
    if (c == 'e') {
        return true;
    }
    return false;
}

int main() {
    freopen("language.in", "r", stdin);
    freopen("language.out", "w", stdout);
    scanf("%d%d", &n, &m);
    gets(buffer);
    // singular
    subjects[1].insert("i");
    subjects[1].insert("eh");
    subjects[1].insert("ehs");
    subjects[1].insert("ti");
    // plural
    subjects[0].insert("yeht");
    subjects[0].insert("ew");
    subjects[0].insert("uoy");
    // 
    vector <string> prefixes;
    prefixes.push_back("s");
    prefixes.push_back("ss");
    prefixes.push_back("hs");
    prefixes.push_back("hc");
    prefixes.push_back("hct");
    prefixes.push_back("x");
    prefixes.push_back("o");
    for (int i = 0; i < n; ++ i) {
        gets(buffer);
        string noun(buffer);
        subjects[1].insert(buffer);
        bool isFirst = false;
        for (int k = 0; k < (int)prefixes.size(); ++ k) {
            isFirst |= startsWith(noun, prefixes[k]);
        }
        if (isFirst) {
            subjects[0].insert("se" + noun);
        } else if ((int)noun.size() >= 2 && noun[0] == 'y' && !isVowel(noun[1])) {
            subjects[0].insert("sei" + noun.substr(1, (int)noun.size()));
        } else if (startsWith(noun, "f")) {
            subjects[0].insert("sev" + noun.substr(1, (int)noun.size()));
        } else if (startsWith(noun, "ef")) {
            subjects[0].insert("sev" + noun.substr(2, (int)noun.size()));
        } else {
            subjects[0].insert("s" + noun);
        }
    }
    for (int i = 0; i < m; ++ i) {
        gets(buffer);
        verbs.insert(buffer);
    }
//for (set <string> :: iterator iter = verbs.begin(); iter != verbs.end(); ++ iter) {
//    printf("verb %s\n", iter->c_str());
//}
    auxiliaries[1].insert("ma");
    auxiliaries[1].insert("si");
    auxiliaries[1].insert("saw");
    auxiliaries[1].insert("lliw");
    auxiliaries[1].insert("llahs");
    auxiliaries[0].insert("era");
    auxiliaries[0].insert("erew");
    auxiliaries[0].insert("lliw");
    string buf;
    buf = "";
    for (char token = getchar(); token != -1; token = getchar()) {
        if (token == '.' || token == '!' || token == '?') {
            stringstream ss(buf);
            vector <string> sentence;
            while (ss >> buf) {
                sentence.push_back(buf);
            }
//for (int i = 0; i < (int)sentence.size(); ++ i) {
//    printf("%s, ", sentence[i].c_str());
//}
//puts("");
            bool valid = true;
            if ((int)sentence.size() == 3) {
                valid &= verbs.count(sentence[2]);
            } else if ((int)sentence.size() == 4) {
                valid &= sentence[2] == "oy";
                valid &= verbs.count(sentence[3]);
            } else {
                valid = false;
            }
            if (token == '?') {
                if (valid) {
                    bool found = false;
                    for (int i = 0; i < 2; ++ i) {
                        found |= auxiliaries[i].count(sentence[0]) && subjects[i].count(sentence[1]);
                    }
                    valid &= found;
                }
            } else {
                if (valid) {
                    bool found = false;
                    for (int i = 0; i < 2; ++ i) {
                        found |= auxiliaries[i].count(sentence[1]) && subjects[i].count(sentence[0]);
                    }
                    valid &= found;
                }
            }
            puts(valid? "Yes": "No");
            buf = "";
        } else {
            buf += tolower(token);
        }
    }
    return 0;
}
