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

const int BUFSIZE = 1 << 16;
const int MAXF = 20;

char input[BUFSIZE];
int matching[BUFSIZE];
int n, ptr;

string nextToken()
{
    assert(ptr < n);
    string ret;
    while (ptr < n && isalnum(input[ptr])) {
        ret += input[ptr ++];
    }
    return ret;
}

vector<string> nextList()
{
    assert(ptr < n && input[ptr] == '(');
    string line(input + ptr + 1, input + matching[ptr]);
    replace(line.begin(), line.end(), ',', ' ');
    vector<string> ret;
    istringstream ssin(line);
    for (string token; ssin >> token; ) {
        ret.push_back(token);
    }
    ptr = matching[ptr] + 1;
    return ret;
}

map<string, int> funcNameMap, parameterMap;

int getID(map<string,int> &mapping, const string &a)
{
    if (mapping.count(a)) {
        return mapping[a];
    }
    int ret = mapping.size();
    return mapping[a] = ret;
}

struct IfSt
{
    int condition;
    struct St *left, *right;

    void emulate(int &value, vector<pair<int,int> > &calls);
};

struct SeqSt
{
    struct St *left;
    struct SeqSt *right;

    void emulate(int &value, vector<pair<int,int> > &calls);
};

struct AssignSt
{
    int variable;
    int value;

    void emulate(int &value, vector<pair<int,int> > &calls);
};

struct FuncCallSt
{
    int funcName;
    int varCnt;
    int *vars;

    void emulate(int &value, vector<pair<int,int> > &calls);
};

struct St
{
    enum StType {
        NONE, IF, SEQ, ASSIGN, FUNCCALL
    } type;

    St();

    St(const struct IfSt *ptr);

    St(const struct SeqSt *ptr);

    St(const struct AssignSt *ptr);

    St(const struct FuncCallSt *ptr);

    union {
        IfSt If;
        SeqSt Seq;
        AssignSt Assign;
        FuncCallSt FuncCall;
    };

    void emulate(int &value, vector<pair<int,int> > &calls);
};

void IfSt::emulate(int &value, vector<pair<int,int> > &calls) {
    if (value >> condition & 1) {
        left->emulate(value, calls);
    } else {
        right->emulate(value, calls);
    }
}

void SeqSt::emulate(int &value, vector<pair<int,int> > &calls) {
    left->emulate(value, calls);
    if (right) {
        right->emulate(value, calls);
    }
}

void AssignSt::emulate(int &value, vector<pair<int,int> > &calls) {
    if (this->value) {
        value |= 1 << variable;
    } else {
        value &= ~(1 << variable);
    }
}

void FuncCallSt::emulate(int &value, vector<pair<int,int> > &calls) {
    int para = 0;
    for (int i = 0; i < varCnt; i++) {
        para |= (value >> vars[i] & 1) << i;
    }
    calls.push_back(make_pair(funcName, para));
}

St::St() : type(NONE) {}

St::St(const IfSt *ptr) {
    if (ptr) {
        type = IF;
        memcpy(&If, ptr, sizeof(IfSt));
    } else {
        type = NONE;
    }
}

St::St(const SeqSt *ptr) {
    if (ptr) {
        type = SEQ;
        memcpy(&Seq, ptr, sizeof(SeqSt));
    } else {
        type = NONE;
    }
}

St::St(const AssignSt *ptr) {
    if (ptr) {
        type = ASSIGN;
        memcpy(&Assign, ptr, sizeof(AssignSt));
    } else {
        type = NONE;
    }
}

St::St(const FuncCallSt *ptr) {
    if (ptr) {
        type = FUNCCALL;
        memcpy(&FuncCall, ptr, sizeof(FuncCallSt));
    } else {
        type = NONE;
    }
}

void St::emulate(int &value, vector<pair<int,int> > &calls) {
    if (type == IF) {
        If.emulate(value, calls);
    } else if (type == SEQ) {
        Seq.emulate(value, calls);
    } else if (type == ASSIGN) {
        Assign.emulate(value, calls);
    } else if (type == FUNCCALL) {
        FuncCall.emulate(value, calls);
    }
}

St *parse();

IfSt *parseIf()
{
    string token = nextToken();
    assert(token == "if");
    assert(input[ptr] == '(');
    ptr ++;
    token = nextToken();
    assert(input[ptr] == ')');
    ptr ++;
    IfSt *ret = new IfSt;
    assert(parameterMap.count(token));
    ret->condition = parameterMap[token];
    ret->left = parse();
    assert(strncmp(input + ptr, "else", 4) == 0);
    ptr += 4;
    ret->right = parse();
    return ret;
}

