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

const int maxn = 333333;

int matching[maxn];
char str[maxn];

const int N = 12;
const int TRUE = N;
const int FALSE = N + 1;
const int NOT = N + 2;
const int AND = N + 3;
const int OR = N + 4;
const int IMPLY = N + 5;
const int EQUAL = N + 6;

const int len = 1 << (N - 5);

struct Result
{
    unsigned result[len];

    void assign(bool a) {
        memset(result, a ? -1 : 0, sizeof(result));
    }

    Result operator&(const Result &o) const {
        Result ret;
        for (int i = 0; i < len; i++) {
            ret.result[i] = result[i] & o.result[i];
        }
        return ret;
    }

    Result operator|(const Result &o) const {
        Result ret;
        for (int i = 0; i < len; i++) {
            ret.result[i] = result[i] | o.result[i];
        }
        return ret;
    }

    Result operator^(const Result &o) const {
        Result ret;
        for (int i = 0; i < len; i++) {
            ret.result[i] = result[i] ^ o.result[i];
        }
        return ret;
    }

    Result flip() const {
        Result ret = *this;
        for (int i = 0; i < len; i++) {
            ret.result[i] = ~ret.result[i];
        }
        return ret;
    }

    bool operator[](int index) const {
        return result[index >> 5] >> (index & 31) & 1;
    }
};

struct Node
{
    int oper;

    vector<Node*> nodes;

    Node(int l, int r) {
        assert(l <= r);
        while (l < r && matching[l] == r) {
            l ++;
            r --;
        }
        while (l + 1 < r && str[l] == '~' && str[l + 1] == '~') {
            l += 2;
        }
        if (l == r) {
            if (str[l] >= 'A' && str[l] <= 'L') {
                oper = str[l] - 'A';
                return;
            }
            if (str[l] == '0') {
                oper = FALSE;
                return;
            }
            if (str[l] == '1') {
                oper = TRUE;
                return;
            }
            assert(false);
        }
        int notPos = -1;
        vector<int> andPos, orPos;
        vector<int> implyPos, equalPos;
        for (int i = l; i <= r; i++) {
            char ch = str[i], ch1 = i < r ? str[i + 1] : 0;
            if (ch == '(') {
                i = matching[i];
            } else if (i == l && ch == '~') {
                notPos = i;
            } else if (ch == '&') {
                andPos.push_back(i);
            } else if (ch == '|') {
                orPos.push_back(i);
            } else if (ch == '-' && ch1 == '>') {
                implyPos.push_back(i);
                i ++;
            } else if (ch == '<' && ch1 == '=') {
                equalPos.push_back(i);
                i += 2;
            }
        }
        if (equalPos.size() >= 1) {
            oper = EQUAL;
            nodes.clear();
            nodes.push_back(new Node(l, equalPos[0] - 1));
            for (int i = 0; i + 1 < equalPos.size(); i++) {
                nodes.push_back(new Node(equalPos[i] + 3, equalPos[i + 1] - 1));
            }
            nodes.push_back(new Node(equalPos.back() + 3, r));
            return;
        }
        if (implyPos.size() >= 1) {
            oper = IMPLY;
            nodes.clear();
            nodes.push_back(new Node(l, implyPos[0] - 1));
            for (int i = 0; i + 1 < implyPos.size(); i++) {
                nodes.push_back(new Node(implyPos[i] + 2, implyPos[i + 1] - 1));
            }
            nodes.push_back(new Node(implyPos.back() + 2, r));
            return;
        }
        if (orPos.size() >= 1) {
            oper = OR;
            nodes.clear();
            nodes.push_back(new Node(l, orPos[0] - 1));
            for (int i = 0; i + 1 < orPos.size(); i++) {
                nodes.push_back(new Node(orPos[i] + 1, orPos[i + 1] - 1));
            }
            nodes.push_back(new Node(orPos.back() + 1, r));
            return;
        }
        if (andPos.size() >= 1) {
            oper = AND;
            nodes.clear();
            nodes.push_back(new Node(l, andPos[0] - 1));
            for (int i = 0; i + 1 < andPos.size(); i++) {
                nodes.push_back(new Node(andPos[i] + 1, andPos[i + 1] - 1));
            }
            nodes.push_back(new Node(andPos.back() + 1, r));
            return;
        }
        if (notPos >= 0) {
            oper = NOT;
            nodes.push_back(new Node(l + 1, r));
            return;
        }
        assert(false);
    }

