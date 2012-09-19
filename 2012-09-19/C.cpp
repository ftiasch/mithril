#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <string>
using namespace std;

int n, m;

int main() {
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    map <string, int> need;
    need["white king"] = 1;
    need["white queen"] = 1;
    need["white bishop"] = 2;
    need["white knight"] = 2;
    need["white rook"] = 2;
    need["white pawn"] = 8;
    need["black king"] = 1;
    need["black queen"] = 1;
    need["black bishop"] = 2;
    need["black knight"] = 2;
    need["black rook"] = 2;
    need["black pawn"] = 8;
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; ++ i) {
        char s1[100],s2[100];
        string name="";
        scanf("%s%s",s1,s2);
        name=s1;
        name+=" ";
        name+=s2;
        need[name]--;
    }
    bool valid = true;
    for (map <string, int> :: iterator iter = need.begin(); iter != need.end(); ++ iter) {
        valid &= (iter->second) >= 0;
    }
    if (!valid) {
        puts("impossible");
    } else {
        vector <string> answer;
        for (int i = 0; i < m; ++ i) {
            char s1[100],s2[100];
			string name="";
			scanf("%s%s",s1,s2);
			name=s1;
			name+=" ";
			name+=s2;
            if (need[name] > 0) {
                need[name] --;
                answer.push_back(name);
            }
        }
        for (map <string, int> :: iterator iter = need.begin(); iter != need.end(); ++ iter) {
            valid &= iter->second == 0;
        }
        if (!valid) {
            puts("impossible");
        } else {
            for (vector <string> :: iterator iter = answer.begin(); iter != answer.end(); ++ iter) {
                printf("%s\n", iter->c_str());
            }
        }
    }
    return 0;
}
