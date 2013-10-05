#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

using std::vector;

vector <int> now;
vector <vector <int> > alls;
std::map <vector <int>, int> maps;

void generate(int i, int left) {
    if (i < 6) {
        for (int x = 0; x <= left; ++ x) {
            now[i] = x;
            generate(i + 1, left - x);
        }
    } else if (left == 0) {
        maps[now] = alls.size();
        alls.push_back(now);
    }
}

int main() {
    now.resize(6);
    generate(0, 15);
    int test_count = 0;
    while (true) {
        char buffer[2];
        scanf("%s", buffer);
        if (*buffer == 'e') {
            break;
        }
        printf("Case %d:", ++ test_count);
        if (*buffer == 'm') {
            for (int i = 0; i < 6; ++ i) {
                scanf("%d", &now[i]);
            }
            printf(" %d\n", maps[now]);
        } else {
            int id;
            scanf("%d", &id);
            for (int i = 0; i < 6; ++ i) {
                printf(" %d", alls[id][i]);
            }
            puts("");
        }
    }
    return 0;
}