SeqSt *parseSeq()
{
    if (input[ptr] == '}') {
        return NULL;
    }
    SeqSt *ret = new SeqSt;
    ret->left = parse();
    ret->right = parseSeq();
    return ret;
}

AssignSt *parseAssign()
{
    string token = nextToken();
    AssignSt *ret = new AssignSt;
    assert(parameterMap.count(token));
    ret->variable = parameterMap[token];
    assert(input[ptr] == input[ptr + 1]);
    if (input[ptr] == '+') {
        ret->value = 1;
    } else if (input[ptr] == '-') {
        ret->value = 0;
    } else {
        assert(false);
    }
    ptr += 2;
    return ret;
}

FuncCallSt *parseFuncCall()
{
    string token = nextToken();
    assert(token != "");
    FuncCallSt *ret = new FuncCallSt;
    vector<string> lst = nextList();
    ret->funcName = getID(funcNameMap, token);
    ret->varCnt = lst.size();
    ret->vars = new int[ret->varCnt];
    for (int i = 0; i < lst.size(); i++) {
        assert(parameterMap.count(lst[i]));
        ret->vars[i] = parameterMap[lst[i]];
    }
    return ret;
}

St *parse()
{
    if (input[ptr] == '{') {
        ptr ++;
        SeqSt *seq = parseSeq();
        assert(input[ptr] == '}');
        ptr ++;
        return new St(seq);
    } else {
        int nptr = ptr;
        while (ptr < n && isalnum(input[nptr])) {
            nptr ++;
        }
        assert(nptr > ptr);
        if (nptr == ptr + 2 && strncmp(input + ptr, "if", 2) == 0) {
            return new St(parseIf());
        } else if (input[nptr] == '(') {
            return new St(parseFuncCall());
        } else if (input[nptr] == '+' || input[nptr] == '-') {
            return new St(parseAssign());
        } else {
            assert(false);
        }
    }
}

struct Func {
    int funcName;
    int parameters;
    St *program;

    void read() {
        string name = nextToken();
        assert(name != "");
        funcName = getID(funcNameMap, name);
        vector<string> ps = nextList();
        parameters = ps.size();
        parameterMap.clear();
        for (int i = 0; i < ps.size(); i++) {
            parameterMap[ps[i]] = i;
        }
        program = parse();
    }
};

Func func[MAXF];

void prepare()
{
    int len = fread(input, 1, BUFSIZE, stdin);
    n = 0;
    for (int i = 0; i < len; i++) {
        if (!isspace(input[i])) {
            input[n ++] = input[i];
        }
    }
    input[n] = '\0';
    memset(matching, -1, sizeof(matching));
    vector<int> st;
    for (int i = 0; i < n; i++) {
        if (input[i] == '(' || input[i] == '{') {
            st.push_back(i);
        } else if (input[i] == ')' || input[i] == '}') {
            int j = st.back();
            st.pop_back();
            matching[i] = j;
            matching[j] = i;
        }
    }
    ptr = 0;
    while (ptr < n) {
        Func f;
        f.read();
        func[f.funcName] = f;
    }
}

char vis[20][1 << 15];

int main()
{
    prepare();
    int n = funcNameMap.size();
    memset(vis, -1, sizeof(vis));
    vector<pair<int,int> > calls;
    for (int i = 0; i < n; i++) {
        int m = func[i].parameters;
        for (int mask = 0; mask < 1 << m; mask++) {
            if (vis[i][mask] < 0) {
                vector<pair<int,int> > st;
                st.push_back(make_pair(i, mask));
                while (!st.empty()) {
                    int fst = st.back().first;
                    int snd = st.back().second;
                    st.pop_back();
                    if (vis[fst][snd] < 0) {
                        vis[fst][snd] = 0;
                        st.push_back(make_pair(fst, snd));
                        calls.clear();
                        int tmp = snd;
                        func[fst].program->emulate(tmp, calls);
                        for (int i = (int)calls.size() - 1; i >= 0; i--) {
                            if (vis[calls[i].first][calls[i].second] < 0) {
                                st.push_back(calls[i]);
                            } else if (vis[calls[i].first][calls[i].second] == 0) {
                                puts("YES");
                                return 0;
                            }
                        }
                    } else if (vis[fst][snd] == 0) {
                        vis[fst][snd] = 1;
                    }
                }
            }
        }
    }
    puts("NO");
    return 0;
}
