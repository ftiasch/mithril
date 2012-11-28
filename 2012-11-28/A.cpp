#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

const int maxn = 666;

const int WORD = 0;
const int ALISTOF = 1;
const int COMMA = 2;
const int AND = 3;

int token[maxn];
int tokens;
string word[maxn];

int memo[maxn][maxn][2];

int go(int l, int r, int flag)
{
    if (l > r) {
        return 0;
    }
    int &ret = memo[l][r][flag];
    if (~ret) {
        return ret;
    }
    ret = 0;
    if (flag == 0) { // no previous ALISTOF
        if (l == r && token[l] == WORD) {
            ret ++;
        }
        if (token[l] == ALISTOF) {
            ret += go(l + 1, r, 1);
            ret += go(l + 1, r, 0);
        }
    } else {
        for (int i = l; i <= r; i++) {
            if (token[i] == COMMA) {
                ret += go(l, i - 1, 0) * go(i + 1, r, 1);
            } else if (token[i] == AND) {
                ret += go(l, i - 1, 0) * go(i + 1, r, 0);
            }
        }
    }
    if (ret > 2) {
        ret = 2;
    }
    return ret;
}

void construct(int l, int r, int flag)
{
    assert(go(l, r, flag) == 1);
    if (flag == 0) { // no previous ALISTOF
        if (l == r && token[l] == WORD) {
            printf("%s", word[l].c_str());
            return;
        }
        if (token[l] == ALISTOF) {
            if (go(l + 1, r, 1)) {
                putchar('(');
                construct(l + 1, r, 1);
                putchar(')');
                return;
            }
            if (go(l + 1, r, 0)) {
                putchar('(');
                construct(l + 1, r, 0);
                putchar(')');
                return;
            }
        }
    } else {
        for (int i = l; i <= r; i++) {
            if (token[i] == COMMA) {
                if (go(l, i - 1, 0) * go(i + 1, r, 1)) {
                    construct(l, i - 1, 0);
                    putchar(' ');
                    construct(i + 1, r, 1);
                    return;
                }
            } else if (token[i] == AND) {
                if (go(l, i - 1, 0) * go(i + 1, r, 0)) {
                    construct(l, i - 1, 0);
                    putchar(' ');
                    construct(i + 1, r, 0);
                    return;
                }
            }
        }
    }
    assert(false);
}

char buf[1 << 16];

int main()
{
    gets(buf);
    int tests = atoi(buf);
    for (int cas = 1; cas <= tests; cas++) {
        gets(buf);
        tokens = 0;
        for (int i = 0; buf[i]; i++) {
            if (buf[i] == 'l') {
                token[tokens++] = ALISTOF;
            } else if (buf[i] == 'n') {
                token[tokens++] = AND;
            } else if (buf[i] == ',') { 
                token[tokens++] = COMMA;
            } else if (isupper(buf[i])) {
                int ni = i;
                while (buf[ni] && isupper(buf[ni])) {
                    ni ++;
                }
                word[tokens] = string(buf + i, buf + ni);
                token[tokens++] = WORD;
                i = ni - 1;
            }
        }
        memset(memo, -1, sizeof(memo));
        int ret = go(0, tokens - 1, 0);
        assert(ret > 0);
        if (ret == 2) {
            puts("AMBIGUOUS");
        } else {
            construct(0, tokens - 1, 0);
            puts("");
        }
    }
}