    Result evaluate() {
        if (oper >= 0 && oper < N) {
            Result ret;
            ret.assign(false);
            for (int mask = 0; mask < (1 << N); mask++) {
                if (mask >> oper & 1) {
                    ret.result[mask >> 5] |= 1 << (mask & 31);
                }
            }
            return ret;
        }
        if (oper == TRUE) {
            Result ret;
            ret.assign(true);
            return ret;
        }
        if (oper == FALSE) {
            Result ret;
            ret.assign(false);
            return ret;
        }
        if (oper == NOT) {
            return nodes[0]->evaluate().flip();
        }
        if (oper == AND) {
            Result ret;
            ret.assign(true);
            FOR (it, nodes) {
                ret = ret & (*it)->evaluate();
            }
            return ret;
        }
        if (oper == OR) {
            Result ret;
            ret.assign(false);
            FOR (it, nodes) {
                ret = ret | (*it)->evaluate();
            }
            return ret;
        }
        if (oper == IMPLY) {
            Result ret = nodes.back() -> evaluate();
            for (int i = (int)nodes.size() - 2; i >= 0; i--) {
                ret = nodes[i]->evaluate().flip() | ret;
            }
            return ret;
        }
        if (oper == EQUAL) {
            Result val0, val1;
            val0.assign(false);
            val1.assign(true);
            for (int i = 0; i < nodes.size(); i++) {
                Result res = nodes[i]->evaluate();
                val0 = val0 | res;
                val1 = val1 & res;
            }
            return (val0 ^ val1).flip();
        }
        assert(false);
    }
};

int main()
{
    freopen("intelligent.in", "r", stdin);
    freopen("intelligent.out", "w", stdout);
    scanf("%s", str);
    int len = strlen(str);
    memset(matching, -1, sizeof(matching));
    vector<int> st;
    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            st.push_back(i);
        } else if (str[i] == ')') {
            assert(!st.empty());
            int j = st.back();
            st.pop_back();
            matching[i] = j;
            matching[j] = i;
        }
    }
    Node *root = new Node(0, len - 1);
    Result table = root->evaluate();
    vector<pair<int,int> > buffer;
    for (int i = 0; i < 1 << N; i += 2) {
        bool withA = table[i | 1];
        bool withoutA = table[i];
        if (withA && withoutA) {
            buffer.push_back(make_pair(i, i | 1));
        } else if (withA) {
            buffer.push_back(make_pair(i | 1, -1));
        } else if (withoutA) {
            buffer.push_back(make_pair(i, -1));
        }
    }
    if (buffer.size() > 0) {
        printf("%d\n", (int)buffer.size() + 1);
        FOR (it, buffer) {
            if (it->second >= 0) {
                printf("23 A ~A");
                for (int i = 1; i < N; i++) {
                    if (it->first >> i & 1) {
                        printf(" %c", 'A' + i);
                    } else {
                        printf(" ~%c", 'A' + i);
                    }
                }
                for (int i = 0; i < 10; i++) {
                    printf(" 0");
                }
                puts("");
            } else {
                printf("23");
                for (int i = 0; i < N; i++) {
                    if (it->first >> i & 1) {
                        printf(" %c", 'A' + i);
                    } else {
                        printf(" ~%c", 'A' + i);
                    }
                }
                for (int i = 0; i < 11; i++) {
                    printf(" 0");
                }
                puts("");
            }
        }
        printf("%d", (int)buffer.size() * 2);
        for (int i = 0; i < buffer.size(); i++) {
            printf(" %d ~0", i + 1);
        }
        puts("");
    } else {
        puts("2");
        puts("1 0");
        puts("1 0");
    }
}
