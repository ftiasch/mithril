#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

char buffer[111];
int indent[2][10], cost[2][10][3];

void prepare(char buffer[111], int &indent, int cost[3]) {
    cost[0] = cost[1] = cost[2] = 0;
    indent = 0;
    while (buffer[indent] == '.') {
        indent ++;
    }
    for (int i = indent; buffer[i]; ++ i) {
        if (buffer[i] == '(') {
            cost[0] ++;
        }
        if (buffer[i] == ')') {
            cost[0] --;
        }
        if (buffer[i] == '[') {
            cost[1] ++;
        }
        if (buffer[i] == ']') {
            cost[1] --;
        }
        if (buffer[i] == '{') {
            cost[2] ++;
        }
        if (buffer[i] == '}') {
            cost[2] --;
        }
    }
}

std::vector <int> choices[10];

int main() {
    while (true) {
        gets(buffer);
        int p, q;
        sscanf(buffer, "%d%d", &p, &q);
        if (p == 0) {
            break;
        }
        for (int i = 0; i < p; ++ i) {
            gets(buffer);
            prepare(buffer, indent[0][i], cost[0][i]);
        }
        for (int i = 0; i < q; ++ i) {
            gets(buffer);
            prepare(buffer, indent[1][i], cost[1][i]);
            choices[i].clear();
        }
        for (int r = 1; r <= 20; ++ r) {
            for (int c = 1; c <= 20; ++ c) {
                for (int s = 1; s <= 20; ++ s) {
                    int now[3] = {0, 0, 0};
                    bool valid = true;
                    for (int i = 0; i < p && valid; ++ i) {
                        int now_indent = now[0] * r + now[1] * c + now[2] * s;
                        valid &= now_indent == indent[0][i];
                        for (int j = 0; j < 3; ++ j) {
                            now[j] += cost[0][i][j];
                        }
                    }
                    if (valid) {
                        memset(now, 0, sizeof(now));
                        for (int i = 0; i < q; ++ i) {
                            int now_indent = now[0] * r + now[1] * c + now[2] * s;
                            choices[i].push_back(now_indent);
                            for (int j = 0; j < 3; ++ j) {
                                now[j] += cost[1][i][j];
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < q; ++ i) {
            std::sort(choices[i].begin(), choices[i].end());
            choices[i].erase(std::unique(choices[i].begin(), choices[i].end()), choices[i].end());
            int answer = (int)choices[i].size() == 1 ? choices[i][0] : -1;
            printf("%d%c", answer, " \n"[i == q - 1]);
        }
    }
    return 0;
}
